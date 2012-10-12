## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

wa_tor_edocdir = ${prefix}/doc/wa_tor_e
wa_tor_edoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(wa_tor_edoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(wa_tor_edocdir)
