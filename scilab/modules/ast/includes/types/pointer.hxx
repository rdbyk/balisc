/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#ifndef __POINTER_HXX__
#define __POINTER_HXX__

#include "user.hxx"

namespace types
{
class Pointer : public UserType
{
public:
    Pointer()
    {
        m_pvData = NULL;
        m_cplx = false;
    }

    Pointer(void* _pvData)
    {
        m_pvData = _pvData;
        m_cplx = false;
    }

    Pointer(int _rows, int _cols, void* _pvData, bool _complex = false)
    {
        m_iRows = _rows;
        m_iCols = _cols;
        m_pvData = _pvData;
        m_cplx = _complex;
    }

    virtual ~Pointer() {}

    bool hasToString()
    {
        return false;
    }

    std::wstring getTypeStr() const
    {
        return L"pointer";
    }

    std::wstring getShortTypeStr() const
    {
        return L"ptr";
    }

    bool isPointer(void)
    {
        return true;
    }

    bool isComplex(void)
    {
        return m_cplx;
    }

    bool toString(std::wostringstream& ostr)
    {
        return true;
    }

    Pointer* clone()
    {
        return new Pointer(getRows(), getCols(), m_pvData, m_cplx);
    }

    void* get()
    {
        return m_pvData;
    }

    void set(void* _pvData)
    {
        m_pvData = _pvData;
    }

    virtual bool isAssignable(void)
    {
        return true;
    }

protected:

    void* m_pvData;
    bool m_cplx;
};
}

#endif /* !__POINTER_HXX__ */
