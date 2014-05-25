ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src

EXTRA_DIST = README.rst

dist_man_MANS = vmod_dns.3
MAINTAINERCLEANFILES = $(dist_man_MANS)

vmod_dns.3: README.rst

%.1 %.2 %.3 %.4 %.5 %.6 %.7 %.8 %.9:
	${RST2MAN} $< $@

