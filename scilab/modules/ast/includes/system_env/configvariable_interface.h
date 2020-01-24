/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2020 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#ifndef __CONFIGVARIABLE_INTERFACE_H__
#define __CONFIGVARIABLE_INTERFACE_H__

#include <string.h>
#include <wchar.h>

typedef enum
{
    SCILAB_API = 1, /* Scilab is launch as an API */
    SCILAB_STD, /* The standard Scilab (gui, plot ...) */
    SCILAB_NW, /* Scilab in command line with the plots */
    SCILAB_NWNI /* Scilab in command line without any graphics. What not mandataroy here */
} scilabMode;

int getSimpMode(void);
void setSimpMode(int);
int getStartProcessing();
int getEndProcessing();

void setFormatSize(int _iFormatSize);
int getFormatSize(void);
void setFormatMode(int _iFormatMode);
int getFormatMode(void);
void setConsoleWidth(int _iConsoleWidth);
int getConsoleWidth(void);
void setConsoleLines(int _iConsoleLines);
int getConsoleLines(void);
int getPromptMode(void);

int getieee(void);
void setieee(int);

scilabMode getScilabMode(void);
void setScilabMode(scilabMode newmode);
const char * getScilabModeString(void);

int getWarningMode(void);
void setWarningMode(int _iMode);
int getWarningStop(void);
void setWarningStop(int _iMode);

int checkReferenceModule(const wchar_t* _module);
void addReferenceModule(const wchar_t* _module);
void removeReferenceModule(const wchar_t* _module);

int getForceQuit();

int getEntryPointPosition(wchar_t* _pwstEntryPointName);
typedef void(*dynlib_ptr)();
dynlib_ptr getEntryPointFromPosition(int position);

int isEnableDebug();
int isDebugInterrupted();

int isExecutionBreak();
void setExecutionBreak();
void resetExecutionBreak();

int setRecursionLimit(int);
#endif /* !__CONFIGVARIABLE_INTERFACE_H__ */
