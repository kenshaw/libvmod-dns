AM_CFLAGS = $(VINYLAPI_CFLAGS)

# Modules

vmod_LTLIBRARIES = \
	libvmod_dns.la

libvmod_dns_la_LDFLAGS = $(VMOD_LDFLAGS)
libvmod_dns_la_SOURCES = vmod_dns.c
nodist_libvmod_dns_la_SOURCES = \
	vcc_dns_if.c \
	vcc_dns_if.h

DISTCLEANFILES = vmod_vcs_version.txt

vmod_vcs_version.txt: $(nodist_libvmod_dns_la_SOURCES)

@BUILD_VMOD_DNS@

# Test suite

AM_TESTS_ENVIRONMENT = \
	PATH="$(abs_builddir):$(VINYL_TEST_PATH):$(PATH)" \
	LD_LIBRARY_PATH="$(VINYL_LIBRARY_PATH)"
TEST_EXTENSIONS = .vtc
VTC_LOG_COMPILER = vtest -v
AM_VTC_LOG_FLAGS = \
	-p vcl_path="$(abs_top_srcdir)/vcl" \
	-p vmod_path="$(abs_builddir)/.libs:$(vmoddir):$(VINYLAPI_VMODDIR)"

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

if HAVE_VCS_VMOD_VERSION
dist_doc_DATA += vmod_vcs_version.txt
endif

dist_man_MANS = \
	vmod_dns.3


.rst.1:
	$(AM_V_GEN) $(RST2MAN) $< $@

# Code coverage

GCOV_PREFIX ?= $(builddir)/coverage

gcov: clean
	$(AM_V_at)@mkdir -p $(GCOV_PREFIX) && chmod 777 -R $(GCOV_PREFIX)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) CC=gcc \
		CFLAGS="${AM_CFLAGS} --coverage -fno-inline -g -O0" check

# Set QUIET=-q for non-verbose builds, otherwise set to empty.
QUIET_0 = -q
QUIET_ = $(QUIET_@AM_DEFAULT_V@)
QUIET = $(QUIET_@AM_V@)

coverage/lcov.info: gcov
if HAVE_LCOV
	-$(AM_V_at)@cp -R $(GCOV_PREFIX)/.libs $(builddir) 2> /dev/null
	$(AM_V_GEN) $(LCOV) $(QUIET)				\
		-c -d $(builddir)/.libs -o $(GCOV_PREFIX)/lcov.info
else
	@echo "================================================="
	@echo "You need lcov installed to generate coverage data"
	@echo "================================================="
	@false
endif

coverage: coverage/lcov.info
if HAVE_GENHTML
	$(AM_V_GEN) $(GENHTML) $(QUIET) $(GCOV_PREFIX)/lcov.info \
		-o $(GCOV_PREFIX)
else
	@echo "======================================================="
	@echo "You need genhtml installed to generate coverage reports"
	@echo "======================================================="
	@false
endif

clean-local:
	@rm -rf $(GCOV_PREFIX)
