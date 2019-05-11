/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2010 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#ifndef __TYPES_HXX__
#define __TYPES_HXX__

#include <vector>
#include <iostream>
#include <string>
#include "internal.hxx"

extern "C"
{
#include "core_math.h"
}

#define MAX_DIMS 32
namespace types
{
/*
** Type
*/
class GenericType : public InternalType
{
protected :
    union {
        struct {
            int m_iRows;
            int m_iCols;
        };
        int m_piDims[MAX_DIMS];
    };
    int                         m_iSize;
    int                         m_iDims;
    int                         m_iSizeMax;

    GenericType() : InternalType(), m_iRows(0), m_iCols(0), m_iSize(0), m_iSizeMax(0), m_iDims(0) {}

public :
    virtual                     ~GenericType() {}

    virtual bool                isComplex()
    {
        return false;
    }

    inline bool isScalar()
    {
        if (m_iDims == 2 && m_iRows == 1 && m_iCols == 1)
        {
            return true;
        }
        return false;
    }

    inline bool isVector() //only one dim must be != 1
    {
        int count = 2;

        int i = 0;
        while (i < m_iDims && count)
        {
            count -= (m_piDims[i++] != 1);
        }

        return count;
    }

    /*commun functions*/
    virtual int                  getCols()
    {
        return m_iCols;
    }

    virtual int                  getRows()
    {
        return m_iRows;
    }

    virtual int                  getSize() const
    {
        return m_iSize;
    }

    virtual int                  getDims()
    {
        return m_iDims;
    }

    virtual int*                 getDimsArray()
    {
        return m_piDims;
    }

    int                         getVarMaxDim(int _iCurrentDim, int _iMaxDim);

    template <typename T> T DimsToString();

    inline bool                 isGenericType()
    {
        return true;
    }

    virtual GenericType*        getColumnValues(int /*_iPos*/)
    {
        return NULL;
    }

    bool                        isIdentity(void);
    virtual bool                isAssignable(void)
    {
        return true;
    }

    virtual ScilabType          getType(void)
    {
        return ScilabGeneric;
    }

    /* return type as string ( double, int, cell, list, ... )*/
    virtual std::wstring        getTypeStr() const
    {
        return L"generictype";
    }
    /* return type as short string ( s, i, ce, l, ... )*/
    virtual std::wstring        getShortTypeStr() const
    {
        return L"";
    }

    virtual GenericType*        clone(void)
    {
        return NULL;
    }

    virtual GenericType*        resize(int* /*_piDims*/, int /*_iDims*/)
    {
        return NULL;
    }

    virtual GenericType*        resize(int /*_iNewRows*/, int /*_iNewCols*/)
    {
        return NULL;
    }

    virtual GenericType*        reshape(int* /*_piDims*/, int /*_iDims*/)
    {
        return NULL;
    }

    virtual GenericType*        reshape(int /*_iNewRows*/, int /*_iNewCols*/)
    {
        return NULL;
    }

    virtual GenericType*        insert(typed_list* /*_pArgs*/, InternalType* /*_pSource*/)
    {
        return NULL;
    }

    virtual GenericType*        insertNew(typed_list* /*_pArgs*/)
    {
        return NULL;
    }

    virtual GenericType*        remove(typed_list* /*_pArgs*/)
    {
        return NULL;
    }

    virtual bool                extract(const std::wstring& /*name*/, InternalType *& /*out*/)
    {
        return false;
    }

    virtual InternalType*       extract(typed_list* /*_pArgs*/)
    {
        return NULL;
    }

};

}
#endif /* !__TYPES_HXX__ */
