/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - 2020 Dirk Reusch, Kybernetik Dr. Reusch
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
#include "polynom.hxx"
#include "implicitlist.hxx"
#include "int.hxx"
#include "listundefined.hxx"
#include "configvariable.hxx"
#include "scilabWrite.hxx"
#include "type_traits.hxx"
#include "types_tools.hxx"
#include "numericconstants.hxx"
#include "doubleexp.hxx"

#ifndef NDEBUG
#include "inspector.hxx"
#endif

#include "tostring_common.hxx"

extern "C"
{
#include "core_math.h"
#include "elem_common.h"
}

std::wstring printInLinePoly(types::SinglePoly* _pPoly, std::wstring _stVar);
std::wstring printDouble(types::Double* _pD);
long long convert_input(types::InternalType* _poIT);
unsigned long long convert_unsigned_input(types::InternalType* _poIT);

namespace types
{
ImplicitList::~ImplicitList()
{
    m_poStart->DecreaseRef();
    m_poStart->killMe();
    m_poStep->DecreaseRef();
    m_poStep->killMe();
    m_poEnd->DecreaseRef();
    m_poEnd->killMe();
#ifndef NDEBUG
    Inspector::removeItem(this);
#endif
}

ImplicitList::ImplicitList()
{
    m_iSize     = -1;
    m_eOutType  = ScilabGeneric;
    m_bComputed = false;
    m_poStart = new ListUndefined();
    m_poStart->IncreaseRef();
    m_poStep = m_poStart;
    m_poStep->IncreaseRef();
    m_poEnd = m_poStep;
    m_poEnd->IncreaseRef();
    m_pDblStart = NULL;
    m_pDblStep  = NULL;
    m_pDblEnd   = NULL;
    m_eStartType = ScilabListUndefinedOperation;
    m_eStepType = ScilabListUndefinedOperation;
    m_eEndType = ScilabListUndefinedOperation;

#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

ImplicitList::ImplicitList(InternalType* _poStart, InternalType* _poStep, InternalType* _poEnd)
{
    m_iSize     = -1;
    m_eOutType  = ScilabGeneric;
    m_pDblStart = NULL;
    m_pDblStep  = NULL;
    m_pDblEnd   = NULL;

    m_poStart = _poStart;
    m_poStart->IncreaseRef();
    m_eStartType = m_poStart->getType();

    m_poStep = _poStep;
    m_poStep->IncreaseRef();
    m_eStepType = m_poStep->getType();

    m_poEnd = _poEnd;
    m_poEnd->IncreaseRef();
    m_eEndType = m_poEnd->getType();

    m_bComputed = false;

#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

ImplicitList* ImplicitList::clone()
{
    return new ImplicitList(m_poStart, m_poStep, m_poEnd);
}

InternalType::ScilabType ImplicitList::getStartType()
{
    return m_poStart->getType();
}

InternalType::ScilabType ImplicitList::getStepType()
{
    return m_poStep->getType();
}

InternalType::ScilabType ImplicitList::getEndType()
{
    return m_poEnd->getType();
}

void ImplicitList::setStart(InternalType *_poIT)
{
    m_poStart->DecreaseRef();
    m_poStart->killMe();
    m_poStart = _poIT;
    m_poStart->IncreaseRef();
    m_eStartType = m_poStart->getType();
    m_bComputed = false;
}

void ImplicitList::setStep(InternalType *_poIT)
{
    m_poStep->DecreaseRef();
    m_poStep->killMe();
    m_poStep = _poIT;
    m_poStep->IncreaseRef();
    m_eStepType = m_poStep->getType();
    m_bComputed = false;
}

void ImplicitList::setEnd(InternalType* _poIT)
{

    m_poEnd->DecreaseRef();
    m_poEnd->killMe();
    m_poEnd = _poIT;
    m_poEnd->IncreaseRef();
    m_eEndType = m_poEnd->getType();
    m_bComputed = false;
}

bool ImplicitList::compute()
{
    if (m_bComputed == true)
    {
        return true;
    }

    if (isComputable() == true)
    {
        m_iSize = 0;

        if (m_eOutType == ScilabDouble)
        {
            m_pDblStart = m_poStart->getAs<Double>();
            double dblStart	= m_pDblStart->getFirst();

            m_pDblStep = m_poStep->getAs<Double>();
            double dblStep	= m_pDblStep->getFirst();

            m_pDblEnd = m_poEnd->getAs<Double>();
            double dblEnd	= m_pDblEnd->getFirst();
            
            // handle finiteness of start, step, and end value
            double dblRange = dblEnd - dblStart;

            if (finite(dblStep) == 0 || finite(dblRange) == 0)
            {
                if (std::isnan(dblStep) || std::isnan(dblRange) || std::signbit(dblStep) == std::signbit(dblRange))
                {
                    // return nan
                    m_iSize = -1;
                }

                m_bComputed = true;
                return true;
            }

            // zero step => return []
            if (dblStep == 0)
            {
                m_bComputed = true;
                return true;
            }

            // zero range a:b:a => return a
            if (dblRange == 0)
            {
                m_iSize = 1;
                return true;
            }

            // compute list size
            double dSize = dblRange / dblStep;
            m_iSize = std::ceil(dSize);

            if (m_iSize <= 0)
            {
                if (dSize <= 0.0)
                {
                    // return []
                    m_iSize = 0;
                    m_bComputed = true;
                    return true;
                }
                else
                {
                    // integer overflow
                    throw ast::InternalError(34);
                }
            }
            else if (std::fabs(m_iSize * dblStep) <= std::nextafter(std::fabs(dblRange), HUGE_VAL))
            {
                ++m_iSize;
            }
        }
        else //m_eOutType == ScilabInt
        {
            if (m_eOutType == ScilabInt8 ||
                    m_eOutType == ScilabInt16 ||
                    m_eOutType == ScilabInt32 ||
                    m_eOutType == ScilabInt64)
            {
                //signed
                long long llStart   = convert_input(m_poStart);
                long long llStep    = convert_input(m_poStep);
                long long llEnd     = convert_input(m_poEnd);
                
                // step null
                if (llStep == 0) // return []
                {
                    m_bComputed = true;
                    return true;
                }
                m_iSize = std::max(0,static_cast<int>(floor( static_cast<double>((llEnd - llStart) /(llStep)) )) + 1);
            }
            else
            {
                //unsigned
                unsigned long long ullStart = convert_unsigned_input(m_poStart);
                unsigned long long ullStep	= convert_unsigned_input(m_poStep);
                unsigned long long ullEnd   = convert_unsigned_input(m_poEnd);

                // step null
                if (ullStep == 0) // return []
                {
                    m_bComputed = true;
                    return true;
                }
                m_iSize = std::max(0,static_cast<int>(floor( static_cast<double>((ullEnd - ullStart) /(ullStep)) )) + 1);
            }
        }
        m_bComputed = true;
        return true;
    }
    else
    {
        m_iSize = -1;
        return false;
    }
}

bool ImplicitList::isComputable()
{
    if (m_eStartType != ScilabDouble && m_poStart->isInt() == false
        || m_eStepType != ScilabDouble && m_poStep->isInt() == false
        || m_eEndType != ScilabDouble && m_poEnd->isInt() == false)
    {
        return false;
    }

    // determine output type
    m_eOutType  = ScilabDouble;

    if (m_poStart->isInt())
    {
        m_eOutType  = m_poStart->getType();
    }
    else if (m_poStep->isInt())
    {
        m_eOutType  = m_poStep->getType();
    }
    else if (m_poEnd->isInt())
    {
        m_eOutType  = m_poEnd->getType();
    }

    return true;
}

bool ImplicitList::toString(std::wostringstream& ostr)
{
    ostr << L" ";
    if (m_eStartType == ScilabDouble)
    {
        Double *pD = m_poStart->getAs<Double>();
        ostr << printDouble(pD);
    }
    else //Polynom
    {
        Polynom* pMP = m_poStart->getAs<types::Polynom>();
        ostr << printInLinePoly(pMP->getFirst(), pMP->getVariableName());
    }

    ostr << L":";

    if (m_eStepType == ScilabDouble)
    {
        Double *pD = m_poStep->getAs<Double>();
        ostr << printDouble(pD);
    }
    else //Polynom
    {
        Polynom* pMP = m_poStep->getAs<types::Polynom>();
        ostr << printInLinePoly(pMP->getFirst(), pMP->getVariableName());
    }

    ostr << L":";

    if (m_eEndType == ScilabDouble)
    {
        Double *pD = m_poEnd->getAs<Double>();
        ostr << printDouble(pD);
    }
    else //Polynom
    {
        Polynom* pMP = m_poEnd->getAs<types::Polynom>();
        ostr << printInLinePoly(pMP->getFirst(), pMP->getVariableName());
    }
    ostr << std::endl;
    return true;
}

InternalType::ScilabType ImplicitList::getOutputType()
{
    return m_eOutType;
}

void ImplicitList::extractValueAsDouble(int _iOccur, Double* d)
{
    double dblStart = m_pDblStart->getFirst();
    double dblStep = m_pDblStep->getFirst();
    d->get()[0] = dblStart + _iOccur * dblStep;
}

template<typename T>
void ImplicitList::extractValueAsInteger(int _iOccur, T* val)
{

    val->get()[0] = static_cast<typename T::type>(convert_input(m_poStart)) +
                    _iOccur * static_cast<typename T::type>(convert_input(m_poStep));
}

template<typename T>
void ImplicitList::extractValueAsUnsignedInteger(int _iOccur, T* val)
{
    val->get()[0] = static_cast<typename T::type>(convert_unsigned_input(m_poStart)) +
                    _iOccur * static_cast<typename T::type>(convert_unsigned_input(m_poStep));
}

InternalType* ImplicitList::getInitialType()
{
    static const int piDims[2] = {1, 1};

    if (compute())
    {
        switch (m_eOutType)
        {
            case ScilabDouble:
                return new Double(2, piDims);
            case ScilabInt8:
                return new Int8(2, piDims);
            case ScilabInt16:
                return new Int16(2, piDims);
            case ScilabInt32:
                return new Int32(2, piDims);
            case ScilabInt64:
                return new Int64(2, piDims);
            case ScilabUInt8:
                return new UInt8(2, piDims);
            case ScilabUInt16:
                return new UInt16(2, piDims);
            case ScilabUInt32:
                return new UInt32(2, piDims);
            case ScilabUInt64:
                return new UInt64(2, piDims);
        }
    }

    return nullptr;
}

//extract single value in a InternalType
void ImplicitList::extractValue(int _iOccur, InternalType* pIT)
{
    if (compute())
    {
        switch (m_eOutType)
        {
            case ScilabInt8:
                extractValueAsInteger(_iOccur, pIT->getAs<Int8>());
                break;
            case ScilabInt16:
                extractValueAsInteger(_iOccur, pIT->getAs<Int16>());
                break;
            case ScilabInt32:
                extractValueAsInteger(_iOccur, pIT->getAs<Int32>());
                break;
            case ScilabInt64:
                extractValueAsInteger(_iOccur, pIT->getAs<Int64>());
                break;
            case ScilabUInt8:
                extractValueAsUnsignedInteger(_iOccur, pIT->getAs<UInt8>());
                break;
            case ScilabUInt16:
                extractValueAsUnsignedInteger(_iOccur, pIT->getAs<UInt16>());
                break;
            case ScilabUInt32:
                extractValueAsUnsignedInteger(_iOccur, pIT->getAs<UInt32>());
                break;
            case ScilabUInt64:
                extractValueAsUnsignedInteger(_iOccur, pIT->getAs<UInt64>());
                break;
            case ScilabDouble:
                extractValueAsDouble(_iOccur, pIT->getAs<Double>());
                break;
        }
    }
}

//extract matrix in a Internaltype
InternalType* ImplicitList::extractFullMatrix()
{
    InternalType* pIT = NULL;
    if (compute())
    {
        if (getSize() == 0) // return []
        {
            pIT = Double::Empty();
        }
        else if (getSize() == -1) // return nan
        {
            unsigned long long raw = 0x7ff8000000000000;
            double not_a_number = *( double* )&raw;
            pIT = new Double(not_a_number);
        }
        else if (m_eOutType == ScilabDouble)
        {
            pIT = new Double(1, m_iSize);
            extractFullMatrix(pIT->getAs<Double>());
        }
        else if (m_eOutType == ScilabInt8)
        {
            pIT	= new Int8(1, m_iSize);
            extractFullMatrix(pIT->getAs<Int8>());
        }
        else if (m_eOutType == ScilabUInt8)
        {
            pIT	= new UInt8(1, m_iSize);
            extractFullMatrix(pIT->getAs<UInt8>());
        }
        else if (m_eOutType == ScilabInt16)
        {
            pIT	= new Int16(1, m_iSize);
            extractFullMatrix(pIT->getAs<Int16>());
        }
        else if (m_eOutType == ScilabUInt16)
        {
            pIT	= new UInt16(1, m_iSize);
            extractFullMatrix(pIT->getAs<UInt16>());
        }
        else if (m_eOutType == ScilabInt32)
        {
            pIT	= new Int32(1, m_iSize);
            extractFullMatrix(pIT->getAs<Int32>());
        }
        else if (m_eOutType == ScilabUInt32)
        {
            pIT	= new UInt32(1, m_iSize);
            extractFullMatrix(pIT->getAs<UInt32>());
        }
        else if (m_eOutType == ScilabInt64)
        {
            pIT	= new Int64(1, m_iSize);
            extractFullMatrix(pIT->getAs<Int64>());
        }
        else if (m_eOutType == ScilabUInt64)
        {
            pIT	= new UInt64(1, m_iSize);
            extractFullMatrix(pIT->getAs<UInt64>());
        }
    }
    return pIT;
}

void ImplicitList::extractFullMatrix(Double *_p)
{
    double dblStart = m_poStart->getAs<Double>()->getFirst();
    double dblStep  = m_poStep->getAs<Double>()->getFirst();

    double* p = _p->get();
    for (int i = 0 ; i < m_iSize ; i++)
    {
        p[i] = dblStart + i * dblStep;
    }
}

template<typename T>
void ImplicitList::extractFullMatrix(T *_pT)
{
    typename T::type tStart = static_cast<typename T::type>(convert_input(m_poStart));
    typename T::type tStep = static_cast<typename T::type>(convert_input(m_poStep));

    typename T::type* p = _pT->get();
    for (int i = 0 ; i < m_iSize ; i++)
    {
        p[i] = tStart + i * tStep;
    }
}

bool ImplicitList::transpose(InternalType *& out)
{
    if (compute())
    {
        Double * pIT = new Double(m_iSize, 1);
        out = pIT;
        extractFullMatrix(pIT);

        return true;
    }

    return false;
}

bool ImplicitList::neg(InternalType *& out)
{
    if (compute() && m_poStart->isDouble() && m_poStep->isDouble() && m_poEnd->isDouble())
    {
        out = new Bool(1, m_iSize);
        type_traits::neg(m_poStart->getAs<Double>()->getFirst(), m_poStep->getAs<Double>()->getFirst(), m_poEnd->getAs<Double>()->getFirst(), static_cast<Bool *>(out)->get());

        return true;
    }

    return false;
}

bool ImplicitList::invoke(typed_list & in, optional_list & /*opt*/, int /*_iRetCount*/, typed_list & out, const ast::Exp & e)
{
    if (in.size() == 0)
    {
        out.push_back(this);
    }
    else
    {
        InternalType * _out = extract(&in);
        if (!_out)
        {
            throw ast::InternalError(2, e.getLocation());
        }
        out.push_back(_out);
    }

    return true;
}

InternalType* ImplicitList::extract(typed_list* _pArgs)
{
    int iDims = (int)_pArgs->size();

    if (iDims > 1)
    {
        // invalid index
        return NULL;
    }

    typed_list pArg;
    InternalType* pOut = NULL;

    int* piMaxDim = new int[iDims];

    //evaluate each argument and replace by appropriate value and compute the count of combinations
    int iSeqCount = checkIndexesArguments(this, _pArgs, &pArg, piMaxDim, NULL);

    delete[] piMaxDim;

    if (iSeqCount == 0)
    {
        // free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        return Double::Empty();
    }

    if (iSeqCount > 0)
    {
        bool bResultAsDoubleOrInteger = true;
        Double* arg = pArg[0]->getAs<Double>();
        double* idx1 = arg->get();
        InternalType* elem[iSeqCount];

        if (isComputable())
        {
            for (int i = 0; i < iSeqCount; ++i)
            {
                int idx0 = static_cast<int>(idx1[i]) - 1;

                if (idx0 < getSize())
                {
                    InternalType* Val = getInitialType();
                    extractValue(static_cast<int>(idx1[i]) - 1, Val);
                    elem[i] = Val;
                }
                else
                {
                    // invalid index
                    for (int j = 0; j < i; ++j)
                    {
                        delete elem[j];
                    }
                    cleanIndexesArguments(_pArgs, &pArg);
                    return NULL;
                }

                if (elem[i]->isPoly())
                {
                    bResultAsDoubleOrInteger = false;
                }
            }
        }
        else
        {
            for (int i = 0; i < iSeqCount; ++i)
            {
                switch (static_cast<int>(idx1[i]))
                {
                    case 1:
                        elem[i] = getStart();
                        break;
                    case 2:
                        elem[i] = getStep();
                        break;
                    case 3:
                        elem[i] = getEnd();
                        break;
                    default:
                        // invalid index
                        cleanIndexesArguments(_pArgs, &pArg);
                        return NULL;
                }

                if (elem[i]->isPoly())
                {
                    bResultAsDoubleOrInteger = false;
                }
            }
        }

        if (bResultAsDoubleOrInteger)
        {
            InternalType* pRes = NULL;

            switch (getOutputType())
            {
                case types::InternalType::ScilabInt8:
                    pRes = new Int8(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<Int8>()->set(i, elem[i]->getAs<Int8>()->getFirst());
                    }
                    break;
                case types::InternalType::ScilabUInt8:
                    pRes = new UInt8(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<UInt8>()->set(i, elem[i]->getAs<UInt8>()->getFirst());
                    }
                    break;
                case types::InternalType::ScilabInt16:
                    pRes = new Int16(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<Int16>()->set(i, elem[i]->getAs<Int16>()->getFirst());
                    }
                    break;
                case types::InternalType::ScilabUInt16:
                    pRes = new UInt16(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<UInt16>()->set(i, elem[i]->getAs<UInt16>()->getFirst());
                    }
                    break;
                case types::InternalType::ScilabInt32:
                    pRes = new Int32(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<Int32>()->set(i, elem[i]->getAs<Int32>()->getFirst());
                    }
                    break;
                case types::InternalType::ScilabUInt32:
                    pRes = new UInt32(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<UInt32>()->set(i, elem[i]->getAs<UInt32>()->getFirst());
                    }
                    break;
                case types::InternalType::ScilabInt64:
                    pRes = new Int64(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<Int64>()->set(i, elem[i]->getAs<Int64>()->getFirst());
                    }
                    break;
                case types::InternalType::ScilabUInt64:
                    pRes = new UInt64(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<UInt64>()->set(i, elem[i]->getAs<UInt64>()->getFirst());
                    }
                    break;
                //case types::InternalType::ScilabDouble:
                default:
                    pRes = new Double(arg->getDims(), arg->getDimsArray());
                    for (int i = 0; i < iSeqCount; ++i)
                    {
                        pRes->getAs<Double>()->set(i, elem[i]->getAs<Double>()->getFirst());
                    }
                    break;
            }

            pOut = pRes;
        }
        else
        {
            Polynom* pRes = new Polynom(L"$", arg->getDims(), arg->getDimsArray());
            SinglePoly* e = new SinglePoly();

            for (int i = 0; i < iSeqCount; ++i)
            {
                if (elem[i]->isPoly())
                {
                    pRes->set(i, elem[i]->getAs<Polynom>()->getFirst());
                }
                else
                {
                    double c = elem[i]->getAs<Double>()->getFirst();

                    e->setCoef(&c, NULL);
                    pRes->set(i, e);
                }
            }

            delete e;

            pOut = pRes;
        }

        if (isComputable())
        {
            for (int i = 0; i < iSeqCount; ++i)
            {
                delete elem[i];
            }
        }
    }

    // free pArg content
    cleanIndexesArguments(_pArgs, &pArg);

    return pOut;
}

ast::Exp * ImplicitList::getExp(const Location & loc)
{
    return new ast::DoubleExp(loc, this);
}

bool ImplicitList::isTrue()
{
    // TODO : manage int & co
    if (m_poStart->isDouble() && m_poStep->isDouble() && m_poEnd->isDouble())
    {
        return type_traits::isTrue(m_poStart->getAs<Double>()->getFirst(), m_poStep->getAs<Double>()->getFirst(), m_poEnd->getAs<Double>()->getFirst());
    }

    return false;
}

bool ImplicitList::getMemory(int* _piSize, int* _piSizePlusType)
{
    *_piSize = sizeof(ImplicitList);
    *_piSizePlusType = *_piSize;
    return true;
}

}

std::wstring printInLinePoly(types::SinglePoly* _pPoly, std::wstring _stVar)
{
    std::wostringstream ostr;
    double* pdblIn = _pPoly->get();
    for (int i = 0 ; i < _pPoly->getSize() ; i++)
    {
        if (pdblIn[i] != 0 || _pPoly->getSize() == 1)
        {
            DoubleFormat df;
            getDoubleFormat(pdblIn[i], &df);
            df.bPrintPoint = false;
            df.bPrintPlusSign = ostr.str().size() != 0;
            df.bPrintOne = i == 0;
            df.bPaddSign = false;
            df.bPrintBlank = false;

            addDoubleValue(&ostr, pdblIn[i], &df);
            if (i != 0)
            {
                ostr << _stVar;
                if (i > 1)
                {
                    ostr << "^" << i;
                }
            }
        }
    }
    return ostr.str();
}

std::wstring printDouble(types::Double* _pD)
{
    std::wostringstream ostr;
    DoubleFormat df;
    getDoubleFormat(_pD->getFirst(), &df);
    df.bPrintPoint = false;
    df.bPaddSign = false;
    df.bPrintBlank = false;
    addDoubleValue(&ostr, _pD->getFirst(), &df);
    return ostr.str();
}

long long convert_input(types::InternalType* _poIT)
{
    switch (_poIT->getType())
    {
        case types::InternalType::ScilabDouble:
            return static_cast<long long>(_poIT->getAs<types::Double>()->getFirst());
        case types::InternalType::ScilabInt8:
            return static_cast<long long>(_poIT->getAs<types::Int8>()->getFirst());
        case types::InternalType::ScilabUInt8:
            return static_cast<long long>(_poIT->getAs<types::UInt8>()->getFirst());
        case types::InternalType::ScilabInt16:
            return static_cast<long long>(_poIT->getAs<types::Int16>()->getFirst());
        case types::InternalType::ScilabUInt16:
            return static_cast<long long>(_poIT->getAs<types::UInt16>()->getFirst());
        case types::InternalType::ScilabInt32:
            return static_cast<long long>(_poIT->getAs<types::Int32>()->getFirst());
        case types::InternalType::ScilabUInt32:
            return static_cast<long long>(_poIT->getAs<types::UInt32>()->getFirst());
        case types::InternalType::ScilabInt64:
            return static_cast<long long>(_poIT->getAs<types::Int64>()->getFirst());
        case types::InternalType::ScilabUInt64:
            return static_cast<long long>(_poIT->getAs<types::UInt64>()->getFirst());
        default:
            return 0;
    }
    return 0;
}

unsigned long long convert_unsigned_input(types::InternalType* _poIT)
{
    switch (_poIT->getType())
    {
        case types::InternalType::ScilabDouble:
            return static_cast<unsigned long long>(_poIT->getAs<types::Double>()->getFirst());
        case types::InternalType::ScilabInt8:
            return static_cast<unsigned long long>(_poIT->getAs<types::Int8>()->getFirst());
        case types::InternalType::ScilabUInt8:
            return static_cast<unsigned long long>(_poIT->getAs<types::UInt8>()->getFirst());
        case types::InternalType::ScilabInt16:
            return static_cast<unsigned long long>(_poIT->getAs<types::Int16>()->getFirst());
        case types::InternalType::ScilabUInt16:
            return static_cast<unsigned long long>(_poIT->getAs<types::UInt16>()->getFirst());
        case types::InternalType::ScilabInt32:
            return static_cast<unsigned long long>(_poIT->getAs<types::Int32>()->getFirst());
        case types::InternalType::ScilabUInt32:
            return static_cast<unsigned long long>(_poIT->getAs<types::UInt32>()->getFirst());
        case types::InternalType::ScilabInt64:
            return static_cast<unsigned long long>(_poIT->getAs<types::Int64>()->getFirst());
        case types::InternalType::ScilabUInt64:
            return static_cast<unsigned long long>(_poIT->getAs<types::UInt64>()->getFirst());
        default:
            return 0;
    }
    return 0;
}
