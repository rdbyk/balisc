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

#ifndef __SCI_LASTERROR_H__
#define __SCI_LASTERROR_H__

#include <wchar.h>
#include "BOOL.h"

int getLastErrorNumber(void);
wchar_t* getLastErrorMessage(void);
int getLastErrorLine(void);
wchar_t* getLastErrorFunction(void);

void setLastErrorNumber(int _iError);
void setLastErrorMessage(const wchar_t* _pwstError);
void setLastErrorLine(int _iLine);
void setLastErrorFunction(const wchar_t* _pwstFunction);

void setLastError(int _iError, const wchar_t* _pwstError, int _iLine, const wchar_t* _pwstFunction);

void SetError();
int isError();
void resetError();

#endif // ! __SCI_LASTERROR_H__
