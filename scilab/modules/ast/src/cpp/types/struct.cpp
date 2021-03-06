/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2020 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "struct.hxx"
#include "string.hxx"
#include "double.hxx"
#include "list.hxx"
#include "int.hxx"
#include "localization.hxx"
#include "scilabWrite.hxx"
#include "exp.hxx"
#include "types_tools.hxx"

extern "C" {
#include "sci_malloc.h"
}

namespace types
{
Struct::Struct()
{
    static int piDims[2] = {0, 0};
    m_bDisableCloneInCopyValue = false;
    SingleStruct** pIT  = NULL;
    create(piDims, 2, &pIT, NULL);
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Struct::Struct(int _iRows, int _iCols, bool _bInit)
{
    m_bDisableCloneInCopyValue = false;
    SingleStruct** pIT  = NULL;
    int piDims[2] = {_iRows, _iCols};
    create(piDims, 2, &pIT, NULL);

    if(_bInit)
    {
        SingleStruct *p = new SingleStruct();
        for (int i = 0 ; i < getSize() ; i++)
        {
            set(i, p);
        }

        p->killMe();
    }
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Struct::Struct(int _iDims, const int* _piDims, bool _bInit)
{
    m_bDisableCloneInCopyValue = false;
    SingleStruct** pIT = NULL;
    create(_piDims, _iDims, &pIT, NULL);
    if(_bInit)
    {
        SingleStruct *p = new SingleStruct();
        for (int i = 0 ; i < getSize() ; i++)
        {
            set(i, p);
        }
        p->killMe();
    }

#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

Struct::~Struct()
{
    for (int i = 0 ; i < m_iSizeMax ; i++)
    {
        SingleStruct *pStr = m_pRealData[i];
        if (pStr)
        {
            pStr->DecreaseRef();
            pStr->killMe();
        }
    }

    delete[] m_pRealData;
#ifndef NDEBUG
    Inspector::removeItem(this);
#endif
}

Struct::Struct(Struct *_oStructCopyMe)
{
    m_bDisableCloneInCopyValue = false;
    SingleStruct** pIT = NULL;
    create(_oStructCopyMe->getDimsArray(), _oStructCopyMe->getDims(), &pIT, NULL);
    for (int i = 0 ; i < getSize() ; i++)
    {
        pIT[i] = _oStructCopyMe->get(i)->clone();
        pIT[i]->IncreaseRef();
    }
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

bool Struct::getMemory(int* _piSize, int* _piSizePlusType)
{
    *_piSize = 0;
    *_piSizePlusType = 0;
    SingleStruct** p = get();
    for (int i = 0; i < getSize(); i++)
    {
        int piS, piSPT;
        if (p[i]->getMemory(&piS, &piSPT))
        {
            *_piSize += piS;
            *_piSizePlusType += piSPT;
        }
    }

    *_piSizePlusType += sizeof(Struct);
    return true;
}

Struct* Struct::clone()
{
    return new Struct(this);
}

bool Struct::transpose(InternalType *& out)
{
    if (isScalar())
    {
        out = clone();
        return true;
    }

    if (m_iDims == 2)
    {
        // dont fill the Struct, transpose will do it.
        Struct * pSt = new Struct(getCols(), getRows(), false);
        Transposition::transpose(getRows(), getCols(), m_pRealData, pSt->get());
        for (int i = 0; i < m_iSize; ++i)
        {
            // Transposition::transpose doesn't increase the ref.
            pSt->get(i)->IncreaseRef();
        }

        out = pSt;
        return true;
    }

    return false;
}

bool Struct::extract(const std::wstring & name, InternalType *& out)
{
    if (exists(name))
    {
        out = extractField(name);
    }
    else
    {
        wchar_t szError[bsiz];
        os_swprintf(szError, bsiz, _W("Unknown field : %ls.\n").c_str(), name.c_str());
        throw ast::InternalError(szError);
    }

    return true;
}

bool Struct::invoke(typed_list & in, optional_list & opt, int _iRetCount, typed_list & out, const ast::Exp & e)
{
    if (in.size() == 0)
    {
        out.push_back(this);
        return true;
    }
    else if (in.size() == 1)
    {
        InternalType * arg = in[0];
        std::vector<InternalType *> _out;
        if (arg->isString())
        {
            std::vector<std::wstring> wstFields;
            String * pString = arg->getAs<types::String>();
            for (int i = 0; i < pString->getSize(); ++i)
            {
                std::wstring wstField(pString->get(i));
                if (this->exists(wstField))
                {
                    wstFields.push_back(wstField);
                }
                else
                {
                    char* field_name = wide_string_to_UTF8(wstField.c_str());
                    ast::InternalError ie(161, e.getLocation(), field_name);
                    FREE(field_name);
                    throw ie;
                }
            }

            _out = extractFields(wstFields);

            out.swap(_out);
            return true;
        }
    }

    return ArrayOf<SingleStruct*>::invoke(in, opt, _iRetCount, out, e);
}

void Struct::set(int _iRows, int _iCols, SingleStruct* _pIT)
{
    set(_iCols * getRows() + _iRows, _pIT);
}

void Struct::set(int _iRows, int _iCols, const SingleStruct* _pIT)
{
    set(_iCols * getRows() + _iRows, _pIT);
}

void Struct::set(int _iIndex, SingleStruct* _pIT)
{
    if (m_bDisableCloneInCopyValue && m_pRealData[_iIndex] == _pIT)
    {
        return;
    }

    InternalType* pOld = m_pRealData[_iIndex];

    m_pRealData[_iIndex] = copyValue(_pIT);
    if (m_bDisableCloneInCopyValue == false)
    {
        //only in clone mode
        m_pRealData[_iIndex]->IncreaseRef();
    }

    if (pOld != NULL)
    {
        pOld->DecreaseRef();
        pOld->killMe();
    }
}

void Struct::set(int _iIndex, const SingleStruct* _pIT)
{
    InternalType* pOld = m_pRealData[_iIndex];

    m_pRealData[_iIndex] = const_cast<SingleStruct*>(_pIT)->clone();

    if (pOld != NULL)
    {
        pOld->DecreaseRef();
        pOld->killMe();
    }
}

void Struct::set(SingleStruct** _pIT)
{
    for (int i = 0 ; i < getSize() ; i++)
    {
        set(i, _pIT[i]);
    }
}

String* Struct::getFieldNames()
{
    if (getSize() != 0)
    {
        return getFirst()->getFieldNames();
    }
    else
    {
        return NULL;
    }
}

bool Struct::exists(const std::wstring& _sKey)
{
    if (getSize() != 0)
    {
        return getFirst()->exists(_sKey);
    }
    else
    {
        return false;
    }
}

bool Struct::operator==(const InternalType& it)
{
    if (const_cast<InternalType &>(it).isStruct() == false)
    {
        return false;
    }

    Struct* pStr = const_cast<InternalType &>(it).getAs<Struct>();

    for (int i = 0 ; i < getDims() ; i++)
    {
        if (pStr->getDimsArray()[i] != getDimsArray()[i])
        {
            return false;
        }
    }

    for (int i = 0 ; i < getSize() ; i++)
    {
        if (*get(i) != *pStr->get(i))
        {
            return false;
        }
    }
    return true;
}

bool Struct::operator!=(const InternalType& it)
{
    return !(*this == it);
}

SingleStruct* Struct::getNullValue()
{
    return new SingleStruct();
}

Struct* Struct::createEmpty(int _iDims, int* _piDims, bool /*_bComplex*/)
{
    Struct* pStr = new Struct(_iDims, _piDims);
    pStr->setCloneInCopyValue(!m_bDisableCloneInCopyValue);
    return pStr;
}

SingleStruct* Struct::copyValue(SingleStruct* _pData)
{
    SingleStruct* pStr = NULL;
    if (m_bDisableCloneInCopyValue)
    {
        pStr = _pData;
        pStr->IncreaseRef();
        //std::wcout << L"copyValueWithoutClone -> " << pStr << L" : " << pStr->getRef() << std::endl;
    }
    else
    {
        pStr = _pData->clone();
    }

    return pStr;
}

void Struct::deleteAll()
{
    for (int i = 0 ; i < getSize() ; i++)
    {
        m_pRealData[i]->DecreaseRef();
        m_pRealData[i]->killMe();
    }
    delete[] m_pRealData;
    m_pRealData = NULL;
}

void Struct::deleteImg()
{
    return;
}

bool Struct::isEmpty()
{
    if (getDims() == 2 && getRows() == 0 && getCols() == 0)
    {
        return true;
    }
    return false;
}

SingleStruct** Struct::allocData(int _iSize)
{
    SingleStruct** pData = new SingleStruct*[_iSize];
    for (int i = 0 ; i < _iSize ; i++)
    {
        pData[i] = NULL;
    }
    return pData;
}

bool Struct::subMatrixToString(std::wostringstream& /*ostr*/, int* /*_piDims*/, int /*_iDims*/)
{
    return true;
}

Struct* Struct::addField(const std::wstring& _sKey)
{
    if (getSize() == 0)
    {
        //change dimension to 1x1 and add field
        resize(1, 1);
    }

    for (int i = 0 ; i < getSize() ; i++)
    {
        get(i)->addField(_sKey);
    }

    return this;
}

Struct* Struct::addFieldFront(const std::wstring& _sKey)
{
    if (getSize() == 0)
    {
        //change dimension to 1x1 and add field
        resize(1, 1);
    }

    for (int i = 0 ; i < getSize() ; i++)
    {
        get(i)->addFieldFront(_sKey);
    }

    return this;
}

Struct* Struct::removeField(const std::wstring& _sKey)
{
    for (int j = 0; j < getSize(); j++)
    {
        get(j)->removeField(_sKey);
    }

    if (getFieldNames()->getSize() == 0)
    {
        // no fields are left, thus resize to empty struct array
        int piDims[2] = {0, 0};
        m_bDisableCloneInCopyValue = true;
        ArrayOf<SingleStruct*>::resize(piDims, 2)->getAs<Struct>();
        m_bDisableCloneInCopyValue = false;
    }

    return this;
}

bool Struct::toString(std::wostringstream& ostr)
{
    if (getSize() == 0)
    {
        ostr << L"  0x0 struct array with no field.";
    }
    else if (getSize() == 1)
    {
        SingleStruct* pSS =  getFirst();
        String* pwstFields =  pSS->getFieldNames();
        if (pwstFields->getSize() == 0)
        {
            ostr << L"  1x1 struct array with no field.";
        }

        for (int i = 0 ; i < pwstFields->getSize() ; i++)
        {
            std::wstring wstField(pwstFields->get(i));
            InternalType* pIT = pSS->get(wstField);

            //                ostr << L"  " << wstField << ": ";
            ostr << L"  " << wstField << L": ";
            ostr << pIT->toStringInLine();
            ostr << L"\n";
        }
        pwstFields->killMe();
    }
    else
    {
        ostr << L"  " << DimsToString<std::wstring>() << L" struct array with fields:\n";
        String* pwstFields = getFieldNames();
        for (int i = 0 ; i < pwstFields->getSize() ; i++)
        {
            ostr << L"    " << pwstFields->get(i) << L"\n";
        }
        pwstFields->killMe();
    }
    
    std::flush(ostr);
    
    return true;
}

List* Struct::extractFieldWithoutClone(const std::wstring& _wstField)
{
    List* pL = new List();
    for (int j = 0 ; j < getSize() ; j++)
    {
        pL->set(j, get(j)->get(_wstField));
    }

    return pL;
}

typed_list Struct::extractFields(std::vector<std::wstring> _wstFields)
{
    typed_list ResultList(_wstFields.size());

    for (int i = 0 ; i < (int)_wstFields.size() ; i++)
    {
        extract(_wstFields[i], ResultList[i]);
    }

    return ResultList;
}

InternalType * Struct::extractField(const std::wstring & wstField)
{
    if (wstField == L"dims")
    {
        Int32 * pDims = new Int32(1, getDims());
        for (int j = 0 ; j < getDims() ; j++)
        {
            pDims->set(j, getDimsArray()[j]);
        }

        return pDims;
    }
    else
    {
        if (getSize() == 1)
        {
            return getFirst()->get(wstField);
        }
        else
        {
            List * pL = new List();
            for (int j = 0 ; j < getSize() ; j++)
            {
                pL->append(get(j)->get(wstField));
            }

            return pL;
        }
    }
}

typed_list Struct::extractFields(typed_list* _pArgs)
{
    typed_list ResultList;

    int iDims           = (int)_pArgs->size();
    typed_list pArg;

    int* piMaxDim       = new int[iDims];

    int iSeqCount = checkIndexesArguments(this, _pArgs, &pArg, piMaxDim, NULL);
    delete[] piMaxDim;

    if (iSeqCount == 0)
    {
        //free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        ResultList.push_back(Double::Empty());
        return ResultList;
    }

    Double* pIndex = pArg[0]->getAs<Double>();

    for (int i = 0 ; i < iSeqCount ; i++)
    {
        int iIndex = (int)pIndex->get(i);

        if (iIndex == 1)
        {
            //struct fields name
            String* pS = getFieldNames();
            String* pFields = NULL;
            if (pS)
            {
                pFields = new String(1, pS->getSize() + 2);
                for (int j = 0; j < pS->getSize(); j++)
                {
                    pFields->set(2 + j, pS->get(j));
                }

                pS->killMe();
            }
            else
            {
                pFields = new String(1, 2);
            }

            pFields->set(0, L"st");
            pFields->set(1, L"dims");

            ResultList.push_back(pFields);
        }
        else if (iIndex == 2)
        {
            //struct dims
            Int32* pDims = new Int32(1, getDims());
            for (int j = 0 ; j < getDims() ; j++)
            {
                pDims->set(j, getDimsArray()[j]);
            }

            ResultList.push_back(pDims);
        }
        else if (getSize() == 0)
        {
            break;
        }
        else if (iIndex > (int)getFirst()->getNumFields() + 2)
        {
            break;
        }
        else if (getSize() == 1)
        {
            //return elements
            const typed_list & pData = getFirst()->getData();
            ResultList.push_back(pData[iIndex - 3]->clone());
        }
        else
        {
            //return each elements for sub structs in a list
            List* pL = new List();

            for (int j = 0 ; j < getSize() ; j++)
            {
                //-2 for fieldlist and dims, -1 for indexed at 0
                const typed_list & pData = get(j)->getData();
                pL->append(pData[iIndex - 3]->clone());
            }

            ResultList.push_back(pL);
        }
    }

    //free pArg content
    cleanIndexesArguments(_pArgs, &pArg);
    return ResultList;
}

Struct* Struct::resize(int _iNewRows, int _iNewCols)
{
    int piDims[2] = {_iNewRows, _iNewCols};
    return resize(piDims, 2);
}

Struct* Struct::resize(int* _piDims, int _iDims)
{
    m_bDisableCloneInCopyValue = true;
    Struct* pSRes = ArrayOf<SingleStruct*>::resize(_piDims, _iDims)->getAs<Struct>();
    m_bDisableCloneInCopyValue = false;
    if (pSRes)
    {
        // insert field(s) only in new element(s) of current struct
        String* pFields = getFieldNames();
        for (int iterField = 0; iterField < pFields->getSize(); iterField++)
        {
            for (int iterStruct = 0; iterStruct < getSize(); iterStruct++)
            {
                get(iterStruct)->addField(pFields->get(iterField));
            }
        }

        pFields->killMe();
    }

    return pSRes;
}

InternalType* Struct::extractWithoutClone(typed_list* _pArgs)
{
    //std::wcout << L"extractWithoutClone start" << std::endl;
    m_bDisableCloneInCopyValue = true;
    InternalType* pIT = extract(_pArgs);
    m_bDisableCloneInCopyValue = false;
    //std::wcout << L"extractWithoutClone end" << std::endl;
    return pIT;
}

void Struct::setCloneInCopyValue(bool _val)
{
    m_bDisableCloneInCopyValue = !_val;
}

void Struct::deleteData(SingleStruct* data)
{
    if (data)
    {
        data->killMe();
    }
}

Struct* Struct::createEmpty()
{
    return new Struct();
}
}
