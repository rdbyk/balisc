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

// This code is separated in matrixpoly.hxx
// but will be inlined in arrayof.hxx
//
// If you need additionnal headers, please add it in arrayof.hxx

//#ifndef __ARRAYOF_HXX__
//    #error This file must only be include by arrayof.hxx
//#endif

#ifndef __POLYNOM_HXX__
#define __POLYNOM_HXX__

#include "arrayof.hxx"
#include "singlepoly.hxx"
#include "double.hxx"

//disable warnings about exports STL items
#ifdef _MSC_VER
#pragma warning (disable : 4251)
#endif

namespace types
{
class Polynom : public ArrayOf<SinglePoly*>
{
public :
    Polynom();
    Polynom(const std::wstring& _szVarName, int _iRows, int _iCols);
    Polynom(const std::wstring& _szVarName, int _iRows, int _iCols, const int *_piRank);
    Polynom(const std::wstring& _szVarName, int _iDims, const int* _piDims);
    Polynom(const std::wstring& _szVarName, int _iDims, const int* _piDims, const int *_piRank);

    virtual                 ~Polynom();

    // FIXME : Should not return NULL
    Polynom*                clone() override;

    void setCoef(int _iRows, int _iCols, Double *_pdblCoef);
    void setCoef(int _iIdx, Double *_pdblCoef);

    virtual void setComplex(bool _bComplex) override;

    inline ScilabType       getType(void) override
    {
        return ScilabPolynom;
    }

    inline ScilabId         getId(void) override
    {
        return isScalar() ? isComplex() ? IdScalarPolynomComplex
               : IdScalarPolynom
               : isComplex() ? IdPolynomComplex
               : IdPolynom;
    }

    bool isComplex(void) override;

    inline bool             isPoly() override
    {
        return true;
    }

    std::wstring&           getVariableName();
    void                    setVariableName(const std::wstring&);
    bool                    getSizes(int *_piSizes);
    bool                    getRank(int *_piRank);
    int                     getMaxRank(void);
    Double*                 evaluate(Double* _pdblValue);
    void                    updateRank(void);
    Double*                 getCoef(void);
    void setCoef(Double *_pCoef);
    Double*                 extractCoef(int _iRank);
    bool                    insertCoef(int _iRank, Double* _pCoef);
    void                    setZeros();
    Polynom*                insert(typed_list* _pArgs, InternalType* _pSource) override;

    void set(int _iPos, SinglePoly* _pS) override;
    void set(int _iRows, int _iCols, SinglePoly* _pS) override;
    void set(SinglePoly** _pS);

    std::wstring            getRowString(int* _piDims, int _iDims, bool _bComplex);
    std::wstring            getColString(int* _piDims, int _iDims, bool _bComplex);
    std::wstring            getMatrixString(int* _piDims, int _iDims, bool _bComplex);

    bool                    operator==(const InternalType& it) override;
    bool                    operator!=(const InternalType& it) override;

    /* return type as string ( double, int, cell, list, ... )*/
    virtual std::wstring    getTypeStr() const override
    {
        return L"polynomial";
    }
    /* return type as short string ( s, i, ce, l, ... )*/
    virtual std::wstring    getShortTypeStr() const override
    {
        return L"p";
    }

    bool isTrue() override
    {
        for (int i = 0; i < m_iSize; ++i)
        {
            if (!get(i)->isTrue())
            {
                return false;
            }
        }

        return true;
    }

    virtual bool neg(InternalType*& out)
    {
        out = new Bool(this->m_iDims, this->m_piDims);
        int* pb = static_cast<Bool*>(out)->get();

        for (int i = 0; i < m_iSize; ++i)
        {
            pb[i] = !get(i)->isTrue();
        }

        return true;
    }

    bool getMemory(int* _piSize, int* _piSizePlusType) override;

    bool transpose(InternalType *& out) override;
    bool adjoint(InternalType *& out) override;

    static Polynom* Dollar();

protected :
    std::wstring            m_szVarName;
    void                    createPoly(const std::wstring& _szVarName, int _iDims, const int* _piDims, const int *_piRank);

private :
    virtual bool            subMatrixToString(std::wostringstream& ostr, int* _piDims, int _iDims) override;

    virtual SinglePoly*     getNullValue() override;
    virtual Polynom*        createEmpty(int _iDims, int* _piDims, bool _bComplex = false) override;
    virtual SinglePoly*     copyValue(SinglePoly* _pData) override;
    virtual void            deleteAll() override;
    virtual void            deleteImg() override;
    virtual SinglePoly**    allocData(int _iSize) override;
    virtual void            deleteData(SinglePoly* data) override;
};
}

#ifdef _MSC_VER
template class types::ArrayOf<types::SinglePoly*>; //Polynom
#endif
#endif /* !__POLYNOM_HXX__ */
