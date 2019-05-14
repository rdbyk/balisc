/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
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

#include <algorithm>
#include <sstream>
#include <math.h>
#include <iomanip>
#include "symbol.hxx"
#include "cell.hxx"
#include "double.hxx"
#include "list.hxx"
#include "colon.hxx"
#include "tostring_common.hxx"
#include "core_math.h"
#include "list.hxx"
#include "configvariable.hxx"
#include "types_tools.hxx"

namespace types
{
/**
** Constructor & Destructor (public)
*/
Cell::Cell()
{
    static int piDims[2] = {0, 0};
    createCell(2, piDims, nullptr);
}

Cell::Cell(int _iRows, int _iCols, InternalType** data)
{
    int piDims[2] = {_iRows, _iCols};
    createCell(2, piDims, data);
}

Cell::Cell(int _iDims, const int* _piDims, InternalType** data)
{
    createCell(_iDims, _piDims, data);
}

bool Cell::getMemory(int* _piSize, int* _piSizePlusType)
{
    *_piSize = 0;
    *_piSizePlusType = 0;
    InternalType** p = get();
    for (int i = 0; i < getSize(); i++)
    {
        int piS, piSPT;
        if (p[i]->getMemory(&piS, &piSPT))
        {
            *_piSize += piS;
            *_piSizePlusType += piSPT;
        }
    }
    *_piSizePlusType += sizeof(Cell);
    return true;
}

void Cell::createCell(int _iDims, const int* _piDims, InternalType** data)
{
    // FIXME: For _iDims = 2, _piDims={-1,-1} we are expected to
    // create an empty cell "{}". However, ArrayOf::create interprets
    // this args as "eye()", thus, for the time being, we have to take
    // care of this case here ...
    // In the long run, it might be a good idea to implement a dedicated
    // Cell::create ... ?!
    if (_iDims == 2 && _piDims[0] == -1 && _piDims[1] == -1)
    {
        int piDims[2] = {0, 0};
        create(piDims, 2, NULL, NULL);
    }
    else
    {
        InternalType** pIT = NULL;
        create(_piDims, _iDims, &pIT, NULL);
    }

    if( m_iSizeMax == 0)
    {
        return;
    }

    if (data == nullptr)
    {
        types::Double* pDbl = Double::Empty();
        for (int i = 0; i < m_iSizeMax; i++)
        {
            m_pRealData[i] = pDbl;
            m_pRealData[i]->IncreaseRef();
        }
    }
    else
    {
        for (int i = 0; i < m_iSizeMax; i++)
        {
            m_pRealData[i] = data[i];
            m_pRealData[i]->IncreaseRef();
        }
    }

#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Cell::~Cell()
{
    for (int i = 0; i < m_iSizeMax; i++)
    {
        m_pRealData[i]->DecreaseRef();
        m_pRealData[i]->killMe();
    }

    delete[] m_pRealData;
#ifndef NDEBUG
    Inspector::removeItem(this);
#endif
}

/**
** Private Copy Constructor and data Access
*/
Cell::Cell(Cell *_oCellCopyMe)
{
    InternalType** pIT = NULL;
    create(_oCellCopyMe->getDimsArray(), _oCellCopyMe->getDims(), &pIT, NULL);
    for (int i = 0 ; i < getSize() ; i++)
    {
        m_pRealData[i] = NULL;
    }

    for (int i = 0 ; i < getSize() ; i++)
    {
        set(i, _oCellCopyMe->get(i)->clone());
    }
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

bool Cell::transpose(InternalType *& out)
{
    if (isScalar())
    {
        out = clone();
        return true;
    }

    if (m_iDims == 2)
    {
        InternalType** pOutData = new InternalType*[getSize()];

        Transposition::transpose_clone(getRows(), getCols(), m_pRealData, pOutData);
        out = new Cell(getCols(), getRows(), pOutData);

        delete[] pOutData;

        return true;
    }

    return false;
}

void Cell::set(int _iRows, int _iCols, InternalType* _pIT)
{
    set(_iCols * getRows() + _iRows, _pIT);
}

void Cell::set(int _iRows, int _iCols, const InternalType* _pIT)
{
    set(_iCols * getRows() + _iRows, _pIT);
}

void Cell::set(int _iIndex, InternalType* _pIT)
{
    // corner case when inserting twice
    if (m_pRealData[_iIndex] == _pIT)
    {
        return;
    }

    if (m_pRealData[_iIndex] != NULL)
    {
        m_pRealData[_iIndex]->DecreaseRef();
        m_pRealData[_iIndex]->killMe();
    }

    _pIT->IncreaseRef();
    m_pRealData[_iIndex] = _pIT;
}

void Cell::set(int _iIndex, const InternalType* _pIT)
{
    // corner case when inserting twice
    if (m_pRealData[_iIndex] == _pIT)
    {
        return;
    }

    if (m_pRealData[_iIndex] != NULL)
    {
        m_pRealData[_iIndex]->DecreaseRef();
        m_pRealData[_iIndex]->killMe();
    }

    const_cast<InternalType*>(_pIT)->IncreaseRef();
    m_pRealData[_iIndex] = const_cast<InternalType*>(_pIT);
}

void Cell::set(InternalType** _pIT)
{
    for (int i = 0; i < m_iSize; i++)
    {
        if (m_pRealData[i] != NULL)
        {
            m_pRealData[i]->DecreaseRef();
            m_pRealData[i]->killMe();
        }

        _pIT[i]->IncreaseRef();
        m_pRealData[i] = _pIT[i];
    }
}

/**
** Clone
** Create a new Struct and Copy all values.
*/
Cell* Cell::clone()
{
    return new Cell(this);
}

InternalType* Cell::getNullValue()
{
    return Double::Empty();
}

Cell* Cell::createEmpty(int _iDims, int* _piDims, bool /*_bComplex*/)
{
    return new Cell(_iDims, _piDims);
}

InternalType* Cell::copyValue(InternalType* _pData)
{
    _pData->IncreaseRef();
    return _pData;
}

void Cell::deleteAll()
{
    for (int i = 0 ; i < getSize() ; i++)
    {
        m_pRealData[i]->DecreaseRef();
        m_pRealData[i]->killMe();
    }

    delete[] m_pRealData;
    m_pRealData = NULL;
}

void Cell::deleteImg()
{
    return;
}

bool Cell::isEmpty()
{
    if (getDims() == 2 && getRows() == 0 && getCols() == 0)
    {
        return true;
    }
    return false;
}

/**
** toString to display Structs
** FIXME : Find a better indentation process
*/
bool Cell::subMatrixToString(std::wostringstream& ostr, int* _piDims, int /*_iDims*/)
{
    int iPrecision = ConfigVariable::getFormatSize();

    if (isEmpty())
    {
        ostr << L"   {}";
    }
    else
    {
        //max len for each column
        int *piTypeLen = new int[getCols()]();
        int *piSizeLen = new int[getCols()]();

        for (int j = 0 ; j < getCols() ; j++)
        {
            for (int i = 0 ; i < getRows() ; i++)
            {
                _piDims[0] = i;
                _piDims[1] = j;

                int iPos = getIndex(_piDims);
                InternalType* pIT = get(iPos);

                if (pIT->isAssignable() && pIT->isListOperation() == false)
                {
                    //compute number of digits to write dimensions
                    int iTypeLen = 0;
                    if (pIT->isGenericType())
                    {
                        GenericType* pGT = pIT->getAs<GenericType>();
                        for (int k = 0 ; k < pGT->getDims() ; k++)
                        {
                            iTypeLen += static_cast<int>(log10(static_cast<double>(pGT->getDimsArray()[k])) + 1);
                        }
                        piSizeLen[j] = std::max(piSizeLen[j], iTypeLen + (pGT->getDims() - 1));//add number of "x"
                    }
                    else
                    {
                        //types non derived from ArrayOf.
                        int iSize = static_cast<int>(log10(static_cast<double>(pIT->getAs<GenericType>()->getRows())) + 1);
                        piSizeLen[j] = std::max(piSizeLen[j], iSize);
                    }
                }
                else
                {
                    //no size so let a white space, size == 1
                    piSizeLen[j] = std::max(piSizeLen[j], 1);
                }

                piTypeLen[j] = std::max(piTypeLen[j], static_cast<int>(pIT->getTypeStr().size()));
            }
        }

        for (int i = 0 ; i < getRows() ; i++)
        {
            for (int j = 0 ; j < getCols() ; j++)
            {
                _piDims[0] = i;
                _piDims[1] = j;
                int iPos = getIndex(_piDims);
                InternalType* pIT = get(iPos);

                ostr << L"  [";
                if (pIT->isAssignable() && pIT->isListOperation() == false)
                {
                    if (pIT->isGenericType())
                    {
                        //"  ixjxkxl type   "
                        GenericType* pGT = pIT->getAs<GenericType>();
                        std::wostringstream ostemp;
                        ostemp << pGT->DimsToString<std::wstring>();
                        configureStream(&ostr, piSizeLen[j], iPrecision, ' ');
                        ostr << std::right << ostemp.str();
                    }
                    else
                    {
                        //" i   "
                        configureStream(&ostr, piSizeLen[j], iPrecision, ' ');
                        if (pIT->isList())
                        {
                            ostr << std::right << pIT->getAs<List>()->getSize();
                        }
                        else
                        {
                            ostr << std::right << 1;
                        }
                    }
                }
                else
                {
                    configureStream(&ostr, piSizeLen[j], iPrecision, ' ');
                    ostr << L"";//fill with space
                }
                ostr << L" ";
                configureStream(&ostr, piTypeLen[j], iPrecision, ' ');
                ostr << std::left << pIT->getTypeStr();
                ostr << L"]";
            }
            ostr << std::endl;
        }

        delete[] piSizeLen;
        delete[] piTypeLen;
    }
    ostr << std::endl << std::resetiosflags(std::ios::adjustfield);
    return true;
}

bool Cell::operator==(const InternalType& it)
{
    if (const_cast<InternalType &>(it).isCell() == false)
    {
        return false;
    }

    Cell* pC = const_cast<InternalType &>(it).getAs<Cell>();

    for (int i = 0 ; i < getDims() ; i++)
    {
        if (pC->getDimsArray()[i] != getDimsArray()[i])
        {
            return false;
        }
    }

    for (int i = 0 ; i < getSize() ; i++)
    {
        if (*get(i) != *pC->get(i))
        {
            return false;
        }
    }
    return true;
}

bool Cell::operator!=(const InternalType& it)
{
    return !(*this == it);
}

List* Cell::extractCell(typed_list* _pArgs)
{
    // FIXME: extract(_pArgs) crashes for _pArgs->size() == 0,
    // thus this is only a workaround ... and actually ArrayOf:extract
    // should be fixed ...
    if (_pArgs->size() == 0)
    {
        List* pList = new List();

        for (int i = 0 ; i < getSize() ; i++)
        {
            pList->append(get(i));
        }

        return pList;
    }
    else
    {
        InternalType* pIT = extract(_pArgs);

        if (pIT == NULL || pIT->isCell() == false)
        {
            return NULL;
        }

        List* pList = new List();

        Cell* pCell = pIT->getAs<Cell>();

        for (int i = 0 ; i < pCell->getSize() ; i++)
        {
            pList->append(pCell->get(i));
        }
        pCell->killMe();

        return pList;
    }
}

Cell* Cell::insertCell(typed_list* _pArgs, InternalType* _pSource)
{
    Cell* pCell = new Cell(1, 1);
    pCell->set(0, _pSource);
    Cell* pOut = insert(_pArgs, pCell)->getAs<Cell>();
    pCell->killMe();
    return pOut;
}

Cell* Cell::insertNewCell(typed_list* _pArgs, InternalType* _pSource)
{
    Cell* pCell = new Cell(1, 1);
    pCell->set(0, _pSource);
    Cell* pOut = pCell->insertNew(_pArgs)->getAs<Cell>();
    return pOut;
}

InternalType** Cell::allocData(int _iSize)
{
    InternalType** pData = new InternalType*[_iSize];
    for (int i = 0 ; i < _iSize ; i++)
    {
        pData[i] = NULL;
    }
    return pData;
}

void Cell::deleteData(InternalType* _pData)
{
    if (_pData)
    {
        _pData->killMe();
    }
}

Cell* Cell::createEmpty()
{
    return new Cell();
}

bool Cell::isTrue()
{
    for (int i = 0; i < getSize(); ++i)
    {
        InternalType* e = get(i);

        if ((e->isGenericType() && !e->isString() && e->getAs<GenericType>()->getSize()) || e->isTrue())
        {
            return true;
        }
    }

    return false;
}

bool Cell::neg(InternalType*& out)
{
    if (getSize() == 0)
    {
        out = new Bool(true);
        return true;
    }

    out = new Bool(this->m_iDims, this->m_piDims);
    int* pb = static_cast<Bool*>(out)->get();

    for (int i = 0; i < m_iSize; ++i)
    {
        InternalType* e = get(i);
        pb[i] = !((e->isGenericType() && !e->isString() && e->getAs<GenericType>()->getSize()) || e->isTrue());
    }

    return true;
}

}
