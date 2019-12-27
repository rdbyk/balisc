/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Antoine ELIAS
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

#ifndef __TLIST_HXX__
#define __TLIST_HXX__

#include <list>
#include <vector>
#include "list.hxx"
#include "string.hxx"

namespace types
{
class TList : public List
{
public :
    TList();
    virtual ~TList();

protected:
    TList(TList *_oTListCopyMe) : List(_oTListCopyMe) {}

public :

    ScilabType                      getType(void) override
    {
        return ScilabTList;
    }

    bool                            isTList() override
    {
        return true;
    }

    virtual TList*                  clone() override;

    bool                            exists(const std::wstring& _sKey);
    InternalType*                   getField(const std::wstring& _sKey);
    int getFieldIndex(const std::wstring& _sKey);
    void set(const std::wstring& _sKey, InternalType* _pIT);
    void set(const int _iIndex, InternalType* _pIT) override;

    using List::extract; // to avoid this extract to hide extract in list
    bool                            extract(const std::wstring& name, InternalType *& out) override;

    virtual bool invoke(typed_list & in, optional_list & opt, int _iRetCount, typed_list & out, const ast::Exp & e) override;

    bool isFieldExtractionOverloadable() const override
    {
        return true;
    }

    InternalType*                   extractStrings(const std::list<std::wstring>& _stFields);

    /* return type as string ( double, int, cell, list, ... )*/
    virtual std::wstring            getTypeStr() const override;
    /* return type as short string ( s, i, ce, l, ... )*/
    virtual std::wstring            getShortTypeStr() const override;

    String*                         getFieldNames() const;

    bool                            toString(std::wostringstream& ostr) override;

    bool                            getMemory(int* _piSize, int* _piSizePlusType) override;

private :
};
}

#endif /* __TLIST_HXX__ */
