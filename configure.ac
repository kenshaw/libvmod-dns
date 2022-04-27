AC_PREREQ(2.68)
AC_COPYRIGHT([Copyright (c) 2013-2015 Kenneth Shaw, 2018 UPLEX])
AC_INIT([libvmod-dns], [trunk])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE([1.12 -Wall -Werror foreign parallel-tests])
AM_SILENT_RULES([yes])
AM_PROG_AR

LT_PREREQ([2.2.6])
LT_INIT([dlopen disable-static])

AC_ARG_WITH([rst2man],
	AS_HELP_STRING(
		[--with-rst2man=PATH],
		[Location of rst2man (auto)]),
	[RST2MAN="$withval"],
	[AC_CHECK_PROGS(RST2MAN, [rst2man rst2man.py], [])])

VARNISH_PREREQ([5.2.0])
VARNISH_VMODS([dns])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

AC_OUTPUT

AS_ECHO("
	==== $PACKAGE_STRING ====

	varnish:      $VARNISH_VERSION
	prefix:       $prefix
	vmoddir:      $vmoddir
	vcldir:       $vcldir
	pkgvcldir:    $pkgvcldir

	compiler:     $CC
	cflags:       $CFLAGS
	ldflags:      $LDFLAGS
")
