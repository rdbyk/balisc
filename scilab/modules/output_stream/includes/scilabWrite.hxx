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

#ifndef __SCILABWRITE_HXX__
#define __SCILABWRITE_HXX__

#define SPACES_LIST L"      "

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*SCILAB_OUTPUT_METHOD)(const char *text);

void setScilabOutputMethod(SCILAB_OUTPUT_METHOD writer);

void scilabWrite(const char* _pstText);

void scilabWriteW(const wchar_t* _pwstText);

void scilabError(const char* _pstText);
void scilabErrorW(const wchar_t* _pwstText);

/* functions write in "console" without take care of mode*/
void scilabForcedWriteW(const wchar_t* _pwsText);
void scilabForcedWrite(const char* _pstText);

#ifdef __cplusplus
}
#endif

#endif /* __SCILABWRITE_HXX__ */
