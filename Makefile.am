## Process this file with automake to produce Makefile.in
# "$Id$"

lib_LTLIBRARIES = libauth.la
libauth_la_SOURCES = auth.cc
libauth_la_CXXFLAGS = -I${top_srcdir}/include \
	-I${top_srcdir}/libgnuworld
libauth_la_LDFLAGS = -module -export-dynamic

EXTRA_DIST = auth.h
