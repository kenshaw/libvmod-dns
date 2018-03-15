AM_CFLAGS = $(VARNISHAPI_CFLAGS)

# Modules

vmod_LTLIBRARIES = \
	libvmod_dns.la

libvmod_dns_la_LDFLAGS = $(VMOD_LDFLAGS)
libvmod_dns_la_SOURCES = vmod_dns.c
nodist_libvmod_dns_la_SOURCES = \
	vcc_dns_if.c \
	vcc_dns_if.h

@BUILD_VMOD_DNS@

# Test suite

AM_TESTS_ENVIRONMENT = \
	PATH="$(abs_builddir):$(VARNISH_TEST_PATH):$(PATH)" \
	LD_LIBRARY_PATH="$(VARNISH_LIBRARY_PATH)"
TEST_EXTENSIONS = .vtc
VTC_LOG_COMPILER = varnishtest -v
AM_VTC_LOG_FLAGS = \
	-p vcl_path="$(abs_top_srcdir)/vcl" \
	-p vmod_path="$(abs_builddir)/.libs:$(vmoddir)"

TESTS = \
	vtc/vmod_dns01.vtc \
	vtc/vmod_dns02.vtc \
	vtc/vmod_dns_valid_ip.vtc \
	vtc/vmod_dns_valid_host_ip.vtc \
	vtc/vmod_dns_valid_host_host.vtc \
	vtc/vmod_dns_example.vtc

# Documentation

dist_doc_DATA = \
	vmod_dns.vcc \
	$(TESTS)

dist_man_MANS = \
	vmod_dns.3


.rst.1:
	$(AM_V_GEN) $(RST2MAN) $< $@
