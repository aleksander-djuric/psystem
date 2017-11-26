AC_INIT([ccalc], [2.0])                                                                                                                 
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([ccalc.c])
AC_CONFIG_HEADERS([config.h])

LT_INIT
AC_ENABLE_SHARED
AC_ENABLE_STATIC

# Checks for programs.
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h termios.h])

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile
                 plugins/Makefile])
AC_OUTPUT
