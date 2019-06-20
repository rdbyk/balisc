# Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
# Copyright (C) 2006 - INRIA - Sylvestre LEDRU
# Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
#
# This file is distributed under the same license as the Scilab package.

GATEWAY_CPP_SOURCES = \
    sci_gateway/cpp/integer_gw.cpp \
    sci_gateway/cpp/sci_inttype.cpp \
    sci_gateway/cpp/sci_double.cpp \
    sci_gateway/cpp/sci_int.cpp \
    sci_gateway/cpp/sci_iconvert.cpp \
    sci_gateway/cpp/sci_intmax.cpp \
    sci_gateway/cpp/sci_intmin.cpp

libsciinteger_la_CPPFLAGS = \
    -I$(srcdir)/includes/ \
    -I$(srcdir)/src/cpp/ \
    -I$(top_srcdir)/modules/ast/includes/ast/ \
    -I$(top_srcdir)/modules/ast/includes/exps/ \
    -I$(top_srcdir)/modules/ast/includes/operations/ \
    -I$(top_srcdir)/modules/ast/includes/parse/ \
    -I$(top_srcdir)/modules/ast/includes/symbol/ \
    -I$(top_srcdir)/modules/ast/includes/system_env/ \
    -I$(top_srcdir)/modules/ast/includes/types/ \
    -I$(top_srcdir)/modules/ast/includes/analysis/ \
    -I$(top_srcdir)/modules/api_scilab/includes/ \
    -I$(top_srcdir)/modules/output_stream/includes/ \
    -I$(top_srcdir)/modules/localization/includes/ \
    -I$(top_srcdir)/modules/dynamic_link/includes/ \
    -I$(top_srcdir)/modules/threads/includes/ \
    -I$(top_srcdir)/modules/string/includes/ \
    -I$(top_srcdir)/modules/console/includes/ \
    $(AM_CPPFLAGS)

if MAINTAINER_MODE
pkglib_LTLIBRARIES = libsciinteger.la
else
noinst_LTLIBRARIES = libsciinteger.la
endif

libsciinteger_la_SOURCES = $(GATEWAY_C_SOURCES) $(GATEWAY_CPP_SOURCES)

# For the code check (splint)
CHECK_SRC = $(GATEWAY_C_SOURCES)
INCLUDE_FLAGS = $(libsciinteger_la_CPPFLAGS)

#### Target ######
modulename=integer

#### integer : Conf files ####
libsciinteger_la_rootdir = $(mydatadir)
libsciinteger_la_root_DATA = license.txt

#### integer : init scripts ####
libsciinteger_la_etcdir = $(mydatadir)/etc
libsciinteger_la_etc_DATA = \
    etc/integer.quit \
    etc/integer.start

#### integer : gateway declaration ####
libsciinteger_la_sci_gatewaydir = $(mydatadir)/sci_gateway

include $(top_srcdir)/Makefile.incl.am
