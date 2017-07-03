bin_PROGRAMS = findup
dist_doc_DATA = README.md
findup_SOURCES = src/findup.c
SUBDIRS = lib
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4
findup_LDADD = lib/libgnu.a
AM_CPPFLAGS = -I$(top_srcdir)/lib
