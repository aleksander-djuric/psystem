AC_INIT([ccalc], [2.0])                                                                                                                 
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([ccalc.c])
AC_CONFIG_HEADERS([config.h])

LT_INIT
AC_ENABLE_SHARED
AC_ENABLE_STATIC

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Common compiler flags
CFLAGS="-Wall -O2"

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h termios.h])

AC_CONFIG_FILES([Makefile
                 plugins/Makefile])
AC_OUTPUT
