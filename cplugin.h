#ifndef __CPLUGIN_H__
#define __CPLUGIN_H__

typedef struct {
    double re;
    double im;
} _complex;

typedef struct {
    char (*key)(void);
    int (*code)(void);
    char * (*name)(void);
    char * (*caption)(void);
    char * (*role)(void);
    _complex (*action)(_complex, _complex);
} ccalc_plugin;

#endif // __CPLUGIN_H__
