/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009-2010 - DIGITEO - Antoine ELIAS
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

#ifndef __LISTUNDEFINED_HXX__
#define __LISTUNDEFINED_HXX__

#include "types.hxx"
#include "listoperation.hxx"

namespace types
{
class ListUndefined : public ListOperation
{
public :
    ListUndefined(): ListOperation() {};
    virtual                 ~ListUndefined();

    // FIXME : Should not return NULL;
    ListUndefined*          clone();

    ScilabType                getType(void);
    bool                    isListUndefined()
    {
        return true;
    }

    bool                    toString(std::wostringstream& ostr);

    /* return type as string ( double, int, cell, list, ... )*/
    virtual std::wstring    getTypeStr() const
    {
        return L"listundefined";
    }
};
}

#endif /* !__LISTUNDEFINED_HXX__ */
