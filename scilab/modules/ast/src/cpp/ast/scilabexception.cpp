// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
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

#include "localization.hxx"
#include "scilabexception.hxx"

extern "C"
{
#include "lasterror.h"
#include "sci_malloc.h"
#include "localization.h"
}

#include "errmsgs.h"

namespace ast
{

ScilabException::ScilabException() : m_wstErrorMessage(), m_iErrorNumber(0), m_ErrorLocation(), m_type(TYPE_ERROR)
{
}

ScilabException::ScilabException(const std::wstring& _wstErrorMesssage)
{
    m_type = TYPE_EXCEPTION;
    createScilabException(_wstErrorMesssage, 999, Location());
}

ScilabException::ScilabException(const std::string& _stErrorMesssage)
{
    m_type = TYPE_EXCEPTION;
    wchar_t* pwst = to_wide_string(_stErrorMesssage.c_str());
    createScilabException(pwst, 999, Location());
    FREE(pwst);
}

ScilabException::ScilabException(const std::wstring& _wstErrorMesssage, int _iErrorNumber, const Location& _ErrorLocation)
{
    m_type = TYPE_EXCEPTION;
    createScilabException(_wstErrorMesssage, _iErrorNumber, _ErrorLocation);
}

void ScilabException::createScilabException(const std::wstring& _wstErrorMessage, int _iErrorNumber, const Location& _ErrorLocation)
{
    m_wstErrorMessage = _wstErrorMessage;
    m_iErrorNumber = _iErrorNumber;
    m_ErrorLocation = _ErrorLocation;
}

InternalError::InternalError(const std::wstring& _wstErrorMesssage) : ScilabException(_wstErrorMesssage)
{
    m_type = TYPE_ERROR;
    setLastError(999, _wstErrorMesssage.c_str(), 0, NULL);
}

InternalError::InternalError(std::string _stErrorMesssage) : ScilabException(_stErrorMesssage)
{
    m_type = TYPE_ERROR;
    setLastError(999, m_wstErrorMessage.c_str(), 0, NULL);
}

InternalError::InternalError(const std::wstring& _wstErrorMesssage, int _iErrorNumber, const Location& _ErrorLocation) : ScilabException(_wstErrorMesssage, _iErrorNumber, _ErrorLocation)
{
    m_type = TYPE_ERROR;
    setLastError(_iErrorNumber, _wstErrorMesssage.c_str(), _ErrorLocation.first_line, NULL);
}

InternalRowColDimensionsError::InternalRowColDimensionsError() : InternalError(_W(ErrorMessageByNumber(3)))
{
}

InternalRowColDimensionsError::InternalRowColDimensionsError(const Location& loc) : InternalError(_W(ErrorMessageByNumber(3)), 3, loc) 
{
}

InternalInvalidIndexError::InternalInvalidIndexError() : InternalError(_W(ErrorMessageByNumber(2)))
{
}

InternalInvalidIndexError::InternalInvalidIndexError(const Location& loc) : InternalError(_W(ErrorMessageByNumber(2)), 2, loc)
{
}

InternalProtectedVariableError::InternalProtectedVariableError(const Location& loc) : InternalError(_W(ErrorMessageByNumber(4)), 4, loc)
{
}

InternalIncompatibleOutputError::InternalIncompatibleOutputError(const Location& loc) : InternalError(_W(ErrorMessageByNumber(5)), 5, loc)
{
}

}
