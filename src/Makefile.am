
vmoddir = $(VMODDIR)
vmod_LTLIBRARIES = libvmod_dns.la

libvmod_dns_la_CFLAGS = -I$(VARNISHSRC)/include -I$(VARNISHSRC)
libvmod_dns_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_dns_la_SOURCES = \
	vmod_dns.c
nodist_libvmod_dns_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

VMOD_TESTS = tests/*.vtc

$(libvmod_dns_la_OBJECTS): vcc_if.h

vcc_if.c vcc_if.h: $(VARNISHSRC)/lib/libvmod_std/vmod.py $(top_srcdir)/src/vmod_dns.vcc
	$(PYTHON) $(VARNISHSRC)/lib/libvmod_std/vmod.py $(top_srcdir)/src/vmod_dns.vcc

check:
	$(VARNISHSRC)/bin/varnishtest/varnishtest -Dvarnishd=$(VARNISHSRC)/bin/varnishd/varnishd -Dvmod_topbuild=$(abs_top_builddir) $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_dns.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h
