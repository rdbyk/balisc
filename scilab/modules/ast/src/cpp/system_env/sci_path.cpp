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

#include <stdlib.h>
#include "configvariable.hxx"
#include "string.hxx"
#include "context.hxx"
#include "filesep.h"

extern "C"
{
#include "sci_malloc.h"
#include "sci_path.h"
#include "os_string.h"
#include "charEncoding.h"
#include "PATH_MAX.h"
#include "setenvc.h"
#include "getenvc.h"
#include "getshortpathname.h"
#include "getlongpathname.h"
#include "strlen.h"
}

char *getSCI(void)
{
    return wide_string_to_UTF8(ConfigVariable::getSCIPath().c_str());
}

/*--------------------------------------------------------------------------*/
wchar_t *getSCIW(void)
{
    return os_wcsdup(ConfigVariable::getSCIPath().c_str());
}

/*--------------------------------------------------------------------------*/
void setSCIW(const wchar_t* _sci_path)
{
    char* pstPath = wide_string_to_UTF8(_sci_path);
    setSCI(pstPath);
    FREE(pstPath);
}
/*--------------------------------------------------------------------------*/
void setSCI(const char* _sci_path)
{
    BOOL bConvertOK = FALSE;
    char* ShortPath = getshortpathname(_sci_path, &bConvertOK);

    //SCI
    FileSep::Unix(ShortPath);
    wchar_t* pwstSCI = to_wide_string(ShortPath);
    FREE(ShortPath);
    types::String *pSSCI = new types::String(pwstSCI);
    FREE(pwstSCI);
    symbol::Context::getInstance()->put(symbol::Symbol(L"SCI"), pSSCI);

    //WSCI
#ifdef _MSC_VER
    char* LongPath = getlongpathname(_sci_path, &bConvertOK);
    FileSep::Win64(LongPath);
    wchar_t* pwstWSCI = to_wide_string(LongPath);
    FREE(LongPath);
    types::String *pSWSCI = new types::String(pwstWSCI);
    symbol::Context::getInstance()->put(symbol::Symbol(L"WSCI"), pSWSCI);
#else
    wchar_t* pwstWSCI = to_wide_string(_sci_path);
#endif

    std::wstring wst(pwstWSCI);
    ConfigVariable::setSCIPath(wst);

    FREE(pwstWSCI);
}
/*--------------------------------------------------------------------------*/
void putenvSCIW(const wchar_t* _sci_path)
{
    char* pstTemp = wide_string_to_UTF8(_sci_path);
    putenvSCI(pstTemp);
    FREE(pstTemp);
    return;
}
/*--------------------------------------------------------------------------*/
void putenvSCI(const char* _sci_path)
{
    /* to be sure that it's unix 8.3 format */
    /* c:/progra~1/scilab-5.0 */
    BOOL bConvertOK = FALSE;
    char* ShortPath = getshortpathname(_sci_path, &bConvertOK);

    FileSep::Unix(ShortPath);
    setenvc("SCI", ShortPath);
    FREE(ShortPath);
}
/*--------------------------------------------------------------------------*/
wchar_t* getenvSCIW()
{
    char *SciPath = getenvSCI();
    wchar_t* pstTemp = to_wide_string(SciPath);
    delete[] SciPath;
    return pstTemp;
}
/*--------------------------------------------------------------------------*/
char* getenvSCI()
{
    int ierr, iflag = 0;
    int lbuf = PATH_MAX;
    char *SciPath = new char[PATH_MAX];

    if (SciPath)
    {
        getenvc(&ierr, "SCI", SciPath, &lbuf, &iflag);

        if (ierr == 1)
        {
            delete[] SciPath;
            return NULL;
        }
    }

    return SciPath;
}
/*--------------------------------------------------------------------------*/
wchar_t* computeSCIW()
{
    char* pstTemp = computeSCI();
    wchar_t* pstReturn = to_wide_string(pstTemp);
    delete[] pstTemp;
    return pstReturn;
}
/*--------------------------------------------------------------------------*/
//windows : find main DLL and extract path
//linux and macos : scilab script fill SCI env variable
#ifdef _MSC_VER
char* computeSCI()
{
    char ScilabModuleName[MAX_PATH + 1];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    char SciPathName[_MAX_DRIVE + _MAX_DIR + 5];

    char *DirTmp = NULL;

    if (!GetModuleFileNameA((HINSTANCE)GetModuleHandleA("core"), ScilabModuleName, MAX_PATH))
    {
        return NULL;
    }

    os_splitpath(ScilabModuleName, drive, dir, fname, ext);

    if (dir[strlen(dir) - 1] == '\\')
    {
        dir[strlen(dir) - 1] = '\0';
    }

    DirTmp = strrchr(dir, '\\');
    if (strlen(dir) - strlen(DirTmp) > 0)
    {
        dir[strlen(dir) - strlen(DirTmp)] = '\0';
    }
    else
    {
        return NULL;
    }

    os_makepath(SciPathName, drive, dir, NULL, NULL);

    for (int i = 0 ; i < static_cast<int>(strlen(SciPathName)) ; i++)
    {
        if (SciPathName[i] == '\\')
        {
            SciPathName[i] = '/';
        }
    }
    SciPathName[strlen(SciPathName) - 1] = '\0';
    return os_strdup(SciPathName);
}
#else
char* computeSCI()
{
    int ierr, iflag = 0;
    int lbuf = PATH_MAX;
    char *SciPathName = new char[PATH_MAX];

    if (SciPathName)
    {
        getenvc(&ierr, "SCI", SciPathName, &lbuf, &iflag);

        if (ierr == 1)
        {
            std::cerr << "SCI environment variable not defined." << std::endl;
            exit(1);
        }
    }

    return SciPathName;
}
#endif
/*--------------------------------------------------------------------------*/
void defineSCI()
{
    wchar_t* sci_path = computeSCIW();
    setSCIW(sci_path);
    putenvSCIW(sci_path);
    FREE(sci_path);
}

