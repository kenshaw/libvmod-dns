
vmoddir = $(VMOD_DIR)
vmod_LTLIBRARIES = libvmod_dns.la

libvmod_dns_la_CFLAGS = $(VMOD_INCLUDES)
libvmod_dns_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_dns_la_SOURCES = \
	vmod_dns.c
nodist_libvmod_dns_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

VMOD_TESTS = tests/*.vtc

$(libvmod_dns_la_OBJECTS): vcc_if.h

vcc_if.c vcc_if.h vmod_dns.man.rst: $(VMODTOOL) $(top_srcdir)/src/vmod_dns.vcc
	$(PYTHON) $(VMODTOOL) $(top_srcdir)/src/vmod_dns.vcc

check:
	$(VARNISHTEST) -Dvarnishd=$(VARNISHD) \
	    -Dvmod_topbuild=$(abs_top_builddir) $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_dns.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_dns.rst \
	$(builddir)/vmod_dns.man.rst
