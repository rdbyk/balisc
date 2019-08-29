/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009-2009 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 * 
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "scilabWrite.hxx"
#include "configvariable.hxx"

extern "C"
{
#include <stdio.h>
#include "charEncoding.h"
#include "sci_malloc.h"
#include "diary.h"
}

static SCILAB_OUTPUT_METHOD _writer_output;
static SCILAB_OUTPUT_METHOD _writer_error;

void setScilabOutputMethod(SCILAB_OUTPUT_METHOD writer)
{
    _writer_output = writer;
    _writer_error = writer;
}

void setScilabErrorStreamMethod(SCILAB_OUTPUT_METHOD writer)
{
    _writer_error = writer;
}

void setScilabOutputStreamMethod(SCILAB_OUTPUT_METHOD writer)
{
    _writer_output = writer;
}

static void scilabPrint(const char* _pstText)
{
    wchar_t* pwstTemp = to_wide_string(_pstText);
    diaryWrite(pwstTemp, FALSE);
    FREE(pwstTemp);
    (*_writer_output)(const_cast<char*>(_pstText));
}

static inline void scilabPrintW(const wchar_t* _pwsText)
{
    diaryWrite(_pwsText, FALSE);
    char* pstTemp = wide_string_to_UTF8(_pwsText);
    (*_writer_output)(const_cast<char*>(pstTemp));
    FREE(pstTemp);
}

static void scilabPrintError(const char* _pstText)
{
    wchar_t* pwstTemp = to_wide_string(_pstText);
    diaryWrite(pwstTemp, FALSE);
    FREE(pwstTemp);
    (*_writer_error)(const_cast<char*>(_pstText));
}

void scilabWrite(const char* _pstText)
{
    if (ConfigVariable::isPrintOutput())
    {
        scilabPrint(const_cast<char*>(_pstText));
    }
}

void scilabForcedWrite(const char* _pstText)
{
    scilabPrint(const_cast<char*>(_pstText));
}

void scilabWriteW(const wchar_t* _pwsText)
{
    if (ConfigVariable::isPrintOutput())
    {
        scilabPrintW(const_cast<wchar_t*>(_pwsText));
    }
}

void scilabForcedWriteW(const wchar_t* _pwsText)
{
    scilabPrintW(const_cast<wchar_t*>(_pwsText));
}

void scilabError(const char* _pstText)
{
    if (ConfigVariable::isSilentError() == 0)
    {
        scilabPrintError(const_cast<char*>(_pstText));
    }
}

void scilabErrorW(const wchar_t* _pwsText)
{
    if (ConfigVariable::isSilentError() == 0)
    {
        char* pstTemp = wide_string_to_UTF8(_pwsText);
        scilabPrintError(pstTemp);
        FREE(pstTemp);
    }
}
