/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2015 - Scilab Enterprises - Cedric Delamarre
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "readwrite.hxx"
#include "string.hxx"

extern "C"
{
#include "strlen.h"
#include "sci_malloc.h"
    extern int C2F(clunit)(int*, char const*, int*, int);
}
/*--------------------------------------------------------------------------*/
types::InternalType::ScilabType checkformat(const char* format)
{
    static const char type1[] =
    {
        'i', 'f', 'e',
        'd', 'g', 'l',
        'a', 'I', 'F',
        'E', 'D', 'G',
        'L', 'A'
    };
    static const types::InternalType::ScilabType type2[] =
    {
        types::InternalType::ScilabInt32, types::InternalType::ScilabDouble, types::InternalType::ScilabDouble,
        types::InternalType::ScilabDouble, types::InternalType::ScilabDouble, types::InternalType::ScilabBool,
        types::InternalType::ScilabString, types::InternalType::ScilabInt32, types::InternalType::ScilabDouble,
        types::InternalType::ScilabDouble, types::InternalType::ScilabDouble, types::InternalType::ScilabDouble,
        types::InternalType::ScilabBool, types::InternalType::ScilabString
    };

    int size = (int)balisc_strlen(format);
    bool isString = false;
    types::InternalType::ScilabType previousType = types::InternalType::ScilabNull;

    if (size < 2 || format[0] != '(' || format[size - 1] != ')')
    {
        return types::InternalType::ScilabNull;
    }

    for (int i = 1; i < size - 1; ++i)
    {
        char c = format[i];

        if (c == '\'')
        {
            isString = !isString;
        }

        //while we are in string continue
        if (isString)
        {
            continue;
        }

        for (int j = 0; j < sizeof(type1); j++)
        {
            if (c == type1[j])
            {
                if (previousType == types::InternalType::ScilabNull)
                {
                    previousType = type2[j];
                }

                //must have same format for all values
                if (type2[j] != previousType)
                {
                    return types::InternalType::ScilabNull;
                }

                break;
            }
        }
    }

    return previousType;
}
/*--------------------------------------------------------------------------*/
void closeFile(types::InternalType* _pIT, int _iID)
{
    if (_pIT->isString())
    {
        int piMode[2] = { 0, 0 };
        types::String* pSPath = _pIT->getAs<types::String>();
        char* pstFilename = wide_string_to_UTF8(pSPath->getFirst());
        int  close = -_iID;
        int iErr = C2F(clunit)(&close, pstFilename, piMode, (int)balisc_strlen(pstFilename));
        FREE(pstFilename);
    }
}
/*--------------------------------------------------------------------------*/
