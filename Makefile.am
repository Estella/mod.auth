## Process this file with automake to produce Makefile.in
# "$Id$"

lib_LTLIBRARIES = libauth.la
libauth_la_SOURCES = auth.cc
libauth_la_LDFLAGS = -module -export-dynamic

EXTRA_DIST = auth.h \
	auth.example.conf.in \
	$(COMMAND_CONF)

confdir=${prefix}/bin
conf_DATA = auth.example.conf \
	$(COMMAND_CONF)
