/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
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

#ifndef __SCI_TMPDIR_H__
#define __SCI_TMPDIR_H__

#include <wchar.h>

wchar_t* getTMPDIRW(void);
char* getTMPDIR(void);

void setTMPDIRW(const wchar_t* _sci_tmpdir);
void setTMPDIR(const char* _sci_tmpdir);

wchar_t* computeTMPDIRW();
char* computeTMPDIR();

wchar_t* getenvTMPDIRW(void);
char* getenvTMPDIR(void);

void putenvTMPDIRW(const wchar_t* _sci_tmpdir);
void putenvTMPDIR(const char* _sci_tmpdir);

void defineTMPDIR();
void clearTMPDIR();

#endif // ! __SCI_TMPDIR_H__
