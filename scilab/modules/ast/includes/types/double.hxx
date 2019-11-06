/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
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
class Double : public ArrayOf<double>
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
    static Double* Identity(bool _bComplex = false);
    static Double* Identity(double _pdblReal);
    static Double* Identity(double _pdblReal, double _pdblImg);
    static Double*              Identity(int _iRows, int _iCols);
    static Double*              Identity(int _iDims, const int* _piDims);
    static Double*              Identity(int _iDims, const int* _piDims, double _dblReal);
    static Double*              Identity(int _iDims, const int* _piDims, double _dblReal, double _dblImg);


    /*data management*/
    double*                     getReal() const;
    double                      getReal(int _iRows, int _iCols);
    void setInt(int* _piReal); //to translate int to double matrix

    // fill array with zeros or ones
    void setZeros();
    void setOnes();

    /*Config management*/
    bool                        isEmpty();

    Double*                     clone() override;
    void append(int _iRows, int _iCols, InternalType* _poSource) override;

    //bool                        append(int _iRows, int _iCols, Double *_poSource);

    bool                        operator==(const InternalType& it) override;
    bool                        operator!=(const InternalType& it) override;

    bool                        isDouble() override
    {
        return true;
    }

    bool isComplex() override
    {
        return (m_pImgData != NULL) || isViewAsZComplex();
    }

    bool isTrue() override;

    bool neg(InternalType *& out) override
    {
        if (isEmpty())
        {
            out = this;
            return true;
        }

        out = new Bool(this->m_iDims, this->m_piDims);
        int* pb = static_cast<Bool*>(out)->get();

        if (m_pImgData ==  NULL)
        {
            if (isViewAsZComplex())
            {
                for (int i = 0; i < m_iSize; ++i)
                {
                    pb[i] = !(m_pRealData[i] || m_pRealData[2*i+1]);
                }
            }
            else
            {
                for (int i = 0; i < m_iSize; ++i)
                {
                    pb[i] = !(m_pRealData[i]);
                }
            }
        }
        else
        {
            for (int i = 0; i < m_iSize; ++i)
            {
                pb[i] = !(m_pRealData[i] || m_pImgData[i]);
            }
        }

        return true;
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
    virtual std::wstring        getTypeStr() const override
    {
        return L"constant";
    }
    /* return type as short string ( s, i, ce, l, ... )*/
    virtual std::wstring        getShortTypeStr() const override
    {
        return L"s";
    }

    inline ScilabType           getType(void) override
    {
        return ScilabDouble;
    }

    inline ScilabId             getId(void) override
    {
        if (getRows() == getCols())
        {
            if (m_iDims == 2)
            {
                switch (getRows())
                {
                    case -1:
                        return isComplex() ? IdIdentityComplex : IdIdentity;
                    case 0:
                        return IdEmpty;
                    case 1:
                        return isComplex() ? IdScalarDoubleComplex : IdScalarDouble;
                    default:
                        return isComplex() ? IdDoubleComplex : IdDouble;
                }
            }
            else
            {
                if (isIdentity())
                {
                    return isComplex() ? IdIdentityComplex : IdIdentity;
                }
                else
                {
                    return isComplex() ? IdDoubleComplex : IdDouble;
                }
            }
        }
        else
        {
            return isComplex() ? IdDoubleComplex : IdDouble;
        }
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
            Double * pReturn = new Double(getCols(), getRows(), true);
            out = pReturn;

            Transposition::conjugate(m_iSize, m_pRealData, pReturn->m_pRealData, m_pImgData, pReturn->m_pImgData);
            return true;
        }

        return false;

    }

    virtual bool adjoint(InternalType *& out) override
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
            Double * pReturn = new Double(getCols(), getRows(), isComplex());
            out = pReturn;
            if (isComplex())
            {
                Transposition::adjoint(getRows(), getCols(), m_pRealData, pReturn->m_pRealData, m_pImgData, pReturn->m_pImgData);
            }
            else
            {
                Transposition::adjoint(getRows(), getCols(), m_pRealData, pReturn->m_pRealData);
            }

            return true;
        }

        return false;
    }

    virtual bool transpose(InternalType *& out) override
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
            Double * pReturn = new Double(getCols(), getRows(), isComplex());
            out = pReturn;
            if (isComplex())
            {
                Transposition::transpose(getRows(), getCols(), m_pRealData, pReturn->m_pRealData, m_pImgData, pReturn->m_pImgData);
            }
            else
            {
                Transposition::transpose(getRows(), getCols(), m_pRealData, pReturn->m_pRealData);
            }

            return true;
        }

        return false;
    }

    virtual ast::Exp*           getExp(const Location& loc) override;

    virtual void set(int _iPos, const double _data) override
    {
        m_pRealData[_iPos] = _data;
    }

    virtual void set(int _iRows, int _iCols, const double _data) override
    {
        m_pRealData[_iCols * getRows() + _iRows] = _data;
    }

    virtual void set(double* _pdata)
    {
        for (int i = 0; i < m_iSize; i++)
        {
            m_pRealData[i] = _pdata[i];
        }
    }

    virtual void set(const double* _pdata) override
    {
        for (int i = 0; i < m_iSize; i++)
        {
            m_pRealData[i] = _pdata[i];
        }
    }

    virtual bool isNativeType() override
    {
        return true;
    }

    virtual void fillDefaultValues() override
    {
        int iMemSize = m_iSize * sizeof(double);

        memset(m_pRealData, 0x00, iMemSize);

        if (m_pImgData)
        {
            memset(m_pImgData, 0x00, iMemSize);
        }
    }

private:
    virtual bool                subMatrixToString(std::wostringstream& ostr, int* _piDims, int _iDims) override;
    virtual std::wstring toStringInLine();
    virtual double              getNullValue() override;
    virtual Double*             createEmpty(int _iDims, int* _piDims, bool _bComplex = false) override;
    virtual double              copyValue(double _dblData) override;
    virtual void                deleteAll() override;
    virtual void                deleteImg() override;
    virtual double*             allocData(int _iSize) override;
    virtual void                deleteData(double /*data*/) override { }

    bool                        m_bViewAsInteger;
    bool                        m_bViewAsZComplex;

};
}

#ifdef _MSC_VER
template class types::ArrayOf<double>; //Double
#endif
#endif /* !__DOUBLE_HXX__ */
