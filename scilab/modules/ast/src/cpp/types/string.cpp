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
#include <iomanip>
#include "core_math.h"
#include "string.hxx"
#include "stringexp.hxx"
#include "tostring_common.hxx"
#include "configvariable.hxx"
#include "type_traits.hxx"

extern "C"
{
#include "charEncoding.h"
#include "os_string.h"
#include "sci_malloc.h"
}

#define SIZE_BETWEEN_TWO_STRING_VALUES  2
#define SPACE_BETWEEN_TWO_STRING_VALUES L"  "

namespace types
{
String::~String()
{
    if (isDeletable() == true)
    {
        deleteAll();
    }
#ifndef NDEBUG
    Inspector::removeItem(this);
#endif
}

String::String(int _iDims, const int* _piDims)
{
    wchar_t** pwsData = NULL;
    create(_piDims, _iDims, &pwsData, NULL);
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

String::String(const wchar_t* _pwstData)
{
    static int piDims[] = {1, 1};
    wchar_t** pwsData = NULL;
    create(piDims, 2, &pwsData, NULL);
    set(0, _pwstData);
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

String::String(const char *_pstData)
{
    static int piDims[] = {1, 1};
    wchar_t** pwsData = NULL;
    create(piDims, 2, &pwsData, NULL);
    wchar_t* data = to_wide_string(const_cast<char*>(_pstData));
    set(0, data);
    FREE(data);
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

String::String(int _iRows, int _iCols)
{
    wchar_t** pwsData = NULL;
    int piDims[] = {_iRows, _iCols};
    create(piDims, 2, &pwsData, NULL);
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

String::String(int _iRows, int _iCols, wchar_t const* const* _pstData)
{
    wchar_t** pwsData = NULL;
    int piDims[] = {_iRows, _iCols};
    create(piDims, 2, &pwsData, NULL);
    for (int i = 0 ; i < m_iSize ; i++)
    {
        set(i, _pstData[i]);
    }
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

String* String::clone()
{
    String *pstClone = new String(getDims(), getDimsArray());
    pstClone->set(m_pRealData);
    return pstClone;
}

void String::deleteString(int _iPos)
{
    wchar_t* str = m_pRealData[_iPos];

    if (str && str != String::nullValue())
    {
        FREE(str);
        str = NULL;
    }
}

void String::deleteAll()
{
    if (m_pRealData)
    {
        for (int i = 0 ; i < m_iSizeMax ; i++)
        {
            deleteString(i);
        }

        delete[] m_pRealData;
        m_pRealData = NULL;
    }
}

void String::deleteImg()
{
    return;
}

bool String::subMatrixToString(std::wostringstream& ostr, int* _piDims, int /*_iDims*/)
{
    int iPrecision = ConfigVariable::getFormatSize();
    int iLineLen = ConfigVariable::getConsoleWidth();
    int iMaxLines = ConfigVariable::getConsoleLines();
    int iCurrentLine = 0;

    // less the two "!" (or two " " in scalar case)
    // for iLineLen = 50 we will write "!48char!"
    int iStrMaxSize = iLineLen - 2;

    if (isScalar())
    {
        int iMaxLen = 0;
        _piDims[0]  = 0;
        _piDims[1]  = 0;

        int iPos = getIndex(_piDims);
        wchar_t* wcsStr = get(iPos);
        int iCurLen = static_cast<int>(wcslen(wcsStr));
        iMaxLen = std::max(iMaxLen, iCurLen);
        iMaxLen = std::min(iMaxLen, iStrMaxSize);

        if (iCurLen > iMaxLen)
        {
            int iStrPos = 0;
            while (iCurLen > iStrMaxSize)
            {
                ostr << L" ";
                ostr.write(wcsStr + iStrPos, iStrMaxSize);
                ostr << L" \n";
                iCurLen -= iStrMaxSize;
                iStrPos += iStrMaxSize;
            }

            ostr << L" ";
            configureStream(&ostr, iStrMaxSize, iPrecision, ' ');
            ostr << std::left << wcsStr + iStrPos << std::resetiosflags(std::ios::adjustfield);
        }
        else
        {
            ostr << L" " << wcsStr << L"\n";
        }
    }
    else if (m_iCols == 1)
    {
        std::wstring spaces(L"");

        // compte max string size
        int iMaxLen = 0;
        for (int i = 0; i < m_iRows; i++)
        {
            _piDims[1] = 0;
            _piDims[0] = i;
            int iPos = getIndex(_piDims);
            iMaxLen = std::max(iMaxLen, static_cast<int>(wcslen(get(iPos))));
            iMaxLen = std::min(iMaxLen, iStrMaxSize);
        }

        int iEmptyLineSize = iMaxLen;
        if (iMaxLen != iStrMaxSize)
        {
            // count SPACE_BETWEEN_TWO_STRING_VALUES size in padding of empty line
            // only if all lines have not a size greater than max size of a line.
            iEmptyLineSize += SIZE_BETWEEN_TWO_STRING_VALUES;
            spaces = SPACE_BETWEEN_TWO_STRING_VALUES;
        }

        for (int i = m_iRows1PrintState; i < m_iRows; i++)
        {
            iCurrentLine += 2;
            if ((iMaxLines == 0 && iCurrentLine >= MAX_LINES) || (iMaxLines != 0 && iCurrentLine >= iMaxLines))
            {
                m_iRows1PrintState = i;
                return false;
            }

            _piDims[1] = 0;
            _piDims[0] = i;
            int iPos = getIndex(_piDims);
            wchar_t* wcsStr = get(iPos);
            int iCurLen = static_cast<int>(wcslen(wcsStr));

            ostr << L"!";
            if (iCurLen > iMaxLen)
            {
                int iStrPos = 0;
                while (iCurLen > iStrMaxSize)
                {
                    ostr.write(wcsStr + iStrPos, iStrMaxSize);
                    ostr << L"!\n!";
                    iCurLen -= iStrMaxSize;
                    iStrPos += iStrMaxSize;
                }

                configureStream(&ostr, iStrMaxSize, iPrecision, ' ');
                ostr << std::left << wcsStr + iStrPos;
            }
            else
            {
                configureStream(&ostr, iMaxLen, iPrecision, ' ');
                ostr << std::left << wcsStr << spaces;
            }

            ostr << L"!\n";

            if ((i + 1) < m_iSize)
            {
                //for all but last one
                ostr << L"!";
                configureStream(&ostr, iEmptyLineSize, iPrecision, ' ');
                ostr << std::left << L" ";
                ostr << L"!\n";
            }
        }
        ostr << std::resetiosflags(std::ios::adjustfield);
    }
    else if (m_iRows == 1)
    {
        std::wostringstream ostemp;
        int iLastVal = m_iCols1PrintState;

        for (int i = m_iCols1PrintState; i < m_iCols; i++)
        {
            _piDims[0] = 0;
            _piDims[1] = i;
            int iPos = getIndex(_piDims);

            int iLen = 0;
            int iCurLen = static_cast<int>(wcslen(get(iPos)));
            iLen = iCurLen + SIZE_BETWEEN_TWO_STRING_VALUES + static_cast<int>(ostemp.str().size());
            if (iLen > iLineLen && iLastVal != i)
            {
                //Max length, new line
                iCurrentLine += 4; //"column x to Y" + empty line + value + empty line
                if ((iMaxLines == 0 && iCurrentLine >= MAX_LINES) || (iMaxLines != 0 && iCurrentLine >= iMaxLines))
                {
                    m_iCols1PrintState = iLastVal;
                    return false;
                }

                addColumnString(ostr, iLastVal + 1, i);
                ostr << L"!" << ostemp.str() << L"!\n";
                ostemp.str(L"");
                iLastVal = i;
            }

            // Manage case where string length is greater than max line size.
            if (iStrMaxSize < iCurLen)
            {
                wchar_t* wcsStr = get(iPos);
                int iStrPos = 0;
                while (iCurLen > iStrMaxSize) // -2 because of two "!"
                {
                    ostemp.write(wcsStr + iStrPos, iStrMaxSize);
                    ostemp << L"!\n!";
                    iCurLen -= iStrMaxSize;
                    iStrPos += iStrMaxSize;
                }

                configureStream(&ostemp, iStrMaxSize, iPrecision, ' ');
                ostemp << std::left << wcsStr + iStrPos;
            }
            else
            {
                configureStream(&ostemp, iCurLen + 2, iPrecision, ' ');
                ostemp << std::left << get(iPos);
            }
        }

        if (iLastVal != 0)
        {
            addColumnString(ostr, iLastVal + 1, m_iCols);
        }

        ostr << L"!" << ostemp.str() << L"!\n" << std::resetiosflags(std::ios::adjustfield);
    }
    else //Matrix
    {
        std::wostringstream ostemp;
        int iLen = 0;
        int iLastCol = m_iCols1PrintState;

        //Array with the max printed size of each col
        int *piSize = new int[m_iCols]();

        for (int iCols1 = m_iCols1PrintState; iCols1 < m_iCols; iCols1++)
        {
            std::wstring spaces(L"");
            for (int iRows1 = 0; iRows1 < m_iRows; iRows1++)
            {
                _piDims[1] = iCols1;
                _piDims[0] = iRows1;
                int iPos = getIndex(_piDims);
                piSize[iCols1] = std::max(piSize[iCols1], static_cast<int>(wcslen(get(iPos))));
                piSize[iCols1] = std::min(piSize[iCols1], iStrMaxSize);
            }

            int iEmptyLineSize = piSize[iLastCol];
            if (piSize[iLastCol] != iStrMaxSize)
            {
                // count SPACE_BETWEEN_TWO_STRING_VALUES size in padding of empty line
                // only if all lines have not a size greater than max size of a line.
                iEmptyLineSize += SIZE_BETWEEN_TWO_STRING_VALUES;
                spaces = SPACE_BETWEEN_TWO_STRING_VALUES;
            }

            if (iLen + piSize[iCols1] > iLineLen && iLastCol != iCols1)
            {
                //find the limit, print this part
                for (int iRows2 = m_iRows2PrintState; iRows2 < m_iRows; iRows2++)
                {
                    iCurrentLine += 2;
                    if ((iMaxLines == 0 && iCurrentLine >= MAX_LINES) ||
                            ( (iMaxLines != 0 && iCurrentLine + 3 >= iMaxLines && iRows2 == m_iRows2PrintState) ||
                              (iMaxLines != 0 && iCurrentLine + 1 >= iMaxLines && iRows2 != m_iRows2PrintState)))
                    {
                        if (m_iRows2PrintState == 0 && iRows2 != 0)
                        {
                            //add header
                            addColumnString(ostr, iLastCol + 1, iCols1);
                        }
                        ostr << ostemp.str();
                        m_iRows2PrintState = iRows2;
                        m_iCols1PrintState = iLastCol;
                        delete[] piSize;
                        return false;
                    }

                    ostemp << L"!";
                    for (int iCols2 = iLastCol; iCols2 < iCols1; iCols2++)
                    {
                        _piDims[0] = iRows2;
                        _piDims[1] = iCols2;
                        int iPos = getIndex(_piDims);
                        wchar_t* wcsStr = get(iPos);
                        int iLenStr = static_cast<int>(wcslen(wcsStr));

                        // Manage case where string length is greater than max line size.
                        if (iLenStr > iStrMaxSize)
                        {
                            int iStrPos = 0;
                            while (iLenStr > iStrMaxSize)
                            {
                                ostemp.write(wcsStr + iStrPos, iStrMaxSize);
                                ostemp << L"!\n!";
                                iLenStr -= iStrMaxSize;
                                iStrPos += iStrMaxSize;
                            }

                            configureStream(&ostemp, iStrMaxSize, iPrecision, ' ');
                            ostemp << std::left << wcsStr + iStrPos;
                        }
                        else
                        {
                            configureStream(&ostemp, piSize[iCols2], iPrecision, ' ');
                            ostemp << std::left << get(iPos) << spaces;
                        }
                    }
                    ostemp << L"!\n";

                    if ((iRows2 + 1) != m_iRows)
                    {
                        ostemp << L"!";
                        // -2 because of two "!"
                        configureStream(&ostemp, iEmptyLineSize, iPrecision, ' ');
                        ostemp << std::left << L" ";
                        ostemp << L"!\n";
                    }
                }

                iLen = 0;
                iCurrentLine += 2;
                if (m_iRows2PrintState == 0)
                {
                    iCurrentLine += 3;
                    addColumnString(ostr, iLastCol + 1, iCols1);
                }

                ostr << ostemp.str();
                ostemp.str(L"");
                iLastCol = iCols1;
                m_iRows2PrintState = 0;
                m_iCols1PrintState = 0;
            }
            iLen += piSize[iCols1] + SIZE_BETWEEN_TWO_STRING_VALUES;
        }

        for (int iRows2 = m_iRows2PrintState; iRows2 < m_iRows; iRows2++)
        {
            std::wstring spaces(L"");
            iCurrentLine += 2;
            if ((iMaxLines == 0 && iCurrentLine >= MAX_LINES) || (iMaxLines != 0 && iCurrentLine >= iMaxLines))
            {
                if (m_iRows2PrintState == 0 && iLastCol != 0)
                {
                    //add header
                    addColumnString(ostr, iLastCol + 1, m_iCols);
                }

                ostr << ostemp.str();
                m_iRows2PrintState = iRows2;
                m_iCols1PrintState = iLastCol;
                delete[] piSize;
                return false;
            }

            int iEmptyLineSize = piSize[iLastCol];
            if (piSize[iLastCol] != iStrMaxSize)
            {
                // count SPACE_BETWEEN_TWO_STRING_VALUES size in padding of empty line
                // only if all lines have not a size greater than max size of a line.
                iEmptyLineSize += SIZE_BETWEEN_TWO_STRING_VALUES;
                spaces = SPACE_BETWEEN_TWO_STRING_VALUES;
            }


            ostemp << L"!";
            iLen = 0;
            for (int iCols2 = iLastCol; iCols2 < m_iCols; iCols2++)
            {
                _piDims[0] = iRows2;
                _piDims[1] = iCols2;
                int iPos = getIndex(_piDims);
                wchar_t* wcsStr = get(iPos);
                int iLenStr = static_cast<int>(wcslen(wcsStr));

                // Manage case where string length is greater than max line size.
                if (iStrMaxSize < iLenStr)
                {
                    int iStrPos = 0;
                    while (iLenStr > iStrMaxSize)
                    {
                        ostemp.write(wcsStr + iStrPos, iStrMaxSize);
                        ostemp << L"!\n!";
                        iLenStr -= iStrMaxSize;
                        iStrPos += iStrMaxSize;
                    }

                    configureStream(&ostemp, iStrMaxSize, iPrecision, ' ');
                    ostemp << wcsStr + iStrPos << std::left;
                    iLen = iStrMaxSize;
                }
                else
                {
                    configureStream(&ostemp, piSize[iCols2], iPrecision, ' ');
                    ostemp << std::left << get(iPos) << spaces;
                    iLen += piSize[iCols2] + static_cast<int>(spaces.size());
                }
            }
            ostemp << L"!\n";

            if ((iRows2 + 1) != m_iRows)
            {
                ostemp << L"!";
                configureStream(&ostemp, iLen, iPrecision, ' ');
                ostemp << std::left << L" ";
                ostemp << L"!\n";
            }
        }

        if (m_iRows2PrintState == 0 && iLastCol != 0)
        {
            addColumnString(ostr, iLastCol + 1, m_iCols);
        }
        ostr << ostemp.str() << std::resetiosflags(std::ios::adjustfield);
        delete[] piSize;
    }
    std::flush(ostr);
    
    return true;
}

std::wstring String::toStringInLine()
{
    if (isScalar())
    {
        // FIXME: an appropriate iWidth should be provided by the caller
        // this would allow to take the length of field names into account
        int iWidth = ConfigVariable::getConsoleWidth() - 12;
        wchar_t* s = getFirst();

        if (wcslen(s) <= iWidth)
        {
            std::wstring ws;
            ws.reserve(iWidth + 2);
            ws += L"\"";
            ws += s;
            ws += L"\"";
            return ws;
        }
        else
        {
            std::wstring ws(s, iWidth - 2);
            ws.reserve(iWidth + 2);
            ws = L"\"" + ws;
            ws += L"...";
            return ws;
        }
    }
    else
    {
        return ArrayOf::toStringInLine();
    }
}

bool String::operator==(const InternalType& it)
{
    if (const_cast<InternalType&>(it).isString() == false)
    {
        return false;
    }

    String* pS = const_cast<InternalType&>(it).getAs<types::String>();

    if (pS->getRows() != m_iRows || pS->getCols() != m_iCols)
    {
        return false;
    }

    wchar_t **p1 = get();
    wchar_t **p2 = pS->get();

    for (int i = 0; i < m_iSize; i++)
    {
        if (wcscmp(p1[i], p2[i]) != 0)
        {
            return false;
        }
    }
    return true;
}

bool String::operator!=(const InternalType& it)
{
    return !(*this == it);
}

static wchar_t* null = L"";
wchar_t* String::nullValue()
{
    // The null value pointer is shared to speed up "" assignement
    // Empty strings creation can then be done without memory allocation
    return null;
}

String* String::createEmpty(int _iDims, int* _piDims, bool /*_bComplex*/)
{
    return new String(_iDims, _piDims);
}

wchar_t* String::copyValue(wchar_t* _pwstData)
{
    if (_pwstData == nullValue())
    {
        return nullValue();
    }

    try
    {
        return os_wcsdup(_pwstData);
    }
    catch (std::bad_alloc & /*e*/)
    {
        char message[bsiz];
        os_sprintf(message, _("Can not allocate data.\n"));
        throw ast::InternalError(message);
    }

    return NULL;
}

wchar_t* String::copyValue(const wchar_t* _pwstData)
{
    if (_pwstData == nullValue())
    {
        return nullValue();
    }

    return os_wcsdup(_pwstData);
}

void String::deleteData(wchar_t* data)
{
    if (data && data != nullValue())
    {
        // data are always allocated using C-like malloc API
        FREE(data);
    }
}

void String::set(int _iPos, const wchar_t* _pwstData)
{
    deleteString(_iPos);
    m_pRealData[_iPos] = copyValue(_pwstData);
}

void String::set(int _iRows, int _iCols, const wchar_t* _pwstData)
{
    set(_iCols * getRows() + _iRows, _pwstData);
}

void String::set(const wchar_t* const* _pwstData)
{
    for (int i = 0; i < m_iSize; ++i)
    {
        deleteString(i);
        m_pRealData[i] = copyValue(_pwstData[i]);
    }
}

void  String::set(int _iPos, const char* _pcData)
{
    wchar_t* w = to_wide_string(_pcData);
    set(_iPos, w);
    FREE(w);
}

void String::set(int _iRows, int _iCols, const char* _pcData)
{
    set(_iCols * getRows() + _iRows, _pcData);
}

void String::set(const char* const* _pstrData)
{
    for (int i = 0; i < m_iSize; ++i)
    {
        set(i, _pstrData[i]);
    }
}

wchar_t** String::allocData(int _iSize)
{
    try
    {
        return new wchar_t*[_iSize]();
    }
    catch (std::bad_alloc & /*e*/)
    {
        char message[bsiz];
        os_sprintf(message, _("Can not allocate %.2f MB memory.\n"), (double)(_iSize * sizeof(char*)) / 1.e6);
        throw ast::InternalError(message);
    }
}

ast::Exp* String::getExp(const Location& loc)
{
    return new ast::StringExp(loc, this);
}

bool String::transpose(InternalType *& out)
{
    return type_traits::transpose(*this, out);
}

}
