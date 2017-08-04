/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

// This code is separated in double.hxx
// but will be inlined in arrayof.hxx
//
// If you need additionnal headers, please add it in arrayof.hxx

//#ifndef __ARRAYOF_HXX__
//    #error This file must only be include by arrayof.hxx
//#endif

#ifndef __DOUBLE_HXX__
#define __DOUBLE_HXX__

#include "arrayof.hxx"
#include "bool.hxx"
#include "types_transposition.hxx"

namespace types
{
class EXTERN_AST Double : public ArrayOf<double>
{
public :
    virtual						~Double();

    Double(double _dblReal);
    Double(double _dblReal, double _dblImg);
    Double(int _iRows, int _iCols, bool _bComplex = false, bool _bZComplex = false);
    Double(int _iRows, int _iCols, double **_pdblReal);
    Double(int _iRows, int _iCols, double **_pdblReal, double **_pdblImg);
    Double(int _iDims, const int* _piDims, bool _bComplex = false, bool _bZComplex = false);

    static Double*              Empty();
    static Double*              Identity(int _iRows, int _iCols);
    static Double*              Identity(int _iDims, const int* _piDims);
    static Double*              Identity(int _iDims, const int* _piDims, double _dblReal);
    static Double*              Identity(int _iDims, const int* _piDims, double _dblReal, double _dblImg);


    /*data management*/
    double*                     getReal() const;
    double                      getReal(int _iRows, int _iCols);
    bool                        setInt(int* _piReal); //to translate int to double matrix

    /*zero or one set filler*/
    bool                        setZeros();
    bool                        setOnes();

    /*Config management*/
    void                        whoAmI();
    bool                        isEmpty();

    Double*                     clone();
    bool                        fillFromCol(int _iCols, Double *_poSource);
    bool                        fillFromRow(int _iRows, Double *_poSource);
    Double*                     append(int _iRows, int _iCols, InternalType* _poSource);

    //bool                        append(int _iRows, int _iCols, Double *_poSource);

    bool                        operator==(const InternalType& it);
    bool                        operator!=(const InternalType& it);

    bool                        isDouble()
    {
        return true;
    }

    bool isComplex()
    {
        return (m_pImgData != NULL) || m_bViewAsZComplex;
    }

    inline bool isNumericallyComplex(double tolerance = 0)
    {
        if (isComplex())
        {
            for (int i = 0; i < m_iSize; i++)
            {
                if (std::abs(m_pImgData[i]) > tolerance)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isTrue();

    bool neg(InternalType *& out)
    {
        if (isEmpty())
        {
            out = this;
            return true;
        }

        return ArrayOf<double>::neg(out);
    }

    void                        setViewAsInteger(bool _bViewAsInteger = true)
    {
        m_bViewAsInteger = _bViewAsInteger;
    }
    bool                        isViewAsInteger()
    {
        return m_bViewAsInteger;
    }

    void                        convertToInteger();
    void                        convertFromInteger();

    void                        setViewAsZComplex(bool _bViewAsZComplex = true)
    {
        m_bViewAsZComplex = _bViewAsZComplex;
    }
    bool                        isViewAsZComplex()
    {
        return m_bViewAsZComplex;
    }

    void                        convertToZComplex();
    void                        convertFromZComplex();

    /* return type as string ( double, int, cell, list, ... )*/
    virtual std::wstring        getTypeStr() const
    {
        return L"constant";
    }
    /* return type as short string ( s, i, ce, l, ... )*/
    virtual std::wstring        getShortTypeStr() const
    {
        return L"s";
    }

    inline ScilabType           getType(void)
    {
        return ScilabDouble;
    }
    inline ScilabId             getId(void)
    {
        return isIdentity() ? isComplex() ? IdIdentityComplex : IdIdentity
               : isEmpty() ? IdEmpty
               : isComplex() ? isScalar() ? IdScalarDoubleComplex
               : IdDoubleComplex
               : isScalar() ? IdScalarDouble
               : IdDouble;
    }

    inline bool conjugate(InternalType *& out)
    {
        if (isEmpty() || isIdentity() || !isComplex())
        {
            out = clone();
            return true;
        }

        if (isScalar())
        {
            out = new Double(m_pRealData[0], -m_pImgData[0]);
            return true;
        }

        if (m_iDims == 2)
        {
            Double * pReturn = new Double(m_iCols, m_iRows, true);
            out = pReturn;

            Transposition::conjugate(m_iSize, m_pRealData, pReturn->m_pRealData, m_pImgData, pReturn->m_pImgData);
            return true;
        }

        return false;

    }

    virtual bool adjoint(InternalType *& out)
    {
        if (isEmpty())
        {
            out = this;
            return true;
        }

        if (isIdentity())
        {
            out = clone();
            return true;
        }

        if (isScalar())
        {
            if (isComplex())
            {
                out = new Double(m_pRealData[0], -m_pImgData[0]);
            }
            else
            {
                out = clone();
            }

            return true;
        }

        if (m_iDims == 2)
        {
            Double * pReturn = new Double(m_iCols, m_iRows, isComplex());
            out = pReturn;
            if (isComplex())
            {
                Transposition::adjoint(m_iRows, m_iCols, m_pRealData, pReturn->m_pRealData, m_pImgData, pReturn->m_pImgData);
            }
            else
            {
                Transposition::adjoint(m_iRows, m_iCols, m_pRealData, pReturn->m_pRealData);
            }

            return true;
        }

        return false;
    }

    virtual bool transpose(InternalType *& out)
    {
        if (isEmpty())
        {
            out = this;
            return true;
        }

        if (isIdentity() || isScalar())
        {
            out = clone();
            return true;
        }

        if (m_iDims == 2)
        {
            Double * pReturn = new Double(m_iCols, m_iRows, isComplex());
            out = pReturn;
            if (isComplex())
            {
                Transposition::transpose(m_iRows, m_iCols, m_pRealData, pReturn->m_pRealData, m_pImgData, pReturn->m_pImgData);
            }
            else
            {
                Transposition::transpose(m_iRows, m_iCols, m_pRealData, pReturn->m_pRealData);
            }

            return true;
        }

        return false;
    }

    virtual ast::Exp*           getExp(const Location& loc);

    virtual Double* set(int _iPos, const double _data)
    {
        if (_iPos >= m_iSize)
        {
            return NULL;
        }

        typedef Double* (Double::*set_t)(int, double);
        Double* pIT = checkRef(this, (set_t)&Double::set, _iPos, _data);
        if (pIT != this)
        {
            return pIT;
        }

        m_pRealData[_iPos] = _data;
        return this;
    }

    virtual Double* set(int _iRows, int _iCols, const double _data)
    {
        return set(_iCols * m_iRows + _iRows, _data);
    }

    virtual Double* set(double* _pdata)
    {
        if (m_pRealData == NULL)
        {
            return NULL;
        }

        typedef Double* (Double::*set_t)(double*);
        Double* pIT = checkRef(this, (set_t)&Double::set, _pdata);
        if (pIT != this)
        {
            return pIT;
        }

        memmove(m_pRealData, _pdata, sizeof(double) * m_iSize);
        
        return this;
    }

    virtual Double* set(const double* _pdata)
    {
        if (m_pRealData == NULL)
        {
            return NULL;
        }

        typedef Double* (Double::*set_t)(const double*);
        Double* pIT = checkRef(this, (set_t)&Double::set, _pdata);
        if (pIT != this)
        {
            return pIT;
        }
        
        memmove(m_pRealData, _pdata, sizeof(double) * m_iSize);
        
        return this;
    }

    virtual bool isNativeType() override
    {
        return true;
    }

    virtual void fillDefaultValues() override
    {
        size_t mem_size = sizeof(double) * m_iSize;
        memset(m_pRealData, 0x00, mem_size);
        if (isComplex())
        {
            memset(m_pImgData, 0x00, mem_size);
        }
    }

private:
    virtual bool                subMatrixToString(std::wostringstream& ostr, int* _piDims, int _iDims) override;

    virtual double              getNullValue();
    virtual Double*             createEmpty(int _iDims, int* _piDims, bool _bComplex = false);
    virtual double              copyValue(double _dblData);
    virtual void                deleteAll();
    virtual void                deleteImg();
    virtual double*             allocData(int _iSize);
    virtual void                deleteData(double /*data*/) { }

    bool                        m_bViewAsInteger;
    bool                        m_bViewAsZComplex;

};

inline bool Double::isEmpty()
{
    if (m_iDims == 2 && m_iRows == 0 && m_iCols == 0)
    {
        return true;
    }
    return false;
}

inline double* Double::getReal() const
{
    return get();
}

inline double Double::getReal(int _iRows, int _iCols)
{
    return get(_iRows, _iCols);
}

inline double Double::getNullValue()
{
    return 0;
}

inline double Double::copyValue(double _dblData)
{
    return _dblData;
}

}

#ifdef _MSC_VER
template class types::ArrayOf<double>; //Double
#endif
#endif /* !__DOUBLE_HXX__ */
