// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
// 02110-1301, USA.

#ifndef __NAMEDARG_HXX__
#define __NAMEDARG_HXX__

#include "types.hxx"

namespace types
{
class NamedArg : public InternalType
{
public:
    NamedArg(std::wstring& n)
    { 
        m_wsName = n;
    }

    virtual ~NamedArg() { }

    NamedArg* clone()
    {
        return new NamedArg(m_wsName);
    }

    inline ScilabType getType(void)
    {
        return ScilabNamedArg;
    }

    inline ScilabId getId(void)
    {
        return IdNamedArg;
    }

    bool isNamedArg()
    {
        return true;
    }

    bool toString(std::wostringstream& ostr)
    {
        ostr << L"    <" << getTypeStr() << L":" << getName() << L">" << std::endl;
        return true;
    }

    virtual std::wstring getTypeStr() const
    {
        return L"namedarg";
    }
    
    virtual std::wstring getShortTypeStr() const
    {
        return L"X";
    }
    
    std::wstring getName() const
    {
        return m_wsName;
    }
private:
    std::wstring m_wsName;
};
}

#endif /* !__NAMEDARG_HXX__ */
