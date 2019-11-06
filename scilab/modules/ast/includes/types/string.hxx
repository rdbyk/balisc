/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - INRIA - Bruno JOFRET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

// This code is separated in string.hxx
// but will be inlined in arrayof.hxx
//
// If you need additionnal headers, please add it in arrayof.hxx

//#ifndef __ARRAYOF_HXX__
//    #error This file must only be include by arrayof.hxx
//#endif

#ifndef __STRING_HXX__
#define __STRING_HXX__

#include <string>
#include <list>

#include "arrayof.hxx"
#include "bool.hxx"
#include "types_transposition.hxx"

namespace types
{
class String : public ArrayOf<wchar_t*>
{
public :
    String(int _iRows, int _iCols);
    String(int _iDims, const int* _piDims);
    String(int _iRows, int _iCols, wchar_t const* const* _pstData);
    String(const wchar_t *_pstData);
    String(const char *_pstData);
    virtual                 ~String();

    static wchar_t* nullValue();

    virtual void set(int _iPos, const wchar_t* _pwstData);
    virtual void set(int _iRows, int _iCols, const wchar_t* _pwstData);
    virtual void set(const wchar_t* const* _pwstData);

    virtual void set(int _iPos, const char* _pcData);
    virtual void set(int _iRows, int _iCols, const char* _pcData);
    virtual void set(const char* const* _pstrData);

    bool                    operator==(const InternalType& it) override;
    bool                    operator!=(const InternalType& it) override;

    bool                    subMatrixToString(std::wostringstream& ostr, int* _piDims, int _iDims) override;
    /* return type as string ( double, int, cell, list, ... )*/
    virtual std::wstring    getTypeStr() const override
    {
        return L"string";
    }
    /* return type as short string ( s, i, ce, l, ... )*/
    virtual std::wstring    getShortTypeStr() const override
    {
        return L"c";
    }
    String*                 clone() override;

    inline ScilabType       getType() override
    {
        return ScilabString;
    }
    inline ScilabId         getId() override
    {
        return isScalar() ? IdScalarString : IdString;
    }
    bool                    isString() override
    {
        return true;
    }

    bool isTrue() override;

    virtual bool neg(InternalType *& /*out*/);

    bool getMemory(int* _piSize, int* _piSizePlusType) override;

    virtual bool transpose(InternalType *& out) override;

    virtual ast::Exp*       getExp(const Location& loc) override;

private :
    void                    deleteString(int _iPos);

    virtual wchar_t*        copyValue(wchar_t* _pwstData) override;
    virtual wchar_t*        copyValue(const wchar_t* _pwstData);
    virtual String*         createEmpty(int _iDims, int* _piDims, bool _bComplex = false) override;
    virtual wchar_t*        getNullValue() override
    {
        return nullValue();
    };
    virtual void            deleteAll() override;
    virtual void            deleteImg() override;
    virtual wchar_t**       allocData(int _iSize) override;
    void                    deleteData(wchar_t* data) override;
    virtual std::wstring toStringInLine();
};
}

#ifdef _MSC_VER
template class types::ArrayOf<wchar_t*>; //String
#endif
#endif /* !__STRING_HXX__ */
