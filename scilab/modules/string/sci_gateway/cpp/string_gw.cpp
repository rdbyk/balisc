/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

//for Visual Leak Detector in debug compilation mode
//#define DEBUG_VLD
#if defined(DEBUG_VLD) && defined(_DEBUG)
#include <vld.h>
#endif


#include "string_gw.hxx"
#include "context.hxx"
#include "function.hxx"

extern "C"
{
#include "sci_malloc.h"
}

wchar_t* StringModule::pwstToken = NULL;
wchar_t StringModule::Name[] = L"string";

int StringModule::Load()
{
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"grep", &sci_grep, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"stripblanks", &sci_stripblanks, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"regexp", &sci_regexp, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"part", &sci_part, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"length", &sci_length, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strindex", &sci_strindex, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strsubst", &sci_strsubst, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strsplit", &sci_strsplit, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"ascii", &sci_ascii, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strcat", &sci_strcat, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"string", &sci_string, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"convstr", &sci_convstr, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strncpy", &sci_strncpy, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strrchr", &sci_strrchr, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strchr", &sci_strchr, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strstr", &sci_strstr, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strrev", &sci_strrev, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strtod", &sci_strtod, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"tokens", &sci_tokens, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strcmp", &sci_strcmp, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"isletter", &sci_isletter, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strcspn", &sci_strcspn, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strtok", &sci_strtok, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"strspn", &sci_strspn, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"isalphanum", &sci_isalphanum, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"isdigit", &sci_isdigit, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"isascii", &sci_isascii, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"isnum", &sci_isnum, StringModule::Name));
    symbol::Context::getInstance()->addFunction(types::Function::createFunction(L"emptystr", &sci_emptystr, StringModule::Name));
    return 1;
}

wchar_t* StringModule::setToken(wchar_t* _base)
{
    deleteToken();

    // clone because strtok is destructive:
    // it writes the L'\0' characters in the elements of the origin string.
    pwstToken = os_wcsdup(_base);
    return pwstToken;
}

void StringModule::deleteToken()
{
    if (pwstToken)
    {
        FREE(pwstToken);
        pwstToken = NULL;
    }
}
