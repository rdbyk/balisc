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

#ifndef __SCI_PATH_H__
#define __SCI_PATH_H__

#include <wchar.h>

wchar_t* getSCIW(void);
char* getSCI(void);

void setSCIW(const wchar_t* _sci_path);
void setSCI(const char* _sci_path);

wchar_t* computeSCIW();
char* computeSCI();

wchar_t* getenvSCIW(void);
char* getenvSCI(void);

void putenvSCIW(const wchar_t* _sci_path);
void putenvSCI(const char* _sci_path);

void defineSCI();

#endif // ! __SCI_PATH_H__
