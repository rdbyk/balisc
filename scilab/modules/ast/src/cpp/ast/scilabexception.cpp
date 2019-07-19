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

#include <stdarg.h>

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

ScilabException::ScilabException(const std::string& _stErrorMesssage)
{
    wchar_t* pwst = to_wide_string(_stErrorMesssage.c_str());
    createScilabException(pwst, 999, Location());
    FREE(pwst);
}

InternalError::InternalError(const std::wstring& _wstErrorMesssage)
{
    createScilabException(_wstErrorMesssage, 999, Location());
    setLastError(m_iErrorNumber, _wstErrorMesssage.c_str(), m_ErrorLocation.first_line, NULL);
}

InternalError::InternalError(std::string _stErrorMesssage)
{
    wchar_t* pwst = to_wide_string(_stErrorMesssage.c_str());
    createScilabException(pwst, 999, Location());
    FREE(pwst);
    setLastError(999, m_wstErrorMessage.c_str(), 0, NULL);
}

InternalError::InternalError(const std::string _stErrorMesssage, int _iErrorNumber, const Location& _ErrorLocation)
{
    wchar_t* pwst = to_wide_string(_stErrorMesssage.c_str());
    createScilabException(pwst, 999, Location());
    FREE(pwst);
    setLastError(_iErrorNumber, m_wstErrorMessage.c_str(), _ErrorLocation.first_line, NULL);
}

InternalError::InternalError(const std::wstring& _wstErrorMesssage, int _iErrorNumber, const Location& _ErrorLocation)
{
    createScilabException(_wstErrorMesssage, _iErrorNumber, _ErrorLocation);
    setLastError(_iErrorNumber, _wstErrorMesssage.c_str(), _ErrorLocation.first_line, NULL);
}

InternalError::InternalError(int _iErrorNumber)
{
    wchar_t* pwst = to_wide_string(ErrorMessageByNumber(_iErrorNumber));
    createScilabException(pwst, _iErrorNumber, Location());
    FREE(pwst);
    setLastError(m_iErrorNumber, m_wstErrorMessage.c_str(), m_ErrorLocation.first_line, NULL);
}

InternalError::InternalError(int _iErrorNumber, const Location& _ErrorLocation, ...)
{
    int retval = 0;
    char* stptr = NULL;
    va_list ap;

    char *errmsg = ErrorMessageByNumber(_iErrorNumber);

    va_start(ap, _ErrorLocation);

    if (errmsg)
    {
        retval = vasprintf(&stptr, errmsg, ap);
    }
    else
    {
        const char* fmt = va_arg(ap, const char*);
        retval = vasprintf(&stptr, fmt, ap);
    }

    va_end(ap);

    if (retval < 0)
    {
        setLastError(_iErrorNumber, NULL, 0, NULL);
    }
    else
    {
        wchar_t* pwstError = to_wide_string(stptr);
        FREE(stptr);
        createScilabException(pwstError, _iErrorNumber, _ErrorLocation);
        FREE(pwstError);
        setLastError(m_iErrorNumber, m_wstErrorMessage.c_str(), m_ErrorLocation.first_line, NULL);
    }
}

}
