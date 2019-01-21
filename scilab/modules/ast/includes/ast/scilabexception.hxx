/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
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

#ifndef AST_SCILABEXCEPTION_HXX
#define AST_SCILABEXCEPTION_HXX

#include <string>
#include <stdexcept>
#include "location.hxx"

//disable warnings about exports STL items
#ifdef _MSC_VER
#pragma warning (disable : 4251)
#endif

namespace ast
{

class ScilabException : public std::exception
{
public :
    ScilabException() : m_wstErrorMessage(), m_iErrorNumber(0), m_ErrorLocation()
    {
    }

    ScilabException(const std::string& _stErrorMesssage);

    virtual ~ScilabException() throw() {};

    std::wstring GetErrorMessage(void) const
    {
        return m_wstErrorMessage;
    }

    void SetErrorLocation(const Location& _ErrorLocation)
    {
        m_ErrorLocation = _ErrorLocation;
    }

    const Location& GetErrorLocation(void) const
    {
        return m_ErrorLocation;
    }

protected :
    void createScilabException(const std::wstring& _wstErrorMessage, int _iErrorNumber, const Location& _ErrorLocation)
    {
        m_wstErrorMessage = _wstErrorMessage;
        m_iErrorNumber = _iErrorNumber;
        m_ErrorLocation = _ErrorLocation;
    }
    std::wstring m_wstErrorMessage;
    int m_iErrorNumber;
    Location m_ErrorLocation;
};

class InternalError : public ScilabException
{
public :
    InternalError(const std::wstring& _wstErrorMesssage);
    InternalError(std::string _stErrorMesssage);
    InternalError(const std::wstring& _wstErrorMesssage, int _iErrorNumber, const Location& _ErrorLocation);
    InternalError(int _iErrorNumber);
    InternalError(int _iErrorNumber, const Location& _ErrorLocation);
};

class InternalAbort : public ScilabException
{
public:
    InternalAbort() {}
};

class RecursionException : public ScilabException
{
public:
    RecursionException() {}
};
}
#endif // !AST_SCILABEXCEPTION_HXX
