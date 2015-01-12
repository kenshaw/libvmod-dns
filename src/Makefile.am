AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_dns.la

libvmod_dns_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_dns_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_dns.c

vcc_if.c vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_dns.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_dns.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc:
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_dns.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
