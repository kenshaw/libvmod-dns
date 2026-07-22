AC_PREREQ([2.69])
AC_COPYRIGHT([Copyright (c) 2013-2015 Kenneth Shaw, 2018 UPLEX])
AC_INIT([libvmod-dns],[trunk])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/vmod_dns.vcc])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.12 -Wall -Werror foreign parallel-tests])
AM_SILENT_RULES([yes])

AC_ARG_VAR([RST2MAN], [the program to build manuals from reStructuredText])
AC_CHECK_PROGS(RST2MAN, [rst2man rst2man.py])

AC_ARG_WITH([lcov],
    AS_HELP_STRING(
        [--with-lcov=PATH],
        [Location of lcov to generate coverage data (auto)]),
    [LCOV="$withval"],
    [AC_CHECK_PROGS(LCOV, [lcov], [])])
AM_CONDITIONAL(HAVE_LCOV, [test -n "$LCOV"])

AC_ARG_WITH([genhtml],
    AS_HELP_STRING(
        [--with-genhtml=PATH],
        [Location of genhtml to generate coverage reports (auto)]),
    [GENHTML="$withval"],
    [AC_CHECK_PROGS(GENHTML, [genhtml], [])])
AM_CONDITIONAL(HAVE_GENHTML, [test -n "$GENHTML"])

VINYL_PREREQ([9.0.0])
VINYL_VMODS([dns])

AM_PROG_AR

LT_PREREQ([2.2.6])
LT_INIT([dlopen disable-static])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

AC_CHECK_PROG([HAVE_GIT], [git], [yes], [no])
if test "x$HAVE_GIT" = "xyes"; then
	if git rev-parse --git-dir >/dev/null 2>&1; then
		HAVE_GIT_REPO=yes
	else
		HAVE_GIT_REPO=no
	fi
else
	HAVE_GIT_REPO=no
fi
AM_CONDITIONAL([HAVE_VCS_VMOD_VERSION], [test -f "src/vmod_vcs_version.txt" || test "x$HAVE_GIT_REPO" = "xyes"])
if test "x$HAVE_GIT_REPO" != "xyes" && test ! -f "src/vmod_vcs_version.txt"; then
   AC_MSG_WARN([Building without version control metadata - vmod_vcs_version.txt will be unavailable])
fi

AC_OUTPUT

AS_ECHO("
	==== $PACKAGE_STRING ====

	vinyl:        $VINYL_VERSION
	prefix:       $prefix
	vmoddir:      $vmoddir
	vcldir:       $vcldir
	pkgvcldir:    $pkgvcldir

	compiler:     $CC
	cflags:       $CFLAGS
	ldflags:      $LDFLAGS
")
