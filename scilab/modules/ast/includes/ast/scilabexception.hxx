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

enum ExceptionType
{
    TYPE_ERROR,
    TYPE_EXCEPTION
};

class ScilabException : public std::exception
{
public :
    ScilabException();
    ScilabException(const std::wstring& _wstErrorMesssage);
    ScilabException(const std::string& _stErrorMesssage);
    ScilabException(const std::wstring& _wstErrorMesssage, int _iErrorNumber, const Location& _ErrorLocation);

    virtual ~ScilabException() throw() {};

    void SetErrorMessage(const std::wstring& _wstErrorMesssage)
    {
        m_wstErrorMessage = _wstErrorMesssage;
    }

    std::wstring GetErrorMessage(void) const
    {
        return m_wstErrorMessage;
    }

    void SetErrorNumber(int _iErrorNumber)
    {
        m_iErrorNumber = _iErrorNumber;
    }

    int GetErrorNumber(void) const
    {
        return m_iErrorNumber;
    }

    void SetErrorLocation(const Location& _ErrorLocation)
    {
        m_ErrorLocation = _ErrorLocation;
    }

    const Location& GetErrorLocation(void) const
    {
        return m_ErrorLocation;
    }

    void SetErrorType(ExceptionType _type)
    {
        m_type = _type;
    }

    ExceptionType GetErrorType(void)
    {
        return m_type;
    }

protected :
    void createScilabException(const std::wstring& _wstErrorMessage, int _iErrorNumber, const Location& _ErrorLocation);
    std::wstring m_wstErrorMessage;
    int m_iErrorNumber;
    Location m_ErrorLocation;
    ExceptionType m_type;
};

class InternalError : public ScilabException
{
public :
    InternalError(const std::wstring& _wstErrorMesssage);
    InternalError(std::string _stErrorMesssage);
    InternalError(const std::wstring& _wstErrorMesssage, int _iErrorNumber, const Location& _ErrorLocation);
};

class InternalRowColDimensionsError : public InternalError
{
public:
    InternalRowColDimensionsError();
    InternalRowColDimensionsError(const Location& loc);
};

class InternalInvalidIndexError : public InternalError
{
public:
    InternalInvalidIndexError();
    InternalInvalidIndexError(const Location& loc);
};

class InternalProtectedVariableError : public InternalError
{
public:
    InternalProtectedVariableError(const Location& loc);
};

class InternalIncompatibleOutputError : public InternalError
{
public:
    InternalIncompatibleOutputError(const Location& loc);
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
