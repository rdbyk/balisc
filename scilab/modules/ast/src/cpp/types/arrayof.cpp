/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
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

#include <cstring>

#include "arrayof.hxx"
#include "double.hxx"
#include "bool.hxx"
#include "singlepoly.hxx"
#include "singlestruct.hxx"
#include "type_traits.hxx"
#include "exp.hxx"
#include "types_tools.hxx"

namespace types
{

static int get_max_size(int* _piDims, int _iDims)
{
    if (_iDims == 0)
    {
        return 0;
    }

    int iMax = _piDims[0];
    for (int i = 1; i < _iDims; i++)
    {
        iMax *= _piDims[i];
    }
    return iMax;
}

template <typename T>
GenericType* ArrayOf<T>::createEmpty()
{
    return Double::Empty();
}

template <typename T>
bool ArrayOf<T>::getMemory(int* _piSize, int* _piSizePlusType)
{
    *_piSize = getSize() * sizeof(T) * (isComplex() ? 2 : 1);
    *_piSizePlusType = *_piSize + sizeof(*this);
    return true;
}

template <typename T>
void ArrayOf<T>::getIndexes(int _iIndex, int* _piIndexes)
{
    getIndexesWithDims(_iIndex, _piIndexes, m_piDims, m_iDims);
}

template <typename T>
ArrayOf<T>* ArrayOf<T>::insert(typed_list* _pArgs, InternalType* _pSource)
{
    ArrayOf<T>* pIT = checkRef(this, &ArrayOf::insert, _pArgs, _pSource);
    if (pIT != this)
    {
        return pIT;
    }

    int index;
    if (getScalarIndex(this, _pArgs, &index))
    {
        ArrayOf* pIns = _pSource->getAs<ArrayOf>();
        int sizeIn = pIns->getSize();
        //only scalar can be used to ".=" operation
        if (sizeIn != 1)
        {
            return NULL;
        }

        T* pRealData = pIns->get();
        T* pImgData = pIns->getImg();

        if (isComplex() == false && pIns->isComplex() == false)
        {
            if (isNativeType() && index < m_iSize)
            {
                m_pRealData[index] = *pRealData;
                return this;
            }
            else
            {
                if (has(index))
                {
                    set(index, *pRealData);
                    return this;
                }
            }
        }

        //if complex continue
    }

    std::vector<int> indexes;
    std::vector<int> dims;
    if (getImplicitIndex(this, _pArgs, indexes, dims))
    {
        if (indexes.size() == 0)
        {
            return this;
        }

        ArrayOf* pIns = _pSource->getAs<ArrayOf>();
        int sizeIn = pIns->getSize();
        int count = static_cast<int>(indexes.size());
        //only scalar can be used to ".=" operation
        if (sizeIn != 1 && count != sizeIn)
        {
            return NULL;
        }

        T* pRealData = pIns->get();
        T* pImgData = pIns->getImg();

        bool status = true;
        if (isComplex() == false && pIns->isComplex() == false)
        {
            if (sizeIn == 1)
            {
                if (isNativeType())
                {
                    for (int i : indexes)
                    {
                        if (i >= m_iSize)
                        {
                            status = false;
                            break;
                        }

                        m_pRealData[i] = *pRealData;
                    }
                }
                else
                {
                    for (int i : indexes)
                    {
                        if (!has(i))
                        {
                            status = false;
                            break;
                        }
                        set(i, *pRealData);
                    }
                }
            }
            else
            {
                if (isNativeType())
                {
                    for (int i : indexes)
                    {
                        if (i >= m_iSize)
                        {
                            status = false;
                            break;
                        }

                        m_pRealData[i] = *pRealData;
                        ++pRealData;
                    }
                }
                else
                {
                    for (int i : indexes)
                    {
                        if (!has(i))
                        {
                            status = false;
                            break;
                        }
                        set(i, *pRealData);
                        ++pRealData;
                    }
                }
            }

            if (status)
            {
                return this;
            }

            //if status is false, continue to entire process
        }
    }

    typed_list pArg;
    int iDims = (int)_pArgs->size();
    int* piMaxDim = new int[iDims];
    int* piCountDim = new int[iDims];

    //evaluate each argument and replace by appropriate value and compute the count of combinations
    int iSeqCount = checkIndexesArguments(this, _pArgs, &pArg, piMaxDim, piCountDim);
    if (iSeqCount == 0)
    {
        //free pArg content
        delete[] piCountDim;
        delete[] piMaxDim;
        cleanIndexesArguments(_pArgs, &pArg);
        return this;
    }

    ArrayOf* pSource = _pSource->getAs<ArrayOf>();

    //only scalar can be used to ".=" operation
    if (iSeqCount != pSource->getSize() && pSource->isScalar() == false)
    {
        return NULL;
    }

    // removing trailing dims of size 1
    while (iDims > m_iDims && piMaxDim[iDims - 1] == 1)
    {
        --iDims;
        pArg.back()->killMe();
        pArg.pop_back();
    }

    // check if resize is needed
    bool bNeedToResize = false;
    int* piNewDims = NULL;
    int iNewDims = 0;

    if (iDims >= m_iDims)
    {
        //all case are good, we can do almost everything
        //check if resize is needed
        if (iDims > m_iDims)
        {
            bNeedToResize = true;
        }
        else //_iDims == m_iDims
        {
            for (int i = 0; i < m_iDims; i++)
            {
                if (m_piDims[i] < piMaxDim[i])
                {
                    bNeedToResize = true;
                    break;
                }
            }
        }

        //determine new dimension of the matrix
        if (bNeedToResize == true)
        {
            iNewDims = iDims;
            piNewDims = new int[iNewDims];

            int i = 0;
            for ( ; i < m_iDims; i++)
            {
                piNewDims[i] = std::max(piMaxDim[i], m_piDims[i]);
            }

            for ( ; i < iNewDims; ++i)
            {
                piNewDims[i] = piMaxDim[i];
            }
        }
    }
    else // _iDims < m_iDims
    {
        if (isVector() || getSize() == 0) //getSize() == 0, only for [] and {}
        {
            if (getSize() < piMaxDim[0])
            {
                bNeedToResize = true;
                iNewDims = 2;
                piNewDims = new int[2]{1,1};

                if (isScalar() || getSize() == 0)
                {
                    int *piSourceDims = pSource->getDimsArray();
                    // if source is scalar then resize indexed array as a column vector
                    // otherwise resize with shape of source
                    piNewDims[(int)(piSourceDims[0] == 1 && pSource->getSize()>1)]=piMaxDim[0];
                }
                else // resize with same shape as indexed array
                {
                    piNewDims[(int)(getRows() == 1)]=piMaxDim[0];
                }
            }
        }
        else
        {
            //each index before last index must be in range of his dimension
            //and last given dimension can not be > prod(last dimensions)
            for (int i = 0; i < iDims - 1; i++)
            {
                //indexes are always doubles
                double* pIdx = pArg[i]->getAs<Double>()->get();
                //InternalType* pVar = pArg[i];
                //double* pIdx = static_cast<double*>(pVar->getAs<Double>()->get());
                int iSize = pArg[i]->getAs<ArrayOf>()->getSize();
                for (int j = 0; j < iSize; j++)
                {
                    if (pIdx[j] > m_piDims[i])
                    {
                        delete[] piCountDim;
                        delete[] piMaxDim;
                        //free pArg content
                        cleanIndexesArguments(_pArgs, &pArg);
                        return NULL;
                    }
                }
            }

            //check last dim
            int iMaxLastDim = getVarMaxDim(iDims - 1, iDims);
            double* pIdx = pArg[pArg.size() - 1]->getAs<Double>()->get();
            //InternalType* pVar = pArg[pArg.size() - 1];
            //double* pIdx = static_cast<double*>(pVar->getAs<Double>()->get());
            int iSize = pArg[pArg.size() - 1]->getAs<GenericType>()->getSize();
            for (int i = 0; i < iSize; i++)
            {
                if (pIdx[i] > iMaxLastDim)
                {
                    delete[] piCountDim;
                    delete[] piMaxDim;
                    //free pArg content
                    cleanIndexesArguments(_pArgs, &pArg);
                    return NULL;
                }
            }
        }
    }

    //update complexity *before* first resizing
    if (pSource->isComplex() && m_pImgData == NULL)
    {
        setComplex(true);
    }

    //before resize, check input dimension
    if (bNeedToResize)
    {
        resize(piNewDims, iNewDims);
        delete[] piNewDims;
        piNewDims = NULL;
    }

    int argSize = static_cast<int>(pArg.size());
    int* piIndex = new int[argSize]();
    int* piCoord = new int[argSize];
    int* piViewDims = new int[iDims];

    //convert  current dimension to view dimension
    for (int i = 0; i < iDims; i++)
    {
        piViewDims[i] = getVarMaxDim(i, iDims);
    }

    T* pRealData = pSource->get();
    T* pImgData = pSource->getImg();
    bool bComplex = pSource->isComplex();

    for (int i = 0; i < iSeqCount; i++)
    {
        computeTuples(piCountDim, argSize - 1, piIndex);

        //std::cout << "[";
        for (int j = 0; j < argSize; j++)
        {
            piCoord[j] = static_cast<int>(pArg[j]->getAs<Double>()->get(piIndex[j])) - 1;
        }

        //std::cout << "]" << std::endl;

        int iPos = getIndexWithDims(piCoord, piViewDims, iDims);
        if (iPos < 0)
        {
            delete[] piMaxDim;
            delete[] piCountDim;
            delete[] piIndex;
            delete[] piCoord;
            delete[] piViewDims;

            //free pArg content
            cleanIndexesArguments(_pArgs, &pArg);
            throw ast::InternalError(2);
        }

        if (pSource->isScalar())
        {
            //element-wise insertion
            set(iPos, pRealData[0]);
            if (pImgData != NULL && bComplex)
            {
                setImg(iPos, pImgData[0]);
            }
        }
        else
        {
            set(iPos, pRealData[i]);
            if (pImgData != NULL && bComplex)
            {
                setImg(iPos, pImgData[i]);
            }
        }

        // reset imaginary part
        if (m_pImgData != NULL && bComplex == false)
        {
            setImg(iPos, 0);
        }

        //update index
        piIndex[0]++;
    }

    delete[] piMaxDim;
    delete[] piCountDim;
    delete[] piIndex;
    delete[] piCoord;
    delete[] piViewDims;

    //free pArg content
    cleanIndexesArguments(_pArgs, &pArg);

    return this;
}

template <typename T>
GenericType* ArrayOf<T>::insertNew(typed_list* _pArgs)
{
    bool bComplex = getImg() != NULL;
    std::vector<int> dims;

    if (getArgsDims(_pArgs, dims))
    {
        InternalType *pOut = NULL;

        if (dims.size() == 1 && getDims() == 2)
        {
            if (getCols() != 1)
            {
                dims.insert(dims.begin(), 1);
            }
            else
            {
                dims.push_back(1);
            }
        }

        while (dims.size() < 2)
        {
            dims.push_back(1);
        }

        pOut = createEmpty((int)dims.size(), dims.data(), bComplex);
        ArrayOf* pArrayOut = pOut->getAs<ArrayOf>();
        pArrayOut->fillDefaultValues();
        ArrayOf* pOut2 = pArrayOut->insert(_pArgs, this);
        if (pOut != pOut2)
        {
            delete pOut;
        }

        return pOut2;
    }

    typed_list pArg;
    InternalType *pOut = NULL;

    int iDims = (int)_pArgs->size();
    int* piMaxDim = new int[iDims];
    int* piCountDim = new int[iDims];

    //evaluate each argument and replace by appropriate value and compute the count of combinations
    int iSeqCount = checkIndexesArguments(NULL, _pArgs, &pArg, piMaxDim, piCountDim);

    if (iSeqCount == 0)
    {
        delete[] piMaxDim;
        delete[] piCountDim;
        //free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        return Double::Empty();
    }

    if (iSeqCount < 0)
    {
        //manage : and $ in creation by insertion
        int iSourceDims = getDims();
        int *piSourceDims = new int[iSourceDims];
        std::memcpy(piSourceDims, getDimsArray(), iSourceDims * sizeof(int));
        int iSource = 0;
        int iNbColon = 0;
        for (int i = 0; i < iDims; ++i)
        {
            if (pArg[i] == NULL)
            {
                ++iNbColon;
            }
        }

        if (iNbColon == iDims)
        {
            delete[] piMaxDim;
            delete[] piCountDim;
            //free pArg content
            cleanIndexesArguments(_pArgs, &pArg);
            return this;
        }

        //vector case
        if (iNbColon == 1 && isVector())
        {
            iSourceDims = 1;
            piSourceDims[0] = getSize();
        }
        
        //vector or matrix case
        for (int i = 0; i < iDims; ++i)
        {
            //if these do not match another following explicit index, replace ":" by known source dimensions
            if (pArg[i] == NULL)
            {
                if (iSource < iSourceDims)
                {
                    //by default, replace colon by current source dimension
                    piMaxDim[i] = piSourceDims[iSource];
                    //if there are more index dimensions left than source dimensions left
                    if (iDims-i > iSourceDims-iSource)
                    {
                        for (int j = i+1; j < iDims - iSourceDims + iSource +1; ++j)
                        {
                            //when first explicit index is reached
                            if (pArg[j] != NULL)
                            {
                                //if future index #j and current source dimensions match
                                if (piCountDim[j] == piSourceDims[iSource])
                                {
                                    piMaxDim[i] = 1;
                                    --iSource;
                                }
                                break;
                            }
                        }
                    }
                    ++iSource;
                }
                else
                {
                    //fill dimensions after iSourceDims with 1
                    piMaxDim[i] = 1;
                }
                pArg[i] = createDoubleVector(piMaxDim[i]);
                --iNbColon;
            }
            else if (piCountDim[i] == piSourceDims[iSource] && (piCountDim[i]>1 || iNbColon < iSourceDims))
            {
                ++iSource;
            }
        }

        delete [] piSourceDims;
    }

    // removing trailing dims of size 1
    while (iDims > 2 && piMaxDim[iDims - 1] == 1)
    {
        --iDims;
        pArg.back()->killMe();
        pArg.pop_back();
    }

    if (checkArgValidity(pArg) == false)
    {
        delete[] piMaxDim;
        delete[] piCountDim;
        //free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        //contain bad index, like <= 0, ...
        return NULL;
    }

    if (iDims == 1)
    {
        if (getCols() == 1)
        {
            int piRealDim[2] = {piMaxDim[0], 1};
            pOut = createEmpty(2, piRealDim, bComplex);
        }
        else
        {
            //rows == 1
            int piRealDim[2] = {1, piMaxDim[0]};
            pOut = createEmpty(2, piRealDim, bComplex);
        }
    }
    else
    {
        pOut = createEmpty(iDims, piMaxDim, bComplex);
    }

    //fill with null item
    ArrayOf* pArrayOut = pOut->getAs<ArrayOf>();
    pArrayOut->fillDefaultValues();
    //T* pRealData = pArrayOut->get();
    //if (bComplex)
    //{
    //    int size = pArrayOut->getSize();
    //    T* pImgData = pArrayOut->getImg();

    //    if (isNativeType())
    //    {
    //        T val = getNullValue();
    //        for (int i = 0; i < size; i++)
    //        {
    //            pRealData[i] = val;
    //            pImgData[i] = val;
    //        }
    //    }
    //    else
    //    {
    //        for (int i = 0; i < size; i++)
    //        {
    //            pArrayOut->deleteData(pRealData[i]);
    //            pRealData[i] = getNullValue();
    //            pArrayOut->deleteData(pImgData[i]);
    //            pImgData[i] = getNullValue();
    //        }
    //    }
    //}
    //else
    //{
    //    int size = pArrayOut->getSize();
    //    if (isNativeType())
    //    {
    //        T val = getNullValue();
    //        for (int i = 0; i < size; i++)
    //        {
    //            pRealData[i] = val;
    //        }
    //    }
    //    else
    //    {
    //        for (int i = 0; i < size; i++)
    //        {
    //            pArrayOut->deleteData(pRealData[i]);
    //            pRealData[i] = getNullValue();
    //        }
    //    }
    //}

    //insert values in new matrix
    ArrayOf* pOut2 = pArrayOut->insert(&pArg, this);
    if (pOut != pOut2)
    {
        delete pOut;
    }

    delete[] piMaxDim;
    delete[] piCountDim;
    //free pArg content
    cleanIndexesArguments(_pArgs, &pArg);

    return pOut2;
}

template <typename T>
void ArrayOf<T>::append(int _iRows, int _iCols, InternalType* _poSource)
{
    ArrayOf * pGT = _poSource->getAs<ArrayOf>();
    int iRows = pGT->getRows();
    int iCols = pGT->getCols();

    //insert without resize
    if (iRows + _iRows > m_iRows || iCols + _iCols > m_iCols)
    {
        return;
    }

    if (pGT->isComplex() && !isComplex())
    {
        setComplex(true);
    }

    if (m_pImgData)
    {
        if (pGT->m_pImgData)
        {
            for (int i = 0; i < iRows; i++)
            {
                int r = _iRows + i;
                for (int j = 0; j < iCols; j++)
                {
                    int c = _iCols + j;
                    set(r, c, pGT->get(i, j));
                    setImg(r, c, pGT->getImg(i, j));
                }
            }
        }
        else
        {
            for (int i = 0; i < iRows; i++)
            {
                int r = _iRows + i;
                for (int j = 0; j < iCols; j++)
                {
                    int c = _iCols + j;
                    set(r, c, pGT->get(i, j));
                    setImg(r, c, getNullValue());
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < iRows; i++)
        {
            int r = _iRows + i;
            for (int j = 0; j < iCols; j++)
            {
                set(r, _iCols + j, pGT->get(i, j));
            }
        }
    }
}

template <typename T>
GenericType* ArrayOf<T>::remove(typed_list* _pArgs)
{
    ArrayOf<T>* pOut = NULL;
    int iDims = (int)_pArgs->size();
    typed_list pArg;

    int* piMaxDim = new int[iDims];
    int* piCountDim = new int[iDims];

    //evaluate each argument and replace by appropriate value and compute the count of combinations
    int iSeqCount = checkIndexesArguments(this, _pArgs, &pArg, piMaxDim, piCountDim);
    delete[] piMaxDim;
    delete[] piCountDim;
    if (iSeqCount == 0)
    {
        //free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        //no Seq, no change but no error.
        return this;
    }

    int iToDelIndex = -1;
    std::vector<int> toDelIndexVect;
    std::vector<int> viewDims;
    viewDims.reserve(iDims);

    // dimensions not subject to deletion must be indexed with colon or equivalent
    for (int i = 0; i < iDims; i++)
    {
        int iDimToCheck = getVarMaxDim(i, iDims);
        viewDims[i] = iDimToCheck;
        int iIndexSize = pArg[i]->getAs<GenericType>()->getSize();
        if ((*_pArgs)[i]->isColon() == false)
        {
            //if equivalent to colon, should be 1:iDimToCheck after sorting and removing duplicates
            double* pIndexes = pArg[i]->getAs<Double>()->get();
            std::vector<int> pIndexesVect(pIndexes, pIndexes + iIndexSize);
            std::sort(pIndexesVect.begin(),pIndexesVect.end());
            pIndexesVect.erase(std::unique(pIndexesVect.begin(), pIndexesVect.end()), pIndexesVect.end());
            //remove index > iDimToCheck to allow a[10, 10](1, 1:100) = [] and a[10, 10]([1 5 20], :) = []
            auto lastUnique = std::find(pIndexesVect.begin(), pIndexesVect.end(), iDimToCheck);
            if (lastUnique != pIndexesVect.end())
            {
                pIndexesVect.erase(++lastUnique, pIndexesVect.end());
            }

            if (pIndexesVect.size() != iDimToCheck || pIndexesVect.front() != 1 || pIndexesVect.back() != iDimToCheck)
            {
                if (iToDelIndex < 0)
                {
                    iToDelIndex = i;
                    toDelIndexVect = pIndexesVect;
                }
                else
                {
                    //free pArg content
                    cleanIndexesArguments(_pArgs, &pArg);
                    return NULL;
                }
            }
        }
    }

    // overall removal x(:,...,:) = []
    if (iToDelIndex < 0)
    {
        int piDims[2] = {0,0};
        pOut = createEmpty(2,piDims,false);
        return pOut;
    }

    // check eventual out of bounds indexes
    int iKeepSize = viewDims[iToDelIndex];
    if (toDelIndexVect.front() < 1 || toDelIndexVect.back() > iKeepSize)
    {
        //free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        return NULL;
    }

    int iNewDimSize = iKeepSize - toDelIndexVect.size();

    int* piNewDims = new int[iDims];
    for (int i = 0; i < iDims; i++)
    {
        piNewDims[i] = viewDims[i];
    }
    piNewDims[iToDelIndex] = iNewDimSize;

    int iOrigDims = iDims;

    // removing trailing dims of size 1
    while (iDims > 2 && piNewDims[iDims - 1] == 1)
    {
        --iDims;
    }

    if (iDims == 1)
    {
        //two cases, depends of original matrix/vector
        if ((*_pArgs)[0]->isColon() == false && m_iDims == 2 && m_piDims[0] == 1 && m_piDims[1] != 1)
        {
            //special case for row vector
            int piRealDim[2] = {1, iNewDimSize};
            //in this case we have to care of 2nd dimension
            //iToDelIndex = 1;
            pOut = createEmpty(2, piRealDim, m_pImgData != NULL);
        }
        else
        {
            int piRealDim[2] = {iNewDimSize, 1};
            pOut = createEmpty(2, piRealDim, m_pImgData != NULL);
        }
    }
    else
    {
        pOut = createEmpty(iDims, piNewDims, m_pImgData != NULL);
    }

    // find a way to copy existing data to new variable ...

    // indexes to remove -> [ 0, toDelIndexVect, piViewDims[iToDelIndex]+1 ] to facilitate loop
    toDelIndexVect.insert(toDelIndexVect.begin(), 0);
    toDelIndexVect.push_back(viewDims[iToDelIndex] + 1);

    // Offsets
    int iOffset1 = 1;
    for (int i = 0; i < iToDelIndex; ++i)
    {
        iOffset1 = viewDims[i] * iOffset1;
    }
    int iOffset2 = viewDims[iToDelIndex] * iOffset1;

    int iNbChunks = getSize()/iOffset2;

    // fast algorithm (allowing in place removal if necessary)
    if (isNativeType())
    {
        for (int k = 0, iDest = 0; k < iNbChunks; k++)
        {
            int iStart = k*iOffset2;
            // loop on indexes to remove
            for (int j = 0; j < toDelIndexVect.size()-1; j++)
            {
                int iSize = (toDelIndexVect[j+1]-toDelIndexVect[j]-1)*iOffset1;
                memcpy(pOut->m_pRealData + iDest, m_pRealData + iStart, iSize*sizeof(T));

                if (m_pImgData != NULL)
                {
                    memcpy(pOut->m_pImgData + iDest, m_pImgData + iStart, iSize*sizeof(T));
                }

                iDest += iSize;
                iStart += iSize + iOffset1;
            }
        }
    }
    else
    {
        for (int k = 0, iDest = 0; k < iNbChunks; k++)
        {
            int iStart = k*iOffset2;
            // loop on indexes to remove
            for (int j = 0; j < toDelIndexVect.size()-1; j++)
            {
                int iSize =  (toDelIndexVect[j+1]-toDelIndexVect[j]-1)*iOffset1;

                for (int i = iStart; i < iStart+iSize; i++, iDest++)
                {
                    pOut->set(iDest,get(i));
                }

                if (m_pImgData != NULL)
                {
                    iDest -= iSize;

                    for (int i = iStart; i < iStart+iSize; i++, iDest++)
                    {
                        pOut->setImg(iDest,getImg(i));
                    }
                }

                iStart += iSize + iOffset1;
            }
        }
    }

    delete[] piNewDims;

    //free pArg content
    cleanIndexesArguments(_pArgs, &pArg);

    return pOut;
}

template <typename T>
GenericType* ArrayOf<T>::extract(typed_list* _pArgs)
{
    ArrayOf<T>* pOut = NULL;

    int index;
    if (getScalarIndex(this, _pArgs, &index))
    {
        if (getSize() == 0)
        {
            return createEmpty();
        }

        if (index >= getSize())
        {
            return NULL;
        }

        static int dims[2] = {1, 1};
        pOut = createEmpty(2, dims, isComplex());;
        pOut->set(0, get(index));
        if (m_pImgData)
        {
            pOut->setImg(0, getImg(index));
        }

        return pOut;
    }

    std::vector<double> il;
    if (getScalarImplicitIndex(this, _pArgs, il))
    {
        double start = il[0];
        double step = il[1];
        double end = il[2];
        //index are ":"
        bool isForceColVector = il.size() == 4;

        //std::cout << start << ":" << step << ":" << end << std::endl;
        int size = static_cast<int>((end - start) / step + 1);

        if (size <= 0 || m_iSize == 0)
        {
            return createEmpty();
        }

        //check bounds
        if (step > 0 && ((size - 1) * step + start > m_iSize || start < 1) ||
                (step < 0 && (start > m_iSize || end < 1)))
        {
            return NULL;
        }

        if (m_iRows == 1 && !isForceColVector)
        {
            // row vector
            int dims[2] = {1, size};
            pOut = createEmpty(2, dims, isComplex());
        }
        else
        {
            int dims[2] = {size, 1};
            pOut = createEmpty(2, dims, isComplex());
        }

        double idx = start;

        if (m_pImgData)
        {
            for (int i = 0; i < size; ++i)
            {
                int index = static_cast<int>(idx) - 1;
                pOut->set(i, get(index));
                pOut->setImg(i, getImg(index));
                idx += step;
            }
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                pOut->set(i, get(static_cast<int>(idx) - 1));
                idx += step;
            }
        }
        return pOut;
    }

    std::vector<int> indexes;
    std::vector<int> dims;
    if (getImplicitIndex(this, _pArgs, indexes, dims))
    {
        if (indexes.size() == 0)
        {
            return createEmpty();
        }

        if (dims.size() == 1)
        {
            int d[2] = {1, dims[0]};
            pOut = createEmpty(2, d, isComplex());
        }
        else
        {
            pOut = createEmpty(static_cast<int>(dims.size()), dims.data(), isComplex());
        }

        if (m_pImgData)
        {
            int size = getSize();
            int idx = 0;
            for (int & i : indexes)
            {
                if (i < 0 || i >= size)
                {
                    pOut->killMe();
                    return NULL;
                }

                pOut->set(idx, get(i));
                pOut->setImg(idx, getImg(i));
                ++idx;
            }
        }
        else
        {
            int idx = 0;
            for (int & i : indexes)
            {
                pOut->set(idx, get(i));
                ++idx;
            }
        }

        return pOut;
    }

    typed_list pArg;
    int iDims = (int)_pArgs->size();
    int* piMaxDim = new int[iDims];
    int* piCountDim = new int[iDims];

    //evaluate each argument and replace by appropriate value and compute the count of combinations
    int iSeqCount = checkIndexesArguments(this, _pArgs, &pArg, piMaxDim, piCountDim);
    if (iSeqCount == 0)
    {
        delete[] piMaxDim;
        delete[] piCountDim;
        //free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        return createEmpty();
    }

    if (iSeqCount < 0)
    {
        delete[] piMaxDim;
        delete[] piCountDim;
        //free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        return NULL;
    }

    //a = {};a(1:2, 1:2) -> {}
    if (getSize() == 0)
    {
        delete[] piMaxDim;
        delete[] piCountDim;
        //free pArg content
        cleanIndexesArguments(_pArgs, &pArg);
        return createEmpty();
    }

    if (iDims < m_iDims)
    {
        for (int i = 0; i < iDims; i++)
        {
            int iDimToCheck = 0;
            if (i == (iDims - 1))
            {
                iDimToCheck = getVarMaxDim(i, iDims);
            }
            else
            {
                iDimToCheck = m_piDims[i];
            }

            if (piMaxDim[i] > iDimToCheck)
            {
                delete[] piMaxDim;
                delete[] piCountDim;
                //free pArg content
                cleanIndexesArguments(_pArgs, &pArg);
                return NULL;
            }
        }
    }
    else
    {
        if (iDims > m_iDims)
        {
            for (int i = m_iDims; i < iDims; i++)
            {
                if (piMaxDim[i] > 1)
                {
                    delete[] piMaxDim;
                    delete[] piCountDim;
                    //free pArg content
                    cleanIndexesArguments(_pArgs, &pArg);
                    return NULL;
                }
            }
        }

        //check MaxDim
        for (int i = 0; i < m_iDims; i++)
        {
            if (piMaxDim[i] > m_piDims[i])
            {
                delete[] piMaxDim;
                delete[] piCountDim;
                //free pArg content
                cleanIndexesArguments(_pArgs, &pArg);
                //exrtact must be in dimension limits
                return NULL;
            }
        }
    }

    // removing trailing dims of size 1
    while (iDims > 2 && piCountDim[iDims - 1] == 1)
    {
        --iDims;
    }

    //vector
    if (iDims == 1)
    {
        if (piCountDim[0] == 0)
        {
            delete[] piMaxDim;
            delete[] piCountDim;
            //free pArg content
            cleanIndexesArguments(_pArgs, &pArg);
            return createEmpty();
        }
        else
        {
            //two cases, depends of original matrix/vector
            if ((*_pArgs)[0]->isColon() == false && m_iDims == 2 && m_piDims[1] != 1 && m_piDims[0] == 1)
            {
                //special case for row vector
                int piRealDim[2] = {1, piCountDim[0]};
                pOut = createEmpty(2, piRealDim, m_pImgData != NULL);
            }
            else
            {
                if (getSize() == 1)
                {
                    //for extraction on scalar
                    pOut = createEmpty(pArg[0]->getAs<GenericType>()->getDims(), pArg[0]->getAs<GenericType>()->getDimsArray(), m_pImgData != NULL);
                }
                else
                {
                    int piRealDim[2] = {piCountDim[0], 1};
                    pOut = createEmpty(2, piRealDim, m_pImgData != NULL);
                }
            }
        }
    }
    else
    {
        //matrix
        pOut = createEmpty(iDims, piCountDim, m_pImgData != NULL);
    }

    int* piIndex = new int[_pArgs->size()]();
    int* piCoord = new int[_pArgs->size()];
    int* piViewDims = new int[iDims];

    for (int i = 0; i < iDims; i++)
    {
        piViewDims[i] = getVarMaxDim(i, iDims);
    }

    for (int i = 0; i < iSeqCount; i++)
    {
        //increment last dimension
        computeTuples(piCountDim, (int)_pArgs->size() - 1, piIndex);

        //std::cout << "[";
        for (int j = 0; j < (int)_pArgs->size(); j++)
        {
            piCoord[j] = static_cast<int>(pArg[j]->getAs<Double>()->get(piIndex[j])) - 1;

            // try to access somewhere wrong.
            if (piCoord[j] < 0)
            {
                delete[] piIndex;
                delete[] piCoord;
                delete[] piViewDims;
                delete[] piMaxDim;
                delete[] piCountDim;

                //free pArg content
                cleanIndexesArguments(_pArgs, &pArg);
                return NULL;
            }
        }

        //std::cout << "]" << std::endl;

        int iPos = 0;
        //put vlaue in the new matrix
        if ((int)_pArgs->size() < m_iDims)
        {
            //compute index based on viewed matrix
            iPos = getIndexWithDims(piCoord, piViewDims, iDims);
        }
        else
        {
            //compute vector index
            iPos = getIndex(piCoord);
        }

        //convert flat dimension to 0
        for (int j = 0; j < iDims; j++)
        {
            if (piCountDim[j] == 1)
            {
                piCoord[j] = 0;
            }
        }

        pOut->set(i, get(iPos));
        if (m_pImgData != NULL)
        {
            pOut->setImg(i, getImg(iPos));
        }


        piIndex[0]++;
    }

    //free pArg content
    cleanIndexesArguments(_pArgs, &pArg);

    delete[] piIndex;
    delete[] piCoord;
    delete[] piViewDims;
    delete[] piMaxDim;
    delete[] piCountDim;

    return pOut;
}

template <typename T>
ArrayOf<T>* ArrayOf<T>::reshape(int* _piDims, int _iDims)
{
    typedef ArrayOf<T>* (ArrayOf<T>::*reshape_t)(int*, int);
    ArrayOf<T>* pIT = checkRef(this, (reshape_t)&ArrayOf<T>::reshape, _piDims, _iDims);
    if (pIT != this)
    {
        return pIT;
    }

    int iNewSize = get_max_size(_piDims, _iDims);
    if (iNewSize != m_iSize)
    {
        return NULL;
    }

    for (int i = 0 ; i < _iDims ; i++)
    {
        m_piDims[i] = _piDims[i];
    }

    if (_iDims == 1)
    {
        // append dim of size 1
        m_piDims[1] = 1;
        _iDims++;
    }
    else
    {
        // removing trailing dims of size 1
        while (_iDims > 2 && m_piDims[_iDims - 1] == 1)
        {
            --_iDims;
        }
    }

    m_iRows = m_piDims[0];
    m_iCols = m_piDims[1];
    m_iSize = iNewSize;
    m_iDims = _iDims;

    return this;
}

template <typename T>
ArrayOf<T>* ArrayOf<T>::resize(int* _piDims, int _iDims)
{
    if (_iDims == m_iDims && memcmp(m_piDims, _piDims, sizeof(int) * m_iDims) == 0)
    {
        //nothing to do
        return this;
    }

    //alloc new data array
    T* pRealData = NULL;
    T* pImgData = NULL;

    int iNewSize = 0;
    if (m_pImgData != NULL)
    {
        iNewSize = get_max_size(_piDims, _iDims);
        if (m_iSizeMax < iNewSize)
        {
            //alloc 10% bigger than asked to prevent future resize
            int iOldSizeMax = m_iSizeMax;
            m_iSizeMax = static_cast<int>(iNewSize * 1.1);
            pRealData = allocData(m_iSizeMax);
            pImgData = allocData(m_iSizeMax);

            //copy values into new one
            int iMaxDims = std::max(m_iDims, _iDims);
            int* piIndexes = new int[iMaxDims]();

            int iPreviousNewIdx = 0;
            for (int i = 0; i < m_iSize; i++)
            {
                getIndexes(i, piIndexes);
                int iNewIdx = getIndexWithDims(piIndexes, _piDims, _iDims);
                pRealData[iNewIdx] = m_pRealData[i];
                pImgData[iNewIdx] = m_pImgData[i];
                for (int j = iPreviousNewIdx; j < iNewIdx; ++j)
                {
                    T pTemp = getNullValue();
                    pRealData[j] = copyValue(pTemp);
                    pImgData[j] = copyValue(pTemp);
                    if (pTemp != pRealData[j])
                    {
                        deleteData(pTemp);
                    }
                }

                iPreviousNewIdx = iNewIdx + 1;
            }

            // if it's not the first resize,
            // fill new data with element of last allocation
            if (iPreviousNewIdx < iOldSizeMax)
            {
                for (int i = iPreviousNewIdx; i < iOldSizeMax; ++i)
                {
                    pRealData[i] = m_pRealData[i];
                    pImgData[i] = m_pImgData[i];
                }
            }
            else
            {
                // first resize, iOldSizeMax don't contain the 10%
                iOldSizeMax = iPreviousNewIdx;
            }

            for (int i = iOldSizeMax; i < m_iSizeMax; ++i)
            {
                T pTemp = getNullValue();
                pRealData[i] = copyValue(pTemp);
                pImgData[i] = copyValue(pTemp);
                if (pTemp != pRealData[i])
                {
                    deleteData(pTemp);
                }
            }

            delete[] piIndexes;
            //delete all array
            delete[] m_pRealData;
            delete[] m_pImgData;
            //replace old array by new one
            m_pRealData = pRealData;
            m_pImgData = pImgData;
        }
        else
        {
            //check if only the last dims change
            bool bNonLastDimChange = false;
            for (int i = 0; i < (m_iDims - 1); i++)
            {
                if (m_piDims[i] != _piDims[i])
                {
                    bNonLastDimChange = true;
                    break;
                }
            }

            //if vector or if row dimension not change, we don't need to shift data
            if (m_iDims != _iDims || (!isVector() && bNonLastDimChange))
            {
                //copy values into new one
                int iMaxDims = std::max(m_iDims, _iDims);
                int* piIndexes = new int[iMaxDims]();

                for (int i = m_iSize - 1; i >= 0; i--)
                {
                    getIndexes(i, piIndexes);
                    int iNewIdx = getIndexWithDims(piIndexes, _piDims, _iDims);
                    if (iNewIdx != i)
                    {
                        T pTemp = m_pRealData[iNewIdx];
                        m_pRealData[iNewIdx] = m_pRealData[i];
                        m_pRealData[i] = pTemp;

                        pTemp = m_pImgData[iNewIdx];
                        m_pImgData[iNewIdx] = m_pImgData[i];
                        m_pImgData[i] = pTemp;
                    }
                }
                delete[] piIndexes;
            }
        }
    }
    else
    {
        iNewSize = get_max_size(_piDims, _iDims);
        if (iNewSize > m_iSizeMax)
        {
            //alloc 10% bigger than asked to prevent future resize
            int iOldSizeMax = m_iSizeMax;
            m_iSizeMax = static_cast<int>(iNewSize * 1.1);
            pRealData = allocData(m_iSizeMax);

            //copy values into new one
            int iMaxDims = std::max(m_iDims, _iDims);
            int* piIndexes = new int[iMaxDims]();

            int iPreviousNewIdx = 0;
            for (int i = 0; i < m_iSize; i++)
            {
                getIndexes(i, piIndexes);
                int iNewIdx = getIndexWithDims(piIndexes, _piDims, _iDims);
                pRealData[iNewIdx] = m_pRealData[i];

                for (int j = iPreviousNewIdx; j < iNewIdx; ++j)
                {
                    T pTemp = getNullValue();
                    T pTemp2 = copyValue(pTemp);
                    pRealData[j] = pTemp2;
                    if (pTemp != pTemp2)
                    {
                        deleteData(pTemp);
                    }
                }

                iPreviousNewIdx = iNewIdx + 1;
            }

            //fill exceeded with NullValue
            for (int i = iPreviousNewIdx; i < m_iSizeMax; ++i)
            {
                T pTemp = getNullValue();
                T pTemp2 = copyValue(pTemp);
                pRealData[i] = pTemp2;
                if (pTemp != pTemp2)
                {
                    deleteData(pTemp);
                }
            }

            //clean section between m_iSize and iOldSizeMax
            for (int i = m_iSize; i < iOldSizeMax; ++i)
            {
                deleteData(m_pRealData[i]);
            }

            delete[] piIndexes;
            //delete all array
            delete[] m_pRealData;
            //replace old array by new one
            m_pRealData = pRealData;
        }
        else
        {
            //check if only the last dims change
            bool bNonLastDimChange = false;
            for (int i = 0; i < (m_iDims - 1); i++)
            {
                if (m_piDims[i] != _piDims[i])
                {
                    bNonLastDimChange = true;
                    break;
                }
            }

            //if vector or if row dimension not change, we don't need to shift data
            if (m_iDims != _iDims || (!isVector() && bNonLastDimChange))
            {
                //copy values into new one
                int iMaxDims = std::max(m_iDims, _iDims);
                int* piIndexes = new int[iMaxDims]();

                for (int i = m_iSize - 1; i >= 0; i--)
                {
                    getIndexes(i, piIndexes);
                    int iNewIdx = getIndexWithDims(piIndexes, _piDims, _iDims);
                    if (iNewIdx != i)
                    {
                        T pTemp = m_pRealData[iNewIdx];
                        m_pRealData[iNewIdx] = m_pRealData[i];
                        m_pRealData[i] = pTemp;
                    }
                }
                delete[] piIndexes;
            }
        }
    }

    for (int i = 0; i < _iDims; i++)
    {
        m_piDims[i] = _piDims[i];
    }

    m_iDims = _iDims;
    m_iRows = m_piDims[0];
    m_iCols = m_piDims[1];
    m_iSize = iNewSize;
    return this;
}

template <typename T>
bool ArrayOf<T>::isTrue()
{
    return type_traits::isTrue<T>(m_iSize, m_pRealData);
}

template<typename T>
bool ArrayOf<T>::neg(InternalType *& out)
{
    out = new Bool(this->m_iDims, this->m_piDims);
    type_traits::neg<T, int>(this->m_iSize, this->m_pRealData, static_cast<Bool *>(out)->get());

    return true;
}

template<typename T>
bool ArrayOf<T>::invoke(typed_list & in, optional_list & /*opt*/, int /*_iRetCount*/, typed_list & out, const ast::Exp & e)
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

template<typename T>
bool ArrayOf<T>::isInvokable() const
{
    return true;
}

template<typename T>
bool ArrayOf<T>::hasInvokeOption() const
{
    return false;
}

template<typename T>
int ArrayOf<T>::getInvokeNbIn()
{
    return -1;
}

template<typename T>
int ArrayOf<T>::getInvokeNbOut()
{
    return 1;
}

template<typename T>
void ArrayOf<T>::clearPrintState()
{
    m_bPrintFromStart = true;
    m_iSavePrintState = 0;
    m_iRows1PrintState = 0;
    m_iCols1PrintState = 0;
    m_iRows2PrintState = 0;
    m_iCols2PrintState = 0;
}

// used to allow definition of ArrayOf methode in this cpp file.
template class ArrayOf < char >;
template class ArrayOf < unsigned char >;
template class ArrayOf < short >;
template class ArrayOf < unsigned short >;
template class ArrayOf < int >;
template class ArrayOf < unsigned int >;
template class ArrayOf < long long >;
template class ArrayOf < unsigned long long >;
template class ArrayOf < double >;
template class ArrayOf < wchar_t* >;
template class ArrayOf < SinglePoly* >;
template class ArrayOf < SingleStruct* >;
template class ArrayOf < InternalType* >; // Cell
}
