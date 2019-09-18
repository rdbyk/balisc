/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 * Copyright (C) 2019 - Stéphane MOTTELET
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
#include <math.h>
#include "double.hxx"
#include "doubleexp.hxx"
#include "tostring_common.hxx"
#include "configvariable.hxx"
#include "type_traits.hxx"
#include "types_tools.hxx"

extern "C"
{
#include <stdio.h>
#include <string.h>
#include "elem_common.h"
#include "localization.h"
#include "charEncoding.h"
#include "os_string.h"
}

namespace types
{
Double* Double::Empty()
{
    return new Double(0, 0);
}

Double* Double::Identity(bool _bComplex)
{
    if (_bComplex)
    {
        return Double::Identity(1.0);
    }
    else
    {
        return Double::Identity(1.0, 1.0);
    }
}

Double* Double::Identity(double _pdblReal)
{
    double* pdbl = NULL;
    Double* pIdent = new Double(-1, -1, &pdbl);

    pdbl[0] = _pdblReal;

    return pIdent;
}

Double* Double::Identity(double _pdblReal, double _pdblImg)
{
    double* pdblR = NULL;
    double* pdblI = NULL;
    Double* pIdent = new Double(-1, -1, &pdblR, &pdblI);

    pdblR[0] = _pdblReal;
    pdblI[0] = _pdblImg;

    return pIdent;
}

Double* Double::Identity(int _iRows, int _iCols)
{
    double* pdbl = NULL;
    Double* pI = new Double(_iRows, _iCols, &pdbl);

    if (_iRows == -1 && _iCols == -1)
    {
        pdbl[0] = 1.0;
    }
    else
    {
        pI->setZeros();

        int n = std::min(_iRows, _iCols);
        for (int i = 0; i < n; ++i)
        {
            pdbl[i * (_iRows +  1)] = 1.0;
        }
    }

    return pI;
}

Double* Double::Identity(int _iDims, const int* _piDims)
{
    int iMinDim = *std::min_element(_piDims, _piDims + _iDims);

    if (iMinDim > 0)
    {
        Double* pI = new Double(_iDims, _piDims);
        double* pdbl = pI->get();
        int* piIndex = new int[_iDims];

        pI->setZeros();

        for (int i = 0; i < iMinDim; i++)
        {
            std::fill(piIndex, piIndex + _iDims, i);

            int index = getIndexWithDims(piIndex, _piDims, _iDims);
            pdbl[index] = 1.0;
        }

        delete[] piIndex;
        return pI;
    }
    else
    {
        return Double::Empty();
    }
}

Double* Double::Identity(int _iDims, const int* _piDims, double _dblReal)
{
    int iMinDim = *std::min_element(_piDims, _piDims + _iDims);

    if (iMinDim > 0)
    {
        Double* pI = new Double(_iDims, _piDims);
        double* pdbl = pI->get();
        int* piIndex = new int[_iDims];

        pI->setZeros();

        for (int i = 0; i < iMinDim; i++)
        {
            std::fill(piIndex, piIndex + _iDims, i);

            int index = getIndexWithDims(piIndex, _piDims, _iDims);
            pdbl[index] = _dblReal;
        }

        delete[] piIndex;
        return pI;
    }
    else
    {
        return Double::Empty();
    }
}

Double* Double::Identity(int _iDims, const int* _piDims, double _dblReal, double _dblImg)
{
    Double* pI = new Double(_iDims, _piDims, true);
    double* pdblReal = pI->get();
    double* pdblImg = pI->getImg();
    int iMinDim = *std::min_element(_piDims, _piDims + _iDims);
    int* piIndex = new int[_iDims];

    pI->setZeros();

    for (int i = 0; i < iMinDim; i++)
    {
        std::fill(piIndex, piIndex + _iDims, i);

        int index = getIndexWithDims(piIndex, _piDims, _iDims);
        pdblReal[index] = _dblReal;
        pdblImg[index] = _dblImg;
    }

    delete[] piIndex;
    return pI;
}

bool Double::isEmpty()
{
    if (getDims() == 2 && getSize() == 0)
    {
        return true;
    }
    return false;
}

Double::~Double()
{
    deleteAll();
#ifndef NDEBUG
    Inspector::removeItem(this);
#endif
}

Double::Double(int _iRows, int _iCols, bool _bComplex, bool _bZComplex)
{
    int piDims[2]   = {_iRows, _iCols};
    double *pReal   = NULL;
    double *pImg    = NULL;
    setViewAsZComplex(_bZComplex);
    if (_bComplex == false || _bZComplex)
    {
        create(piDims, 2, &pReal, NULL);
    }
    else
    {
        create(piDims, 2, &pReal, &pImg);
    }

    setViewAsInteger(false);
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Double::Double(double _dblReal)
{
    m_iDims = 2;
    m_iRows = 1;
    m_iCols = 1;
    m_iSize = 1;
    m_iSizeMax = m_iSize;
    m_pRealData = new double[1];
    setViewAsInteger(false);
    setViewAsZComplex(false);
    m_pRealData[0] = _dblReal;
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Double::Double(double _dblReal, double _dblImg)
{
    m_iDims = 2;
    m_iRows = 1;
    m_iCols = 1;
    m_iSize = 1;
    m_iSizeMax = m_iSize;
    m_pRealData = new double[1];
    m_pImgData = new double[1];
    setViewAsInteger(false);
    setViewAsZComplex(false);
    m_pRealData[0] = _dblReal;
    m_pImgData[0] = _dblImg;
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Double::Double(int _iRows, int _iCols, double **_pdblReal)
{
    int piDims[2] = {_iRows, _iCols};
    setViewAsInteger(false);
    setViewAsZComplex(false);
    create(piDims, 2, _pdblReal, NULL);

#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Double::Double(int _iRows, int _iCols, double **_pdblReal, double **_pdblImg)
{
    int piDims[2] = {_iRows, _iCols};
    setViewAsInteger(false);
    setViewAsZComplex(false);
    create(piDims, 2, _pdblReal, _pdblImg);

#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Double::Double(int _iDims, const int* _piDims, bool _bComplex, bool _bZComplex)
{
    double *pReal   = NULL;
    double *pImg    = NULL;
    setViewAsZComplex(_bZComplex);
    setViewAsInteger(false);

    if (_bComplex == false || _bZComplex)
    {
        create(_piDims, _iDims, &pReal, NULL);
    }
    else
    {
        create(_piDims, _iDims, &pReal, &pImg);
    }

#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

double*    Double::getReal() const
{
    return get();
}

double Double::getReal(int _iRows, int _iCols)
{
    return get(_iRows, _iCols);
}

void Double::setInt(int* _piReal)
{
    for (int i = 0 ; i < m_iSize ; i++)
    {
        set(i, static_cast<double>(_piReal[i]));
    }
}

void Double::setZeros()
{
    memset(m_pRealData, 0x00, m_iSize * sizeof(double));

    if (m_pImgData != NULL)
    {
        memset(m_pImgData, 0x00, m_iSize * sizeof(double));
    }
}

void Double::setOnes()
{
    std::fill(m_pRealData, m_pRealData + m_iSize, 1);

    if (m_pImgData != NULL)
    {
        std::fill(m_pImgData, m_pImgData + m_iSize, 1);
    }
}

bool Double::subMatrixToString(std::wostringstream& ostr, int* _piDims, int /*_iDims*/)
{
    int iCurrentLine = 0;
    int iLineLen = ConfigVariable::getConsoleWidth();
    int iMaxLines = ConfigVariable::getConsoleLines();

    if (isIdentity())
    {
        ostr << L"eye *\n\n";
        if (isComplex() == false)
        {
            printDoubleValue(ostr, m_pRealData[0]);
            ostr << L"\n";
        }
        else
        {
            //complex value
            printComplexValue(ostr, m_pRealData[0], m_pImgData[0]);
            ostr << L"\n";
        }
        ostr << L"\n";
    }
    else if (isEmpty())
    {
        printEmptyString(ostr);
        ostr << L"\n";
    }
    else if (isScalar())
    {
        //scalar
        _piDims[0] = 0;
        _piDims[1] = 0;
        int iPos = getIndex(_piDims);

        if (isComplex() == false)
        {
            printDoubleValue(ostr, m_pRealData[iPos]);
            ostr << L"\n";
        }
        else
        {
            //complex value
            printComplexValue(ostr, m_pRealData[iPos], m_pImgData[iPos]);
            ostr << L"\n";
        }
    }
    else // matrix
    {
        std::wostringstream ostemp;
        int iLen = SIZE_BETWEEN_TWO_VALUES;
        int iLastCol = m_iCols1PrintState;
        // some unchanging field is to be retrieved for later used
        DoubleFormat df;
        int iBlankSize = df.bPrintBlank ? BLANK_SIZE : 0;

        //Array with the max printed size of each col
        int *piSize = new int[getCols()]();
        int *piRSize = new int[getCols()]();
        int *piISize = new int[getCols()]();

        if (isComplex() == false)
        {
            //compute the row size for padding for the full matrix
            for (int iCols1 = 0 ; iCols1 < getCols() ; iCols1++)
            {
                for (int iRows1 = 0 ; iRows1 < getRows() ; iRows1++)
                {
                    _piDims[0] = iRows1;
                    _piDims[1] = iCols1;
                    int iPos = getIndex(_piDims);

                    DoubleFormat df;
                    getDoubleFormat(m_pRealData[iPos], &df);
                    piSize[iCols1] = std::max(piSize[iCols1], df.iWidth);
                }
            }

            for (int iCols1 = m_iCols1PrintState ; iCols1 < getCols() ; iCols1++)
            {
                if (iLen + piSize[iCols1] > iLineLen && iCols1 != iLastCol)
                {
                    //find the limit, print this part
                    for (int iRows2 = m_iRows2PrintState ; iRows2 < getRows() ; iRows2++)
                    {
                        iCurrentLine++;
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

                        for (int iCols2 = iLastCol ; iCols2 < iCols1 ; iCols2++)
                        {
                            _piDims[0] = iRows2;
                            _piDims[1] = iCols2;
                            int iPos = getIndex(_piDims);

                            DoubleFormat df;
                            getDoubleFormat(m_pRealData[iPos], &df);

                            ostemp << SPACE_BETWEEN_TWO_VALUES;

                            df.iWidth = piSize[iCols2];
                            addDoubleValue(&ostemp, m_pRealData[iPos], &df);
                        }
                        ostemp << L"\n";
                    }

                    iLen = SIZE_BETWEEN_TWO_VALUES;

                    iCurrentLine++;
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

                iLen += piSize[iCols1] + SIZE_BETWEEN_TWO_VALUES + iBlankSize;
            }

            for (int iRows2 = m_iRows2PrintState ; iRows2 < getRows() ; iRows2++)
            {
                iCurrentLine++;
                if ((iMaxLines == 0 && iCurrentLine >= MAX_LINES) || (iMaxLines != 0 && iCurrentLine >= iMaxLines))
                {
                    if (m_iRows2PrintState == 0 && iLastCol != 0)
                    {
                        //add header
                        addColumnString(ostr, iLastCol + 1, getCols());
                    }

                    ostr << ostemp.str();
                    m_iRows2PrintState = iRows2;
                    m_iCols1PrintState = iLastCol;
                    delete[] piSize;
                    return false;
                }

                for (int iCols2 = iLastCol ; iCols2 < getCols() ; iCols2++)
                {
                    _piDims[0] = iRows2;
                    _piDims[1] = iCols2;
                    int iPos = getIndex(_piDims);

                    DoubleFormat df;
                    getDoubleFormat(m_pRealData[iPos], &df);

                    ostemp << SPACE_BETWEEN_TWO_VALUES;
                    df.iWidth = piSize[iCols2];
                    addDoubleValue(&ostemp, m_pRealData[iPos], &df);
                }
                ostemp << L"\n";
            }

            if (m_iRows2PrintState == 0 && iLastCol != 0)
            {
                addColumnString(ostr, iLastCol + 1, getCols());
            }
            ostr << ostemp.str();
        }
        else //Complex case
        {
            //compute the row size for padding for the full matrix.
            for (int iCols1 = 0; iCols1 < getCols() ; iCols1++)
            {
                for (int iRows1 = 0 ; iRows1 < getRows() ; iRows1++)
                {
                    int iTotalWidth = 0;
                    _piDims[0] = iRows1;
                    _piDims[1] = iCols1;
                    int iPos = getIndex(_piDims);

                    DoubleFormat dfR, dfI;

                    getComplexFormat(m_pRealData[iPos], m_pImgData[iPos], &iTotalWidth, &dfR, &dfI);
                    // keep track of real and imaginary part width for further alignment
                    piISize[iCols1] = std::max(piISize[iCols1], dfI.iWidth);
                    piRSize[iCols1] = std::max(piRSize[iCols1], dfR.iWidth);
                    piSize[iCols1]  = std::max(piSize[iCols1], iTotalWidth);
                }
            }

            for (int iCols1 = m_iCols1PrintState ; iCols1 < getCols() ; iCols1++)
            {
                if (iLen + piSize[iCols1] > iLineLen && iCols1 != iLastCol)
                {
                    //find the limit, print this part
                    for (int iRows2 = m_iRows2PrintState ; iRows2 < getRows() ; iRows2++)
                    {
                        iCurrentLine++;
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
                            delete[] piRSize;
                            delete[] piISize;
                            return false;
                        }

                        for (int iCols2 = iLastCol ; iCols2 < iCols1 ; iCols2++)
                        {
                            int iTotalWidth = 0;
                            _piDims[0] = iRows2;
                            _piDims[1] = iCols2;
                            int iPos = getIndex(_piDims);

                            DoubleFormat dfR, dfI;
                            getComplexFormat(m_pRealData[iPos], m_pImgData[iPos], &iTotalWidth, &dfR, &dfI);

                            // override with precomputed real part width for alignment of imaginary part sign
                            dfR.iWidth = piRSize[iCols2];
                            dfI.iWidth = piISize[iCols2];
                            ostemp << SPACE_BETWEEN_TWO_VALUES;
                            addDoubleComplexValue(&ostemp, m_pRealData[iPos], m_pImgData[iPos], piSize[iCols2], &dfR, &dfI);
                        }
                        ostemp << L"\n";
                    }

                    iLen = SIZE_BETWEEN_TWO_VALUES;

                    iCurrentLine++;
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

                iLen += piSize[iCols1] + SIZE_BETWEEN_TWO_VALUES;
            }

            for (int iRows2 = m_iRows2PrintState ; iRows2 < getRows() ; iRows2++)
            {
                iCurrentLine++;
                if ((iMaxLines == 0 && iCurrentLine >= MAX_LINES) || (iMaxLines != 0 && iCurrentLine >= iMaxLines))
                {
                    if (m_iRows2PrintState == 0 && iLastCol != 0)
                    {
                        //add header
                        addColumnString(ostr, iLastCol + 1, getCols());
                    }

                    ostr << ostemp.str();
                    m_iRows2PrintState = iRows2;
                    m_iCols1PrintState = iLastCol;
                    delete[] piSize;
                    delete[] piRSize;
                    return false;
                }

                for (int iCols2 = iLastCol ; iCols2 < getCols() ; iCols2++)
                {
                    int iTotalWidth = 0;
                    _piDims[0] = iRows2;
                    _piDims[1] = iCols2;
                    int iPos = getIndex(_piDims);

                    DoubleFormat dfR, dfI;
                    getComplexFormat(m_pRealData[iPos], m_pImgData[iPos], &iTotalWidth, &dfR, &dfI);

                    // override with precomputed real part width for aligment of imaginary part sign
                    dfR.iWidth = piRSize[iCols2];
                    dfI.iWidth = piISize[iCols2];
                    ostemp << SPACE_BETWEEN_TWO_VALUES;
                    addDoubleComplexValue(&ostemp, m_pRealData[iPos], m_pImgData[iPos], piSize[iCols2], &dfR, &dfI);
                }
                ostemp << L"\n";
            }

            if (m_iRows2PrintState == 0 && iLastCol != 0)
            {
                addColumnString(ostr, iLastCol + 1, getCols());
            }
            ostr << ostemp.str();
        }

        delete[] piSize;
        delete[] piRSize;
        delete[] piISize;
    }
    
    std::flush(ostr);
    
    return true;
}

std::wstring Double::toStringInLine()
{
    if (isScalar())
    {
        std::wostringstream ostr;

        if (isComplex())
        {
            double re = getFirst();
            double im = getImgFirst();
            DoubleFormat dfR, dfI;
            dfR.bPrintBlank = false;
            dfR.bPaddSign = false;
            getDoubleFormat(re, &dfR);
            getDoubleFormat(im, &dfI);
            addDoubleComplexValue(&ostr, re, im, dfR.iWidth + dfI.iWidth, &dfR, &dfI);
        }
        else
        {
            double re = getFirst();
            DoubleFormat df;
            df.bPrintBlank = false;
            df.bPaddSign = false;
            getDoubleFormat(re, &df);
            addDoubleValue(&ostr, re, &df);
        }

        return ostr.str();
    }
    else if (isEmpty())
    {
        return L"[]";
    }
    else
    {
        return ArrayOf<double>::toStringInLine();
    }
}

Double* Double::clone()
{
    int iMemSize = m_iSize * sizeof(double);
    bool bHasImgData = (m_pImgData !=  NULL);
    Double *pReturn = new Double(m_iDims, m_piDims, bHasImgData);

    memcpy(pReturn->getReal(), m_pRealData, iMemSize);

    if (bHasImgData)
    {
        memcpy(pReturn->getImg(), m_pImgData, iMemSize);
    }

    return pReturn;
}

bool Double::operator==(const InternalType& it)
{
    if (const_cast<InternalType &>(it).isDouble() == false)
    {
        return false;
    }

    Double* pdbl = const_cast<InternalType &>(it).getAs<Double>();

    if (pdbl->getDims() != getDims())
    {
        return false;
    }

    for (int i = 0; i < m_iDims; i++)
    {
        if (pdbl->getDimsArray()[i] != getDimsArray()[i])
        {
            return false;
        }
    }

    double *pdblReal = pdbl->getReal();
    for (int i = 0; i < m_iSize; i++)
    {
        if (m_pRealData[i] != pdblReal[i])
        {
            return false;
        }
    }

    //both complex
    if (getImg() && pdbl->getImg())
    {
        double *pdblImg = pdbl->getImg();
        for (int i = 0 ; i < m_iSize ; i++)
        {
            if (m_pImgData[i] != pdblImg[i])
            {
                return false;
            }
        }
    }
    //pdbl complex check all img values == 0
    else if (pdbl->getImg())
    {
        double *pdblImg = pdbl->getImg();
        return std::all_of(pdblImg, pdblImg + m_iSize, [](double d){ return d == 0.0; });
    }
    //complex check all img values == 0
    else if (getImg())
    {
        return std::all_of(m_pImgData, m_pImgData + m_iSize, [](double d){ return d == 0.0; });
    }

    return true;
}

bool Double::operator!=(const InternalType& it)
{
    return !(*this == it);
}

double Double::getNullValue()
{
    return 0;
}

Double* Double::createEmpty(int _iDims, int* _piDims, bool _bComplex)
{
    return new Double(_iDims, _piDims, _bComplex);
}

double Double::copyValue(double _dblData)
{
    return _dblData;
}

void Double::deleteAll()
{
    if (isViewAsZComplex())
    {
        vFreeDoubleComplexFromPointer((doublecomplex*)m_pRealData);
    }
    else
    {
        delete[] m_pRealData;
    }

    m_pRealData = NULL;
    deleteImg();
}

void Double::deleteImg()
{
    delete[] m_pImgData;
    m_pImgData = NULL;
}

double* Double::allocData(int _iSize)
{
    if (isViewAsZComplex())
    {
        return (double*)new doublecomplex[_iSize];
    }
    else
    {
        return new double[_iSize];
    }
}

void Double::append(int _iRows, int _iCols, InternalType* _poSource)
{
    Double* pD = _poSource->getAs<Double>();
    int iRows = pD->getRows();
    int iCols = pD->getCols();
    int iSize = iRows * iCols;

    //insert without resize
    if (iRows + _iRows > getRows() || iCols + _iCols > getCols())
    {
        return;
    }

    //Update complexity if necessary
    if (isComplex() != pD->isComplex())
    {
        setComplex(true);
    }

    int iInc = 1;
    int iOne = 1;

    //two cases :
    //  - append to 0,0
    //  - real append in x,y

    if (_iRows == 0 && _iCols == 0)
    {
        //append to 0,0
        //std::cout << "append 0,0" << std::endl;
        if (iRows == 1 || iRows == getRows())
        {
            //std::cout << "full Rows or one row" << std::endl;
            if (iRows == 1)
            {
                iInc = getRows();
                //std::cout << "iInc : " << iInc << std::endl;
            }

            if (getImg())
            {
                C2F(dcopy)(&iSize, pD->get(), &iOne, get(), &iInc);
                if (pD->getImg())
                {
                    C2F(dcopy)(&iSize, pD->getImg(), &iOne, getImg(), &iInc);
                }
                else
                {
                    memset(getImg(), 0x00, iSize * sizeof(double));
                }
            }
            else
            {
                C2F(dcopy)(&iSize, pD->get(), &iOne, get(), &iInc);
            }
        }
        else
        {
            //std::cout << "part of row" << std::endl;
            if (getImg())
            {
                for (int i = 0 ; i < iCols ; i++)
                {
                    int iOffset = i * getRows();
                    memmove(get() + iOffset, pD->get() + i * iRows, iRows * sizeof(double));
                    if (pD->getImg())
                    {
                        memmove(getImg() + iOffset, pD->getImg() + i * iRows, iRows * sizeof(double));
                    }
                    else
                    {
                        memset(getImg() + iOffset, 0x00, iRows * sizeof(double));
                    }
                }
            }
            else
            {
                for (int i = 0 ; i < iCols ; i++)
                {
                    memmove(get() + i * getRows(), pD->get() + i * iRows, iRows * sizeof(double));
                }
            }
        }
    }
    else if (_iRows == 0 || (_iCols == 0 && (iCols == 1 || iRows == 1)))
    {
        //real append in x,y
        //std::cout << "real append in x,y" << std::endl;
        if (iRows == 1)
        {
            iInc = getRows();
            //std::cout << "iInc : " << iInc << std::endl;
        }

        int iOffset =  _iCols * getRows() + _iRows;
        C2F(dcopy)(&iSize, pD->get(), &iOne, get() + iOffset, &iInc);

        if (getImg())
        {
            int iOffset =  _iCols * getRows() + _iRows;
            C2F(dcopy)(&iSize, pD->get(), &iOne, get() + iOffset, &iInc);
            if (pD->getImg())
            {
                C2F(dcopy)(&iSize, pD->getImg(), &iOne, getImg() + iOffset, &iInc);
            }
            else
            {
                int iZero = 0;
                double dblZero = 0;
                C2F(dcopy)(&iSize, &dblZero, &iZero, getImg() + iOffset, &iInc);
            }
        }
    }
    else
    {
        //std::cout << "no optimisation" << std::endl;
        if (getImg())
        {
            for (int i = 0 ; i < iCols ; i++)
            {
                int iOffset = (_iCols + i) * getRows() + _iRows;
                
                memmove(get() + iOffset, pD->get() + i * iRows, iRows * sizeof(double));
                
                if (pD->getImg())
                {
                    memmove(getImg() + iOffset, pD->getImg() + i * iRows, iRows * sizeof(double));
                }
                else
                {
                    memset(getImg() + iOffset, 0x00, iRows * sizeof(double));
                }
            }
        }
        else
        {
            for (int i = 0 ; i < iCols ; i++)
            {
                memmove(get() + (_iCols + i) * getRows() + _iRows, pD->get() + i * iRows, iRows * sizeof(double));
            }
        }
    }
}

void Double::convertToInteger()
{
    if (isViewAsInteger())
    {
        //already done
        return;
    }
    //convert in place double to integer
    int* piR = (int*)get();
    double *pdblR = get();

    if (getImg())
    {
        int* piI = (int*)getImg();
        double *pdblI = getImg();

        //normal way to prevent overlap
        for (int i = 0; i < m_iSize; i++)
        {
            piR[i] = (int)pdblR[i];
            piI[i] = (int)pdblI[i];
        }
    }
    else
    {
        //normal way to prevent overlap
        for (int i = 0; i < m_iSize; i++)
        {
            piR[i] = (int)pdblR[i];
        }
    }

    setViewAsInteger(true);
}

void Double::convertFromInteger()
{
    if (isViewAsInteger() == false)
    {
        //no need change
        return;
    }

    int* piR = (int*)get();
    double *pdblR = get();
    //convert in place integer to double

    if (getImg())
    {
        int* piI = (int*)getImg();
        double *pdblI = getImg();

        //reverse way to prevent overlap
        for (int i = m_iSize - 1 ; i >= 0 ; i--)
        {
            pdblR[i] = (double)piR[i];
            pdblI[i] = (double)piI[i];
        }
    }
    else
    {
        //reverse way to prevent overlap
        for (int i = m_iSize - 1 ; i >= 0 ; i--)
        {
            pdblR[i] = (double)piR[i];
        }
    }

    setViewAsInteger(false);
}

void Double::convertFromZComplex()
{
    if (isViewAsZComplex() == false)
    {
        //no need change
        return;
    }

    doublecomplex* pdblZ = (doublecomplex*)get();
    m_pRealData = new double[getSize()];

    delete[] m_pImgData;
    m_pImgData = new double[getSize()];

    vGetPointerFromDoubleComplex(pdblZ, getSize(), m_pRealData, m_pImgData);
    vFreeDoubleComplexFromPointer(pdblZ);

    setViewAsZComplex(false);
}

void Double::convertToZComplex()
{
    if (isViewAsZComplex())
    {
        //already done
        return;
    }

    doublecomplex* pdblZ = NULL;

    pdblZ = oGetDoubleComplexFromPointer(getReal(), getImg() , getSize());

    delete[] m_pImgData;
    m_pImgData = NULL;

    delete[] m_pRealData;
    m_pRealData = (double*)pdblZ;

    setViewAsZComplex(true);
}

ast::Exp* Double::getExp(const Location& loc)
{
    return new ast::DoubleExp(loc, this);
}

bool Double::isTrue()
{
    if (isEmpty())
    {
        return false;
    }

    if (m_pImgData ==  NULL)
    {
        return type_traits::isTrue<double>(isViewAsZComplex() ? 2 * m_iSize : m_iSize, m_pRealData);
    }
    else
    {
        for (int i = 0; i < m_iSize; ++i)
        {
            if (!(m_pRealData[i] || m_pImgData[i]))
            {
                return false;
            }
        }

        return true;
    }
}

}
