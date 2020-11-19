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

#ifndef __ARRAYOF_HXX__
#define __ARRAYOF_HXX__

#ifdef _MSC_VER
#define NOMINMAX
#endif

#include <sstream>
#include <cstdio>
#include "types.hxx"
#include "scilabexception.hxx"
#include "inspector.hxx"

extern "C"
{
#include "core_math.h"
#include "localization.h"
#include "os_string.h"
}

namespace types
{

template <typename T>
class ArrayOf : public GenericType
{
public:
    typedef T type;

protected :
    T*                      m_pRealData;
    T*                      m_pImgData;

    // variables to manage print taking care of lines
    bool m_bPrintFromStart;
    int  m_iSavePrintState;
    int  m_iRows1PrintState;
    int  m_iCols1PrintState;
    int  m_iRows2PrintState;
    int  m_iCols2PrintState;

    ArrayOf() : GenericType(), m_pRealData(NULL),
                               m_pImgData(NULL),
                               m_bPrintFromStart(true),
                               m_iSavePrintState(0),
                               m_iRows1PrintState(0),
                               m_iCols1PrintState(0),
                               m_iRows2PrintState(0),
                               m_iCols2PrintState(0) {}

    virtual                 ~ArrayOf()
    {
        //delete[] m_piDims;
    }


    /*internal constructor*/
    void create(const int* _piDims, int _iDims, T** _pRealData, T** _pImgData)
    {
        m_iSize     = 1;
        m_iDims     = _iDims;

        // reduce dims if it's possible,
        // i.e. removing trailing dims of size 1
        while (m_iDims > 2 && _piDims[m_iDims - 1] == 1)
        {
            --m_iDims;
        }

        //m_piDims    = new int[m_iDims];

        //eye detection ^^
        if (m_iDims == 2 && _piDims[0] == -1 && _piDims[1] == -1)
        {
            m_iRows = -1;
            m_iCols = -1;
        }
        else
        {
            for (int i = 0 ; i < m_iDims ; i++)
            {
                // if one of dim is null, create an empty matrix
                if (_piDims[i] <= 0)
                {
                    m_iDims = 2;
                    m_iRows = 0;
                    m_iCols = 0;
                    m_iSize = 0;
                    break;
                }

                m_piDims[i] = _piDims[i];

                // At this point all elements of m_piDims are positive
                // ( > 0), thus in the following iterative calculation
                // we have always m_iSize > 0.

                int iTmpSize = m_iSize * m_piDims[i];

                // overflow of iTmpSize ?
                if (iTmpSize / m_iSize != m_piDims[i])
                {
                    throw ast::InternalError(34);
                }

                m_iSize = iTmpSize;
            }
        }

        try
        {

            if (_pRealData)
            {
                m_pRealData = allocData(m_iSize);
                *_pRealData = m_pRealData;
            }
            else
            {
                m_pRealData = NULL;
            }

            if (_pImgData)
            {
                m_pImgData = allocData(m_iSize);
                *_pImgData = m_pImgData;
            }
            else
            {
                m_pImgData = NULL;
            }
        }
        catch (std::bad_alloc & /*e*/)
        {
            throw ast::InternalError(1);
        }

        m_iSizeMax = m_iSize;
    }

    virtual T               getNullValue() = 0;
    virtual ArrayOf<T>*     createEmpty(int _iDims, int* _piDims, bool _bComplex = false) = 0;
    virtual GenericType*    createEmpty();

    virtual T               copyValue(T _data) = 0;
    virtual T*              allocData(int _iSize) = 0;
    virtual void            deleteAll() = 0;
    virtual void            deleteImg() = 0;
public :

    bool isArrayOf() override
    {
        return true;
    }

    bool isTrue() override;

    // The function is not write here because we needs to create a Bool which inherits from ArrayOf<int>
    // so it will create a cyclic dependency... so the body of the function is in bool.hxx after the Bool definition.
    virtual bool neg(InternalType *& out) override;

    virtual bool isComplex() override
    {
        return m_pImgData != NULL;
    }

    //type does not need to delete or clone ( int, double, ... )
    virtual bool isNativeType()
    {
        return false;
    }

    virtual void fillDefaultValues()
    {
        int size = getSize();
        T tNullVal = getNullValue();
        if (isComplex())
        {
            for (int i = 0; i < size; ++i)
            {
                set(i, tNullVal);
                setImg(i, tNullVal);
            }
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                set(i, tNullVal);
            }
        }

        deleteData(tNullVal);
    }

    virtual void setComplex(bool _bComplex)
    {
        if (_bComplex == false)
        {
            if (m_pImgData != NULL)
            {
                deleteImg();
            }
        }
        else // _bComplex == true
        {
            if (m_pImgData == NULL)
            {
                m_pImgData = allocData(m_iSize);
                memset(m_pImgData, 0x00, sizeof(T) * m_iSize);
            }
        }
    }

    virtual bool has(int _iPos)
    {
        return (_iPos < m_iSize);
    }

    virtual void set(int _iPos, const T _data)
    {
        deleteData(m_pRealData[_iPos]);
        m_pRealData[_iPos] = copyValue(_data);
    }

    virtual void set(int _iRows, int _iCols, const T _data)
    {
        set(_iCols * getRows() + _iRows, _data);
    }

    virtual void set(const T* _pdata)
    {
        for (int i = 0 ; i < m_iSize ; i++)
        {
            deleteData(m_pRealData[i]);
            m_pRealData[i] = copyValue(_pdata[i]);
        }
    }

    inline T* get() const
    {
        return m_pRealData;
    }

    inline T get(int _iPos)
    {
        return m_pRealData[_iPos];
    }

    inline T get(int _iRows, int _iCols)
    {
        return get(_iCols * getRows() + _iRows);
    }

    // specialized "get" for scalars (first element)
    // wo/ any safety checks!!!
    inline T getFirst()
    {
        return m_pRealData[0];
    }

    inline T getImgFirst()
    {
        return m_pImgData[0];
    }

    /*internal function to manage img part*/
    void setImg(int _iPos, T _data)
    {
        m_pImgData[_iPos] = copyValue(_data);
    }

    void setImg(int _iRows, int _iCols, T _data)
    {
        setImg(_iCols * getRows() + _iRows, copyValue(_data));
    }

    void setImg(T* _pdata)
    {
        for (int i = 0 ; i < m_iSize ; i++)
        {
            m_pImgData[i] = copyValue(_pdata[i]);
        }
    }

    void setImg(const T* _pdata)
    {
        for (int i = 0 ; i < m_iSize ; i++)
        {
            m_pImgData[i] = copyValue(_pdata[i]);
        }
    }

    inline T* getImg() const
    {
        return m_pImgData;
    }

    inline T getImg(int _iPos)
    {
        return m_pImgData[_iPos];
    }

    inline T getImg(int _iRows, int _iCols)
    {
        return getImg(_iCols * getRows() + _iRows);
    }

    virtual ArrayOf<T>* insert(typed_list* _pArgs, InternalType* _pSource) override;
    virtual void append(int _iRows, int _iCols, InternalType* _poSource);
    virtual ArrayOf<T>* resize(int* _piDims, int _iDims) override;

    // return a GenericType because of [] wich is a types::Double (can't be a ArrayOf<char>)
    virtual GenericType* remove(typed_list* _pArgs) override;
    virtual GenericType* extract(typed_list* _pArgs) override;
    virtual GenericType* insertNew(typed_list* _pArgs) override;

    virtual bool invoke(typed_list & in, optional_list & /*opt*/, int /*_iRetCount*/, typed_list & out, const ast::Exp & e) override;
    virtual bool isInvokable() const override;
    virtual bool hasInvokeOption() const override;
    virtual int getInvokeNbIn() override;
    virtual int getInvokeNbOut() override;

    virtual ArrayOf<T>* reshape(int _iNewRows, int _iNewCols) override
    {
        int piDims[2] = {_iNewRows, _iNewCols};
        return reshape(piDims, 2);
    }

    virtual ArrayOf<T>* reshape(int* _piDims, int _iDims) override;


    virtual ArrayOf<T>* resize(int _iNewRows, int _iNewCols) override
    {
        int piDims[2] = {_iNewRows, _iNewCols};
        return resize(piDims, 2);
    }

    virtual void deleteData(T /*data*/)
    {
    }

    /*dimensions functions*/
    int getIndex(const int* _piIndexes)
    {
        if (m_iDims == 2)
        {
            return _piIndexes[0] + _piIndexes[1] * getRows();
        }
        else
        {
            int idx = 0;
            int iMult = 1;
            for (int i = 0 ; i < m_iDims ; i++)
            {
                idx += _piIndexes[i] * iMult;
                iMult *= m_piDims[i];
            }
            return idx;
        }
    }

    void getIndexes(int _iIndex, int* _piIndexes);

    virtual bool getMemory(int* _piSize, int* _piSizePlusType) override;

    ArrayOf<T>* getColumnValues(int _iPos) override
    {
        int iRows = getRows();
        int piDims[2] = {iRows, 1};
        bool bComplex = m_pImgData != NULL;
        ArrayOf<T>* pOut = createEmpty(2, piDims, bComplex);
        T* pReal    = pOut->get();
        T* pImg     = pOut->getImg();
        int iOffset = iRows * _iPos;

        for (int i = 0 ; i < iRows ; i++)
        {
            pReal[i] = copyValue(get(iOffset + i));
        }

        if (bComplex)
        {
            for (int i = 0 ; i < iRows ; i++)
            {
                pImg[i] = copyValue(getImg(iOffset + i));
            }
        }

        return pOut;
    }

    virtual bool toString(std::wostringstream& ostr) override
    {
        int* piDims = new int[m_iDims];
        bool bFinish = parseSubMatrix(ostr, piDims, m_iDims, m_iDims - 1);
        delete[] piDims;
        return bFinish;
    }

    bool parseSubMatrix(std::wostringstream& ostr, int* _piDims, int _iDims, int _iDim)
    {
        bool bFinish = false;
        if (_iDim == 1)
        {
            //we have reach 2-dim matrix

            if (m_iDims > 2 && m_bPrintFromStart)
            {
                //only print for dims > 2
                ostr << L"(:,:";
                for (int i = 2 ; i < _iDims ; i++)
                {
                    ostr << L"," << (_piDims[i] + 1);
                }
                ostr << L")" << L"\n\n";
            }

            //reset flag to print dims on next call
            m_bPrintFromStart = true;

            bFinish = subMatrixToString(ostr, _piDims, _iDims);
            if (bFinish == false)
            {
                //save print status
                m_bPrintFromStart = false;
                return false;
            }
        }
        else
        {
            //draw, continue to dig
            for (int i = m_iSavePrintState ; i < m_piDims[_iDim] ; i++)
            {
                _piDims[_iDim] = i;
                bFinish = parseSubMatrix(ostr, _piDims, _iDims, _iDim - 1);
                if (bFinish == false)
                {
                    //save print status
                    m_iSavePrintState = i;
                    return false;
                }
            }

            //reset state to print from state
            m_iSavePrintState = 0;
            m_iRows1PrintState = 0;
            m_iCols1PrintState = 0;
            m_iRows2PrintState = 0;
            m_iCols2PrintState = 0;
        }

        return true;
    }

    virtual bool subMatrixToString(std::wostringstream& ostr, int* _piDims, int _iDims) = 0;

    virtual std::wstring toStringInLine() override
    {
        std::wostringstream ostr;
        ostr << L"[" << DimsToString<std::wstring>() << L" " << getTypeStr() << L"]";
        return ostr.str();
    }

    virtual void clearPrintState();
};

}

#endif /* !__ARRAYOF_HXX__ */
