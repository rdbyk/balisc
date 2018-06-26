/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include <list>
#include <vector>

#include "alltypes.hxx"
#include "types_tools.hxx"
#include "overload.hxx"
#include "scilabWrite.hxx"

extern "C"
{
#include "elem_common.h"
#include "os_string.h"
#include "more.h"
}

namespace types
{
template<typename T>
void getIndexes(T* val, std::vector<int>& vec)
{
    typename T::type* p = val->get();
    int size = val->getSize();
    for (int i = 0; i < size; ++i)
    {
        vec[i] = static_cast<int>(p[i]);
    }
}

template<typename T>
double getIndex(T* val)
{
    typename T::type* p = val->get();
    return static_cast<double>(p[0]);
}

template<typename T>
Double* convertIndex(T* pI)
{
    int size = pI->getSize();
    Double* pCurrentArg = new Double(1, size);
    double* pdbl = pCurrentArg->get();
    for (int l = 0; l < size; l++)
    {
        pdbl[l] = static_cast<double>(pI->get(l));
    }
    return pCurrentArg;
}

double getIndex(InternalType* val)
{
    switch (val->getType())
    {
        //scalar
        case InternalType::ScilabDouble:
        {
            return getIndex(val->getAs<Double>());
        }
        case InternalType::ScilabInt8:
        {
            return getIndex(val->getAs<Int8>());
        }
        case InternalType::ScilabInt16:
        {
            return getIndex(val->getAs<Int16>());
        }
        case InternalType::ScilabInt32:
        {
            return getIndex(val->getAs<Int32>());
        }
        case InternalType::ScilabInt64:
        {
            return getIndex(val->getAs<Int64>());
        }
        case InternalType::ScilabUInt8:
        {
            return getIndex(val->getAs<UInt8>());
        }
        case InternalType::ScilabUInt16:
        {
            return getIndex(val->getAs<UInt16>());
        }
        case InternalType::ScilabUInt32:
        {
            return getIndex(val->getAs<UInt32>());
        }
        case InternalType::ScilabUInt64:
        {
            return getIndex(val->getAs<UInt64>());
        }
    }

    return 0;
}

//get only scalar index
bool getArgsDims(typed_list* _pArgsIn, std::vector<int>& dims)
{
    //input size must be equal to ref dims
    int dimsIn = static_cast<int>(_pArgsIn->size());

    //same dims and less than internal limit
    if (dimsIn > MAX_DIMS)
    {
        return false;
    }

    dims.reserve(dimsIn);

    for (int i = 0; i < dimsIn; ++i)
    {
        InternalType* in = (*_pArgsIn)[i];
        //input arg type must be scalar double, int8, int16, ...
        if (in->isGenericType() && in->getAs<GenericType>()->isScalar())
        {
            int ind = static_cast<int>(getIndex(in));
            if (ind <= 0)
            {
                return false;
            }

            dims.push_back(ind);
        }
        else if (in->isImplicitList())
        {
            ImplicitList* pIL = in->getAs<ImplicitList>();
            if (pIL->isComputable() == false)
            {
                return false;
            }

            int size = pIL->getSize();
            if (size <= 0)
            {
                return false;
            }


            double start = getIndex(pIL->getStart());
            double step = getIndex(pIL->getStep());
            if (step > 0)
            {
                double real_end = start + step * (size - 1);
                dims.push_back(real_end);
            }
            else if (step < 0)
            {
                dims.push_back(start);
            }
            else
            {
                return false;
            }
        }
        else
        {
            //failed, so use entire process
            return false;
        }
    }


    // removing trailing dims with size 1
    while (dims.size() > 2 && dims.back() == 1)
    {
        dims.pop_back();
    }

    return true;
}


//get only scalar index
bool getScalarIndex(GenericType* _pRef, typed_list* _pArgsIn, int* index)
{
    //input size must be equal to ref dims
    int dimsRef = _pRef->getDims();
    int dimsIn = static_cast<int>(_pArgsIn->size());

    //same dims and less than internal limit
    if (dimsIn != 1 && (dimsIn != dimsRef || dimsIn > MAX_DIMS))
    {
        return false;
    }

    int* pdims = _pRef->getDimsArray();
    int previousDims = 1;
    *index = 0;
    for (int i = 0; i < dimsIn; ++i)
    {
        InternalType* in = (*_pArgsIn)[i];
        //input arg type must be scalar double, int8, int16, ...
        if (in->isGenericType() && in->getAs<GenericType>()->isScalar())
        {
            // FIXME: This handles non-finite index values by accident,
            // rather than by standards, because the casting result of a
            // non-finite double to int is in general *not* defined ...
            int ind = static_cast<int>(getIndex(in)) - 1;

            if (ind < 0 || (dimsIn != 1 && ind >= pdims[i]))
            {
                return false;
            }

            *index += ind * previousDims;
            previousDims *= pdims[i];
        }
        else
        {
            //failed, so use entire process
            return false;
        }
    }

    return true;
}

static double evalute(InternalType* pIT, int sizeRef)
{
    double real;
    double img;
    if (pIT->getId() == InternalType::IdScalarPolynom)
    {
        SinglePoly* pSP = pIT->getAs<Polynom>()->get()[0];
        pSP->evaluate(sizeRef, 0, &real, &img);
    }
    else
    {
        real = getIndex(pIT);
    }

    return real;
}

bool getScalarImplicitIndex(GenericType* _pRef, typed_list* _pArgsIn, std::vector<double>& index)
{
    int dimsIn = static_cast<int>(_pArgsIn->size());
    if (dimsIn != 1)
    {
        return false;
    }

    InternalType* pIT = (*_pArgsIn)[0];

    if (pIT->isImplicitList() == false)
    {
        return false;
    }

    if (pIT->isColon())
    {
        // an "index" of size 4 tells the caller that the implicit index
        // was a ":" colon, and he will accordingly shape the result as
        // column vector
        index.resize(4);
        index[0] = 1;
        index[1] = 1;
        index[2] = _pRef->getSize();
        //index[3] = 0; // useless, cf. above
    }
    else
    {
        ImplicitList* pIL = pIT->getAs<ImplicitList>();
        int sizeRef = _pRef->getSize();
        index.resize(3);
        index[0] = evalute(pIL->getStart(), sizeRef);
        index[1] = evalute(pIL->getStep(), sizeRef);
        index[2] = evalute(pIL->getEnd(), sizeRef);
    }

    return true;
}

//get index from implicit or colon index + scalar
bool getImplicitIndex(GenericType* _pRef, typed_list* _pArgsIn, std::vector<int>& index, std::vector<int>& dims)
{
    int dimsRef = _pRef->getDims();
    int dimsIn = static_cast<int>(_pArgsIn->size());
    bool viewAsVector = dimsIn == 1;
    dims.reserve(dimsIn);
    //same dims and less than internal limit
    if (dimsIn != 1 && (dimsIn != dimsRef || dimsIn > MAX_DIMS))
    {
        return false;
    }

    int* pdims = _pRef->getDimsArray();
    //input arg type must be computable ( double, $, :, ... )
    std::list<std::vector<int>> lstIdx;
    int finalSize = 1;
    for (int i = 0; i < dimsIn; ++i)
    {
        InternalType* in = (*_pArgsIn)[i];
        if (in->isGenericType() && in->getAs<GenericType>()->isScalar())
        {
            // FIXME: This handles non-finite index values by accident,
            // rather than by standards, because the casting result of a
            // non-finite double to int is in general *not* defined ...
            int idx = static_cast<int>(getIndex(in)) - 1;
            if (idx < 0)
            {
                return false;
            }

            lstIdx.emplace_back(1, idx);
            dims.push_back(1);
        }
        else if (in->isColon())
        {
            std::vector<int> idx {-1, viewAsVector ? _pRef->getSize() : pdims[i]};
            lstIdx.push_back(idx);
            finalSize *= idx[1];
            dims.push_back(idx[1]);
        }
        else if (in->isImplicitList())
        {
            ImplicitList* pIL = in->getAs<ImplicitList>();
            InternalType* piStart = pIL->getStart();
            InternalType* piStep = pIL->getStep();
            InternalType* piEnd = pIL->getEnd();

            bool isColon = false;
            if (piStart->isDouble() && piStep->isDouble() && piEnd->isPoly())
            {
                if (piStart->getAs<Double>()->get()[0] == 1 && piStep->getAs<Double>()->get()[0] == 1)
                {
                    SinglePoly* end = piEnd->getAs<Polynom>()->get()[0];
                    if (end->getRank() == 1 && end->get()[0] == 0 && end->get()[1] == 1)
                    {
                        std::vector<int> idx {-1, viewAsVector ? _pRef->getSize() : pdims[i]};
                        lstIdx.push_back(idx);
                        finalSize *= idx[1];
                        isColon = true;
                        dims.push_back(idx[1]);
                    }
                }
            }

            if (isColon == false)
            {
                int sizeRef = viewAsVector ? _pRef->getSize() : pdims[i];
                double start = evalute(pIL->getStart(), sizeRef);
                double step = evalute(pIL->getStep(), sizeRef);
                double end = evalute(pIL->getEnd(), sizeRef);

                double dsize = (end - start) / step + 1;
                int size = static_cast<int>(dsize);

                if (std::isnan(dsize) || start < 1 || start + (size - 1)*step < 1)
                {
                    wchar_t szError[bsiz];
                    os_swprintf(szError, bsiz, _W("Invalid index.\n").c_str());
                    throw ast::InternalError(szError);
                }

                if (size <= 0)
                {
                    //manage implicit that return []
                    index.clear();
                    return true;
                }

                std::vector<int> idx(size);

                double val = start - 1;

                idx[0] = (int)val;
                for (int i = 1; i < size; ++i)
                {
                    val += step;
                    idx[i] = (int)val;
                }

                lstIdx.push_back(idx);
                finalSize *= size;
                dims.push_back(size);
            }
        }
        else
        {
            return false;
        }
    }

    index.resize(finalSize, 0);

    if (finalSize == 0)
    {
        return true;
    }

    //compute tuples
    int previousSize = 1;
    int currentDim = 0;
    int previousDims = 1;
    int* p = index.data();
    while (lstIdx.empty() == false)
    {
        std::vector<int>& v = lstIdx.front();
        int currentSize = static_cast<int>(v.size());
        const int* pv = v.data();

        if (pv[0] == -1 && currentSize == 2)
        {
            currentSize = pv[1];
            int prodOfSizes = currentSize * previousSize;
            int occ = finalSize / prodOfSizes;
            for (int n = 0; n < occ; ++n)
            {
                int idx = prodOfSizes * n;
                for (int m = 0; m < currentSize; ++m)
                {
                    if (dimsIn > 1 && m >= pdims[currentDim])
                    {
                        return false;
                    }
                    int idx2 = idx + previousSize * m;
                    int idx3 = previousDims * m;
                    for (int j = 0; j < previousSize; ++j)
                    {
                        p[idx2 + j] += idx3;
                    }
                }
            }
        }
        else
        {
            int* p = index.data();
            int prodOfSizes = currentSize * previousSize;
            int occ = finalSize / prodOfSizes;
            for (int n = 0; n < occ; ++n)
            {
                int idx = prodOfSizes * n;
                for (int m = 0; m < currentSize; ++m)
                {
                    if (dimsIn > 1 && pv[m] >= pdims[currentDim])
                    {
                        return false;
                    }
                    int idx2 = idx + previousSize * m;
                    int idx3 = previousDims * pv[m];
                    for (int j = 0; j < previousSize; ++j)
                    {
                        p[idx2 + j] += idx3;
                    }
                }
            }
        }

        previousSize *= currentSize;
        previousDims *= pdims[currentDim];
        ++currentDim;
        //remove used vector
        lstIdx.pop_front();
    }

    return true;
}

//check argument types and compute, dimensions, count of combinations, max indexes
int checkIndexesArguments(InternalType* _pRef, typed_list* _pArgsIn, typed_list* _pArgsOut, int* _piMaxDim, int* _piCountDim)
{
    int iDims = static_cast<int>(_pArgsIn->size());
    int iSeqCount = 1;
    bool bUndefine = false;

    for (int i = 0; i < iDims; i++)
    {
        bool bDeleteNeeded = false;
        InternalType* pIT = (*_pArgsIn)[i];
        Double *pCurrentArg = NULL;

        if (pIT->isDouble())
        {
            pCurrentArg = pIT->getAs<Double>();
            if (pCurrentArg->isEmpty())
            {
                return 0;
            }

            if (pCurrentArg->isIdentity())
            {
                //extract with eye() <=> :
                pIT = new Colon();
                bDeleteNeeded = true;
            }
            else if (pIT->isDeletable())
            {
                // Clone pIT when this ref is equal to zero
                // will prevent double delete.
                pCurrentArg = pIT->clone()->getAs<Double>();
            }

            // check for valid index values
            // non-complex and real positive (non-negative for lists)
            if (pCurrentArg->isComplex())
            {
                pCurrentArg->killMe();
                pCurrentArg = NULL;
            }
            else
            {
                int size = pCurrentArg->getSize();
                double* idx = pCurrentArg->get();
                double min_idx = _pRef && _pRef->isList() ? 0 : 1;
                for (int j = 0; j < size; ++j)
                {
                    int idxj = idx[j];

                    if (idxj < min_idx || std::isnan(idxj))
                    {
                        pCurrentArg->killMe();
                        pCurrentArg = NULL;
                        break;
                    }
                }
            }
        }

        //previous  if can update pIT to Colon
        if (pIT->isColon() || pIT->isImplicitList())
        {
            //: or a:b:c
            ImplicitList* pIL = pIT->getAs<ImplicitList>()->clone()->getAs<ImplicitList>();
            if (pIL->isComputable() == false)
            {
                //: or $
                if (_pRef == NULL)
                {
                    //not enough information to compute indexes.
                    _pArgsOut->push_back(NULL);
                    bUndefine = true;
                    pIL->killMe();
                    continue;
                }
                //evalute polynom with "MaxDim"
                int iMaxDim = _pRef->getAs<GenericType>()->getVarMaxDim(i, iDims);
#if defined(_SCILAB_DEBUGREF_)
                Double* pdbl = new Double(iMaxDim);
#else
                Double dbl(iMaxDim);
#endif
                if (pIL->getStart()->isPoly())
                {
                    Polynom *poPoly = pIL->getStart()->getAs<types::Polynom>();
#if defined(_SCILAB_DEBUGREF_)
                    pIL->setStart(poPoly->evaluate(pdbl));
#else
                    pIL->setStart(poPoly->evaluate(&dbl));
#endif
                }
                if (pIL->getStep()->isPoly())
                {
                    Polynom *poPoly = pIL->getStep()->getAs<types::Polynom>();
#if defined(_SCILAB_DEBUGREF_)
                    pIL->setStep(poPoly->evaluate(pdbl));
#else
                    pIL->setStep(poPoly->evaluate(&dbl));
#endif
                }
                if (pIL->getEnd()->isPoly())
                {
                    Polynom *poPoly = pIL->getEnd()->getAs<types::Polynom>();
#if defined(_SCILAB_DEBUGREF_)
                    pIL->setEnd(poPoly->evaluate(pdbl));
#else
                    pIL->setEnd(poPoly->evaluate(&dbl));
#endif
                }

#if defined(_SCILAB_DEBUGREF_)
                pdbl->killMe();
#endif
            }


            pCurrentArg = pIL->extractFullMatrix()->getAs<Double>();
            pIL->killMe();
        }
        else if (pIT->isString())
        {
            String* pStr = pIT->getAs<String>();
            if(!_pRef)
            {
                bUndefine = true;
                continue;
            }
            if (_pRef->isStruct())
            {
                Struct* pStruct = _pRef->getAs<Struct>();

                if (_pArgsIn->size() != 1 || pStr->isScalar() == false)
                {
                    bUndefine = true;
                    continue;
                }

                wchar_t* pFieldName = pStr->getFirst();

                // pCurrent arg is indexed to 1 unlike the return of "getFieldIndex"
                int iIndex = pStruct->getFirst()->getFieldIndex(pFieldName) + 1;
                if (iIndex == -1)
                {
                    bUndefine = true;
                    continue;
                }

                pCurrentArg = new Double((double)iIndex);
            }
            else if (_pRef->isTList())
            {
                // List can't be extract by field and MList must call overload
                TList* pTL = _pRef->getAs<TList>();
                pCurrentArg = new Double(pStr->getDims(), pStr->getDimsArray());
                double* pdbl = pCurrentArg->get();
                for (int i = 0; i < pStr->getSize(); i++)
                {
                    wchar_t* pFieldName = pStr->get(i);
                    int iIndex = pTL->getFieldIndex(pFieldName);
                    if (iIndex == -1)
                    {
                        bUndefine = true;
                        continue;
                    }
                    pdbl[i] = (double)(iIndex + 1);
                }
            }
            else if (_pRef->isList())
            {
                bUndefine = true;
                break;
            }
            else if (_pRef->isCell())
            {
            }
        }
        else if (pIT->isPoly())
        {
            //$
            Polynom* pMP = pIT->getAs<types::Polynom>();
            int iMaxDim = 0;
            //if pRef == NULL, use 0 insteadof, to allow a($+1) on new variable
            if (_pRef)
            {
                iMaxDim = _pRef->getAs<GenericType>()->getVarMaxDim(i, iDims);
            }

#ifdef _SCILAB_DEBUGREF_
            Double* pdbl = new Double(iMaxDim); // $
            pCurrentArg = pMP->evaluate(pdbl);
            pdbl->killMe();
#else
            Double dbl(iMaxDim); // $
            pCurrentArg = pMP->evaluate(&dbl);
#endif
        }
        else if (pIT->isBool())
        {
            //[T F F T F]
            Bool *pB = pIT->getAs<types::Bool>();
            int *piB = pB->get();
            const int size = pB->getSize();

            //find true item count
            int iItemCount = 0;
            for (int j = 0; j < size; j++)
            {
                if (piB[j])
                {
                    iItemCount++;
                }
            }

            //allow new Double variable
            Double* pDbl = new Double(1, iItemCount);
            double* pdbl = pDbl->getReal();

            int j = 0;
            for (int l = 0; l < size; l++)
            {
                if (piB[l])
                {
                    pdbl[j++] = l + 1;
                }
            }
            pCurrentArg = pDbl;
        }
        else if (pIT->isSparseBool())
        {
            types::SparseBool* pSb = pIT->getAs<types::SparseBool>();
            int iItemCount = static_cast<int>(pSb->nbTrue());
            int iRows = pSb->getRows();
            int *pCoord = new int[iItemCount * 2];

            //get (r,c) positions of True Elements
            pSb->outputRowCol(pCoord);
            int* pY = pCoord + iItemCount;
            //allow new Double index variable
            Double* pDbl = new Double(1, iItemCount);
            double* pdbl = pDbl->getReal();
            for (int i = 0; i < iItemCount; ++i)
            {
                pdbl[i] = pCoord[i] + (pY[i] - 1) * iRows;
            }

            delete[] pCoord;
            pCurrentArg = pDbl;
        }
        else if (pIT->isInt())
        {
            switch (pIT->getType())
            {
                case InternalType::ScilabInt8:
                {
                    pCurrentArg = convertIndex(pIT->getAs<Int8>());
                    break;
                }
                case InternalType::ScilabInt16:
                {
                    pCurrentArg = convertIndex(pIT->getAs<Int16>());
                    break;
                }
                case InternalType::ScilabInt32:
                {
                    pCurrentArg = convertIndex(pIT->getAs<Int32>());
                    break;
                }
                case InternalType::ScilabInt64:
                {
                    pCurrentArg = convertIndex(pIT->getAs<Int64>());
                    break;
                }
                case InternalType::ScilabUInt8:
                {
                    pCurrentArg = convertIndex(pIT->getAs<UInt8>());
                    break;
                }
                case InternalType::ScilabUInt16:
                {
                    pCurrentArg = convertIndex(pIT->getAs<UInt16>());
                    break;
                }
                case InternalType::ScilabUInt32:
                {
                    pCurrentArg = convertIndex(pIT->getAs<UInt32>());
                    break;
                }
                case InternalType::ScilabUInt64:
                {
                    pCurrentArg = convertIndex(pIT->getAs<UInt64>());
                    break;
                }
            }
        }

        if (bDeleteNeeded)
        {
            pIT->killMe();
        }

        if (pCurrentArg)
        {
            const int iCountDim = pCurrentArg->getSize();
            _piMaxDim[i] = 0;
            for (int j = 0; j < iCountDim; j++)
            {
                //checks if size < size(int)
                if (pCurrentArg->get(j) >= INT_MAX)
                {
                    wchar_t szError[bsiz];
                    os_swprintf(szError, bsiz, _W("variable size exceeded : less than %d expected.\n").c_str(), INT_MAX);
                    throw ast::InternalError(szError);
                }

                int d = static_cast<int>(pCurrentArg->get(j));
                if (d > _piMaxDim[i])
                {
                    _piMaxDim[i] = d;
                }
            }

            iSeqCount *= iCountDim;
            if (_piCountDim)
            {
                _piCountDim[i] = iCountDim;
            }
        }
        else
        {
            wchar_t szError[bsiz];
            os_swprintf(szError, bsiz, _W("Invalid index.\n").c_str());

            delete[] _piMaxDim;
            delete[] _piCountDim;
            cleanIndexesArguments(_pArgsIn, _pArgsOut);

            throw ast::InternalError(szError);
        }
        _pArgsOut->push_back(pCurrentArg);

    }


    //return 0 to force extract to create an empty matrix
    if (_pRef &&
            (_pRef->isDouble() && _pRef->getAs<Double>()->isEmpty()))
    {
        return 0;
    }

    //returns a negative value if at least one parameter is undefined
    //case with : or $ for creation by insertion
    return (!bUndefine ? iSeqCount : -iSeqCount);
}

void cleanIndexesArguments(typed_list* _pArgsOrig, typed_list* _pArgsNew)
{
    if (_pArgsNew)
    {
        //free pArg content
        for (int iArg = 0; iArg < _pArgsNew->size(); iArg++)
        {
            if ((*_pArgsNew)[iArg] != (*_pArgsOrig)[iArg])
            {
                if ((*_pArgsNew)[iArg])
                {
                    (*_pArgsNew)[iArg]->killMe();
                }
            }
        }

        _pArgsNew->clear();
    }
}

void getIndexesWithDims(int _iIndex, int* _piIndexes, const int* _piDims, int _iDims)
{
    if (_iDims == 2)
    {
        int iDim0 = _piDims[0];
        _piIndexes[0] = _iIndex % iDim0;
        _piIndexes[1] = (_iIndex / iDim0) % _piDims[1];
    }
    else
    {
        int iMul = 1;

        for (int i = 0; i < _iDims; i++)
        {
            _piIndexes[i] = (int)(_iIndex / iMul) % _piDims[i];
            iMul *= _piDims[i];
        }
    }

    //matrix [2,4,3]
    //index = 12 ( 0,2,1) = 1 * 4 * 2 + 2 * 2 + 0 = 12
    //loop 1
    // (12 / 1) % 2 -> 0
    //loop 2
    // (12 / 2) % 4 -> 2
    //loop 3
    // (12 / 8) % 3 -> 1

    //matrix [3,4,3]
    //index = 22
    //loop 1
    // (22 / 1) % 3 -> 1
    //loop 2
    // (22 / 3) % 4 -> 3
    //loop 3
    // (22 / 12) % 3 -> 1

    //matrix [3,4,3]
    //index = 35
    //loop 1
    // (35 / 1) % 3 -> 2
    //loop 2
    // (35 / 3) % 4 -> 3
    //loop 3
    // (35 / 12) % 3 -> 2
}


int getIndexWithDims(int* _piIndexes, const int* _piDims, int _iDims)
{
    if (_iDims == 2)
    {
        return _piIndexes[0] + _piIndexes[1] * _piDims[0];
    }
    else
    {
        int idx = 0;
        int iMult = 1;

        for (int i = 0; i < _iDims; i++)

        {
            idx += _piIndexes[i] * iMult;
            iMult *= _piDims[i];
        }

        return idx;
    }
}

types::Function::ReturnValue VariableToString(types::InternalType* pIT, const wchar_t* wcsVarName)
{
    if (pIT->hasToString() == false)
    {
        //call overload %type_p
        types::typed_list in;
        types::typed_list out;

        pIT->IncreaseRef();
        in.push_back(pIT);

        try
        {
            types::Function::ReturnValue ret = Overload::generateNameAndCall(L"p", in, 1, out);
            pIT->DecreaseRef();
            return ret;
        }
        catch (const ast::InternalError &ie)
        {
            pIT->DecreaseRef();
            throw ie;
        }
    }
    else
    {
        std::wostringstream ostr;
        if (pIT->isList() || (pIT->isCallable() && pIT->isFunction() == false))
        {
            ostr << wcsVarName;
        }

        //to manage lines information
        int iLines = ConfigVariable::getConsoleLines();

        bool bFinish = false;
        do
        {
            //block by block
            bFinish = pIT->toString(ostr);
            if (ConfigVariable::isError())
            {
                ConfigVariable::resetError();
                ostr.str(L"");
                ConfigVariable::resetExecutionBreak();
                return types::Function::Error;
            }

            if (bFinish == false && iLines != 0)
            {
                //show message on prompt
                bFinish = linesmore() == 1;
            }

            if (ConfigVariable::isPrintCompact() == false && ConfigVariable::isPrintInput() == false)
            {
                ostr << L"\n";
            }

            scilabForcedWriteW(ostr.str().c_str());
            ostr.str(L"");
        }
        while (bFinish == false && ConfigVariable::isExecutionBreak() == false);

        if (bFinish == false)
        {
            ConfigVariable::resetExecutionBreak();
        }
        pIT->clearPrintState();
        return types::Function::OK;
    }
}

//n-uplet in french
int computeTuples(int* _piCountDim, int _iCurrentDim, int* _piIndex)
{
    //if bRet == 1, previous dims has reach max value.
    int iRet = 0;

    if (_iCurrentDim == 0)
    {
        //last dims
        if (_piIndex[_iCurrentDim] >= _piCountDim[_iCurrentDim])
        {
            _piIndex[_iCurrentDim] = 0;
            return 1;
        }
    }
    else
    {
        iRet = computeTuples(_piCountDim, _iCurrentDim - 1, _piIndex);
        if (iRet)
        {
            _piIndex[_iCurrentDim]++;
            if (_piIndex[_iCurrentDim] >= _piCountDim[_iCurrentDim])
            {
                _piIndex[_iCurrentDim] = 0;
                return 1;
            }
        }
    }
    return 0;
}

Double* createDoubleVector(int _iSize)
{
    int piDims[] = {1, _iSize};
    Double* pOut = new Double(2, piDims);
    double* pd = pOut->get();

    for (int i = 0; i < _iSize; i++)
    {
        pd[i] = i + 1;
    }
    return pOut;
}

bool checkArgValidity(typed_list& _Arg)
{
    for (int i = 0; i < (int)_Arg.size(); i++)
    {
        if (_Arg[i]->isDouble() == false)
        {
            return false;
        }

        Double* pDbl = _Arg[i]->getAs<Double>();
        double* pdbl = pDbl->get();
        for (int j = 0; j < pDbl->getSize(); j++)
        {
            if (pdbl[j] <= 0)
            {
                return false;
            }
        }
    }

    return true;
}

}
