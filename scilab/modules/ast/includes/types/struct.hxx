/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
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

#ifndef __STRUCT_HXX__
#define __STRUCT_HXX__

#include "list.hxx"
#include "arrayof.hxx"
#include "singlestruct.hxx"

extern "C"
{
#include "localization.h"
}

namespace types
{
class Struct : public ArrayOf<SingleStruct*>
{
public :
    ~Struct();
    Struct();
    // _bInit: true, fill the struct by empty SingleStructs.
    // _bInit: false, Only alocate the array and fill each element by NULL.
    //           that mean you have to fill it by SingleStructs and increase there ref.
    Struct(int _iRows, int _iCols, bool _bInit = true);
    Struct(int _iDims, const int* _piDims, bool _bInit = true);

private :
    Struct(Struct* _oCellCopyMe);

public :

    inline ScilabType           getType(void) override
    {
        return ScilabStruct;
    }
    inline ScilabId             getId(void) override
    {
        return IdStruct;
    }

    bool                        isStruct() override
    {
        return true;
    }
    bool                        isEmpty();

    bool transpose(InternalType *& out) override;


    /**
    ** Clone
    ** Create a new List and Copy all values.
    */
    Struct*                     clone() override;

    void set(int _iRows, int _iCols, SingleStruct* _pIT) override;
    void set(int _iRows, int _iCols, const SingleStruct* _pIT);
    void set(int _iIndex, SingleStruct* _pIT) override;
    void set(int _iIndex, const SingleStruct* _pIT);
    void set(SingleStruct** _pIT);

    bool                        operator==(const InternalType& it) override;
    bool                        operator!=(const InternalType& it) override;

    /* return type as string ( double, int, cell, list, ... )*/
    virtual std::wstring        getTypeStr() const override
    {
        return L"struct";
    }
    /* return type as short string ( s, i, ce, l, ... )*/
    virtual std::wstring        getShortTypeStr() const override
    {
        return L"st";
    }
    virtual bool                isContainer(void) override
    {
        return true;
    }

    bool isTrue() override
    {
        if (getSize() == 0)
        {
            return false;
        }

        for (int i = 0; i < getSize(); ++i)
        {
            if (!get(i)->isTrue())
            {
                return false;
            }
        }

        return true;
    }

    virtual bool neg(InternalType*& out)  override
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
            pb[i] = !get(i)->isTrue();
        }

        return true;
    }

    bool                        subMatrixToString(std::wostringstream& ostr, int* _piDims, int _iDims) override;
    String*                     getFieldNames();
    bool                        exists(const std::wstring& _sKey);
    Struct*                     addField(const std::wstring& _sKey);
    Struct*                     addFieldFront(const std::wstring& _sKey);
    Struct*                     removeField(const std::wstring& _sKey);
    bool                        toString(std::wostringstream& ostr) override;
    List*                       extractFieldWithoutClone(const std::wstring& _wstField);
    typed_list                  extractFields(std::vector<std::wstring> _wstFields);
    typed_list                  extractFields(typed_list* _pArgs);
    InternalType *              extractField(const std::wstring& wstField);

    Struct*                     resize(int* _piDims, int _iDims) override;
    Struct*                     resize(int _iNewRows, int _iNewCols) override;

    /*specials functions to disable clone operation during copydata*/
    InternalType*               extractWithoutClone(typed_list* _pArgs);
    void                        setCloneInCopyValue(bool _val);

    using ArrayOf<SingleStruct *>::extract;
    bool extract(const std::wstring& name, InternalType *& out) override;

    virtual bool invoke(typed_list & in, optional_list & opt, int _iRetCount, typed_list & out, const ast::Exp & e) override;

    virtual int getInvokeNbOut() override
    {
        return -1;
    }

    bool                        getMemory(int* _piSize, int* _piSizePlusType) override;

private :
    virtual SingleStruct*       getNullValue() override;
    virtual Struct*             createEmpty(int _iDims, int* _piDims, bool _bComplex = false) override;
    virtual Struct*             createEmpty() override;
    virtual SingleStruct*       copyValue(SingleStruct* _pData) override;
    virtual void                deleteAll() override;
    virtual void                deleteImg() override;
    virtual SingleStruct**      allocData(int _iSize) override;
    virtual void                deleteData(SingleStruct* data) override;

    bool                        m_bDisableCloneInCopyValue;

};
}

#ifdef _MSC_VER
template class types::ArrayOf<types::SingleStruct*>; //Struct
#endif
#endif /* !__STRUCT_HXX__ */
