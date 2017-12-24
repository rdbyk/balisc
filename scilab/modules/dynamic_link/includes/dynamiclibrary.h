/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */
#ifndef __DYNAMICLIBRARY_H__
#define __DYNAMICLIBRARY_H__

#include <wchar.h>
#include "BOOL.h"

typedef int(*PROC_GATEWAY) (void);

typedef enum
{
    DYN_GW_NO_ERROR = 0,
    DYN_GW_LOAD_LIBRARY_ERROR = 1,
    DYN_GW_PTR_FUNCTION_ERROR = 2,
    DYN_GW_CALL_FUNCTION_ERROR = 3

} dynamic_gateway_error_code;

typedef enum
{
    DYNLIB_NAME_FORMAT_AUTO = 0,
    DYNLIB_NAME_FORMAT_1 = 1,
    DYNLIB_NAME_FORMAT_2 = 2,
    DYNLIB_NAME_FORMAT_3 = 3
} dynlib_name_format;

#define FORMATGATEWAYLIBNAME_1 L"%ls%ls"
#define FORMATGATEWAYLIBNAME_2 L"sci%ls%ls"
#define FORMATGATEWAYLIBNAME_3 L"libsci%ls%ls"

#ifdef _MSC_VER

#ifdef _WIN32 // guard against mis-compilation

//avoid declaration on macro min/max
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX

typedef HINSTANCE DynLibHandle;
typedef FARPROC DynLibFuncPtr;

/**
* Maps the specified executable module into the address space of the calling process
* @param name of dynamic library
* @return Handle to the loaded library
*/
DynLibHandle LoadDynLibrary(char *libname);
DynLibHandle LoadDynLibraryW(wchar_t *libname);

/**
* return last dynamic linking error
* @return a string
*/
char * GetLastDynLibError(void);

#endif /* _WIN32 // guard against mis-compilation */

#else

#if defined(__GNUC__) // guard against mis-compilation

#include <dlfcn.h>

typedef void * DynLibHandle;
typedef void * DynLibFuncPtr;

/**
* Maps the specified executable module into the address space of the calling process
* @param name of dynamic library
* @return Handle to the loaded library
*/
#define LoadDynLibrary(libname) ((DynLibHandle)dlopen(libname,  RTLD_NOW | RTLD_GLOBAL));

/**
* return last dynamic linking error
* @return a string
*/
#define GetLastDynLibError() dlerror()

#endif /* __unix // guard against mis-compilation */

#endif

/**
* Decrements the reference count of the loaded dynamic-link library
* @param Handle to the loaded library
* @return BOOL If the function succeeds, the return value is nonzero
*/
BOOL FreeDynLibrary(DynLibHandle hInstance);

/**
* Retrieves the address of an exported function
* @param Handle to the loaded library
* @param string that specifies the function
* @return
*/
DynLibFuncPtr GetDynLibFuncPtr(DynLibHandle hInstance, const char *funcName);

/**
* Build name of dynamic library based on module name
* @param[in] module name
* @param[in] generated dynamic lib name type
* @return name of dynamic library
*/
wchar_t* buildModuleDynLibraryNameW(const wchar_t* _pwstModuleName, dynlib_name_format _iType);
char* buildModuleDynLibraryName(const char* _pstModuleName, dynlib_name_format _iType);

#endif /* __DYNAMICLIBRARY_H__ */
/*---------------------------------------------------------------------------*/
