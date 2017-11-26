/*
 * ccalc.c
 *
 * Description: Complex calc with plug-in system (Example)
 * Copyright (c) 2017 Aleksander Djuric. All rights reserved.
 * Distributed under the GNU Lesser General Public License (LGPL).
 * The complete text of the license can be found in the LICENSE
 * file included in the distribution.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <ctype.h>
#include <dirent.h>
#include <dlfcn.h>
#include "cplugin.h"

#define MAX_STR 255
#define PLUGIN_DIR "./plugins/bin/"

struct plugin_ent
{
    ccalc_plugin p;
    struct plugin_ent *next;
};

struct plugin_ent *curr = NULL;

int plist_add (char *pname)
{
    struct plugin_ent *node;
    char ppath[MAX_STR+1];
    void *phandle;

    node = (struct plugin_ent *) malloc (sizeof (struct plugin_ent));
    if (!node) return 1;

    snprintf(ppath, MAX_STR, "%s%s", PLUGIN_DIR, pname);
    printf("loading: %s.. ", pname);
    phandle = dlopen(ppath, RTLD_LAZY);
    printf("%s\n", phandle ? "ok" : "fail");

    if (!phandle ||
	!(node->p.key = dlsym(phandle, "key")) ||
	!(node->p.code = dlsym(phandle, "code")) ||
	!(node->p.name = dlsym(phandle, "name")) ||
	!(node->p.caption = dlsym(phandle, "caption")) ||
	!(node->p.role = dlsym(phandle, "role")) ||
	!(node->p.action = dlsym(phandle, "action"))) {
	free(node);
	return -1;
    }

    node->next = curr;
    curr = node;

    return 0;
}

void plist_print (void)
{
    struct plugin_ent *node = NULL;
    struct plugin_ent *p = curr;

    printf("Available functions: ");
    
    while (curr)
    {
	node = curr;
	curr = curr->next;
	printf("* %c (%s) ", node->p.key(), node->p.name());
    }
    printf("\n");

    curr = p;
}

struct plugin_ent * plist_search (int code)
{
    int found = 0;
    struct plugin_ent *node = NULL;
    struct plugin_ent *p = curr;

    while (curr)
    {
	node = curr;

	if (node->p.code() == code) {
	    found = 1;
	    break;
	}

	curr = curr->next;
    }
    
    curr = p;
    
    return (found)? node : NULL;
}

void plist_free (void)
{
    struct plugin_ent *node = NULL;

    while (curr)
    {
	node = curr;
	curr = curr->next;
	free(node);
    }
}

void term_mode (int mode, struct termios *term)
{
    if (mode) {
	term->c_lflag |= ICANON;
	term->c_lflag |= ECHO;
	tcsetattr(fileno(stdin), TCSANOW, term);
    } else {
	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	tcsetattr(fileno(stdin), TCSANOW, term);
    }
}

void cfread(_complex *a, _complex *b, struct termios *term)
{
    term_mode(1, term);
    
    printf("Real A: ");
    scanf("%lf", &(a->re));
    printf("Img A: ");
    scanf("%lf", &(a->im));
    
    printf("Real B: ");
    scanf("%lf", &(b->re));
    printf("Img B: ");
    scanf("%lf", &(b->im));
    
    term_mode(0, term);
}

void cprintf(_complex a, char *s) {
    printf("%s = %lf + %lf i\n", s, a.re, a.im);
}


int main(int argc, char *argv[])
{
    char cmd;
    _complex a, b, c;
    DIR *dir;
    struct dirent *ent;
    struct termios term;
    struct plugin_ent *pe = NULL;

    printf("Complex calc with plug-in system (Example)\n");

    if ((dir = opendir(PLUGIN_DIR)) != NULL) {
	while ((ent = readdir(dir)) != NULL) {
	    if (ent->d_name[0] != '.')
		if (plist_add(ent->d_name) < 0)
		    printf("!!! %s\n", dlerror());
	}
	closedir(dir);
    }

    plist_print();

    tcgetattr(fileno(stdin), &term);
    term_mode(0, &term);

    do {
	cmd = getchar();

	switch (cmd) {
	case 113:	// 'Q'
	case 10:	// 'Enter'
	    break;
	default:
	    pe = plist_search(cmd);
	    if (pe) {
		printf("\n%s\n", pe->p.caption());
		cfread(&a, &b, &term);
		c = pe->p.action(a, b);
		cprintf(c, pe->p.role());
	    } else {
		printf("Command: '%c' is not supported\n", cmd);
	    }
	    break;
	}
    } while (cmd != 113); // 113 = 'Q

    term_mode(1, &term);
    plist_free();

    return 0;
}
