/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
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

#include <sstream>
#include "types.hxx"

namespace types
{

template <typename T>
T GenericType::DimsToString()
{
}

template <>
std::wstring GenericType::DimsToString<std::wstring>()
{
    std::wstring s;
    int n = getDims();
    int* d = getDimsArray();

    if (n > 0)
    {
        s.reserve(12 * n);
        s = std::to_wstring(d[0]);

        for (int i = 1; i < n; ++i)
        {
            s += L"x";
            s += std::to_wstring(d[i]);
        }
    }

    return s;
}

template <>
std::string GenericType::DimsToString<std::string>()
{
    std::string s;
    int n = getDims();
    int* d = getDimsArray();

    if (n > 0)
    {
        s.reserve(12 * n);
        s = std::to_string(d[0]);

        for (int i = 1; i < n; ++i)
        {
            s += "x";
            s += std::to_string(d[i]);
        }
    }

    return s;
}

bool GenericType::isIdentity(void)
{
    int i = getDims();

    while (i && m_piDims[--i] == -1);

    return !i;
}

int GenericType::getVarMaxDim(int _iCurrentDim, int _iMaxDim)
{
    if (m_iDims != 0)
    {
         // normal view, all dimensions are used
        int iVarMaxDim = m_piDims[_iCurrentDim];

        if (_iMaxDim < m_iDims)
        {
            if (_iCurrentDim + 1 == _iMaxDim)
            {
                // view as "vector", not all dimensions are used
                for (int i = _iCurrentDim + 1; i < m_iDims; ++i)
                {
                    iVarMaxDim *= m_piDims[i];
                }
            }
        }
        else if (_iCurrentDim >= m_iDims)
        {
            iVarMaxDim = 1;
        }

        return iVarMaxDim;
    }
    else
    {
        // for non ArrayOf derived types, like list, tlist, mlist
        return getSize();
    }
}
}
