# Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
# Copyright (C) 2007 - INRIA - Bruno JOFRET
# Copyright (C) 2010 - DIGITEO - Bruno JOFRET
# Copyright (C) 2011 - DIGITEO - Antoine ELIAS
# Copyright (C) 2012 - 2016 - Scilab Enterprises
# Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
#
# This file is hereby licensed under the terms of the GNU GPL v2.0,
# pursuant to article 5.3.4 of the CeCILL v.2.1.
# This file was originally licensed under the terms of the CeCILL v2.1,
# and continues to be available under such terms.
# For more information, see the COPYING file which you should have received
# along with this program.

OUTPUT_STREAM_CPP_SOURCES = \
	src/cpp/Diary.cpp \
	src/cpp/scilabWrite.cpp \
	src/cpp/DiaryList.cpp \
	src/cpp/diary_manager.cpp \
	src/cpp/getDiaryDate.cpp \
	src/cpp/getUniqueFilename.cpp \
	src/cpp/scilab_sprintf.cpp \
	src/cpp/basout.cpp \
	src/cpp/Sciwarning.cpp \
	src/cpp/Scierror.cpp


GATEWAY_CPP_SOURCES = \
	sci_gateway/cpp/sci_diary.cpp \
	sci_gateway/cpp/sci_disp.cpp \
	sci_gateway/cpp/output_stream_gw.cpp \
	sci_gateway/cpp/sci_msprintf.cpp \
	sci_gateway/cpp/sci_mprintf.cpp \
	sci_gateway/cpp/sci_print.cpp

OUTPUT_STREAM_C_SOURCES = \
	src/c/sciprint.c \
	src/c/error.c

OUTPUT_STREAM_FORTRAN_SOURCES = \
	src/fortran/fmttyp.f


libscioutput_stream_la_CPPFLAGS= \
    -I$(srcdir)/includes/ \
    -I$(srcdir)/src/cpp/ \
    -I$(srcdir)/src/c/ \
    -I$(top_srcdir)/modules/ast/includes/ast/ \
    -I$(top_srcdir)/modules/ast/includes/exps/ \
    -I$(top_srcdir)/modules/ast/includes/operations/ \
    -I$(top_srcdir)/modules/ast/includes/parse/ \
    -I$(top_srcdir)/modules/ast/includes/symbol/ \
    -I$(top_srcdir)/modules/ast/includes/system_env/ \
    -I$(top_srcdir)/modules/ast/includes/types/ \
    -I$(top_srcdir)/modules/ast/includes/analysis/ \
    -I$(top_srcdir)/modules/core/includes/ \
    -I$(top_srcdir)/modules/api_scilab/includes \
    -I$(top_srcdir)/modules/string/includes \
    -I$(top_srcdir)/modules/functions_manager/includes \
    -I$(top_srcdir)/modules/threads/includes \
    -I$(top_srcdir)/modules/console/includes \
    -I$(top_srcdir)/modules/dynamic_link/includes \
    -I$(top_srcdir)/modules/localization/includes/ \
    -I$(top_srcdir)/modules/fileio/includes/ \
    $(AM_CPPFLAGS)

if MAINTAINER_MODE
pkglib_LTLIBRARIES = libscioutput_stream.la
noinst_LTLIBRARIES = libscioutput_stream-algo.la
else
noinst_LTLIBRARIES = libscioutput_stream-algo.la libscioutput_stream.la
endif


libscioutput_stream_algo_la_SOURCES = $(OUTPUT_STREAM_C_SOURCES) $(OUTPUT_STREAM_CPP_SOURCES) $(OUTPUT_STREAM_FORTRAN_SOURCES) $(JNI_SOURCES)
libscioutput_stream_la_SOURCES = $(GATEWAY_CPP_SOURCES)
libscioutput_stream_algo_la_CPPFLAGS = $(libscioutput_stream_la_CPPFLAGS)

# For the code check (splint)
CHECK_SRC= $(OUTPUT_STREAM_C_SOURCES) $(OUTPUT_STREAM_CPP_SOURCES) $(OUTPUT_STREAM_CPP_SOURCES)
INCLUDE_FLAGS = $(libscioutput_stream_la_CPPFLAGS)

libscioutput_stream_la_LIBADD =  libscioutput_stream-algo.la $(FLIBS)

#### Target ######
modulename=output_stream

#### output_stream : Conf files ####
libscioutput_stream_la_rootdir = $(mydatadir)
libscioutput_stream_la_root_DATA =  license.txt


#### output_stream : init scripts ####
libscioutput_stream_la_etcdir = $(mydatadir)/etc
libscioutput_stream_la_etc_DATA = \
    etc/output_stream.quit \
    etc/output_stream.start

#### output_stream : gateway declaration ####
libscioutput_stream_la_sci_gatewaydir = $(mydatadir)/sci_gateway

#### output_stream : include files ####
libscioutput_stream_la_includedir=$(pkgincludedir)
libscioutput_stream_la_include_HEADERS = includes/do_error_number.h \
includes/sciprint.h \
includes/Scierror.h \
includes/scilabWrite.hxx

include $(top_srcdir)/Makefile.incl.am

