AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (c) 2013 kenneth shaw])
AC_INIT([libvmod-dns], [trunk])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR(src/vmod_dns.vcc)
AM_CONFIG_HEADER(config.h)

AC_CANONICAL_SYSTEM
AC_LANG(C)

AM_INIT_AUTOMAKE([foreign])

AC_GNU_SOURCE
AC_PROG_CC
AC_PROG_CC_STDC
if test "x$ac_cv_prog_cc_c99" = xno; then
	AC_MSG_ERROR([Could not find a C99 compatible compiler])
fi
AC_PROG_CPP

AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([sys/stdlib.h])

# Check for python
AC_CHECK_PROGS(PYTHON, [python3 python3.1 python3.2 python2.7 python2.6 python2.5 python2 python])
test -z "$PYTHON" && AC_MSG_ERROR([Python is needed to build this vmod, please install python.])

# Check for rst utilities
AC_PATH_PROG([RST2MAN], [rst2man])
test -z "$RST2MAN" && AC_MSG_ERROR([rst2man is required.])

VARNISH_VMOD_INCLUDES
VARNISH_VMOD_DIR
VARNISH_VMODTOOL

AC_PATH_PROG([VARNISHTEST], [varnishtest])
AC_PATH_PROG([VARNISHD], [varnishd])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
AC_OUTPUT
