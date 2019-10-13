/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2013 - Scilab Enterprises - Antoine Elias
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

#include "data_structures_gw.hxx"
#include "internal.hxx"
#include "function.hxx"
#include "double.hxx"
#include "int.hxx"
#include "string.hxx"
#include "list.hxx"
#include "mlist.hxx"
#include "tlist.hxx"
#include "struct.hxx"
#include "user.hxx"

extern "C"
{
#include "Scierror.h"
#include "sci_malloc.h"
#include "localization.h"
}

static types::Function::ReturnValue sci_getfieldStruct(types::typed_list &in, int _iRetCount, types::typed_list &out);
static types::Function::ReturnValue sci_getfieldUserType(types::typed_list &in, int _iRetCount, types::typed_list &out);

types::Function::ReturnValue sci_getfield(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 2)
    {
        Scierror(71, 2);
        return types::Function::Error;
    }

    //special case for struct
    if (in[1]->isStruct())
    {
        return sci_getfieldStruct(in, _iRetCount, out);
    }

    //special case for UserType
    if (in[1]->isUserType())
    {
        return sci_getfieldUserType(in, _iRetCount, out);
    }

    types::InternalType* pIndex = in[0];
    if (in[1]->isList() == false && in[1]->isMList() == false && in[1]->isTList() == false)
    {
        Scierror(90, 2, _("list"));
        return types::Function::Error;
    }

    types::List* pL = in[1]->getAs<types::List>();
    types::InternalType* pITOut = NULL;

    if (pIndex->isString())
    {
        //extraction by fieldnames
        if (pL->isMList() == false && pL->isTList() == false)
        {
            Scierror(2);
            return types::Function::Error;
        }

        types::TList* pT = pL->getAs<types::TList>();
        types::String* pS = pIndex->getAs<types::String>();

        std::list<std::wstring> stFields;

        //check output arguments count
        for (int i = 0 ; i < pS->getSize() ; i++)
        {
            std::wstring wst = pS->get(i);
            if (pT->exists(wst) == false)
            {
                Scierror(2);
                return types::Function::Error;
            }

            stFields.push_back(pS->get(i));
        }

        pITOut = pT->extractStrings(stFields);
    }
    else
    {
        //extraction by index
        types::typed_list Args;
        Args.push_back(pIndex);
        pITOut = pL->extract(&Args);
    }

    if (pITOut == NULL)
    {
        Scierror(2);
        return types::Function::Error;
    }

    types::List* pList = pITOut->getAs<types::List>();
    int iListSize = pList->getSize();

    for (int i = 0; i < iListSize; i++)
    {
        out.push_back(pList->get(i));
    }

    pList->killMe();

    return types::Function::OK;
}

static types::Function::ReturnValue sci_getfieldStruct(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::InternalType* pIndex = in[0];
    types::Struct* pSt = in[1]->getAs<types::Struct>();
    types::typed_list vectResult;

    if (pIndex->isString())
    {
        types::String* pFields = pIndex->getAs<types::String>();
        std::vector<std::wstring> wstFields;

        for (int i = 0 ; i < pFields->getSize() ; i++)
        {
            wstFields.push_back(pFields->get(i));
        }

        vectResult = pSt->extractFields(wstFields);
    }
    else
    {
        //extraction by index
        // do not extract myself of myself
        types::typed_list input;
        input.push_back(in[0]);
        vectResult = pSt->extractFields(&input);
    }

    if (vectResult.size() == 0)
    {
        Scierror(2);
        return types::Function::Error;
    }

    for (int i = 0 ; i < vectResult.size() ; i++)
    {
        out.push_back(vectResult[i]);
    }

    return types::Function::OK;
}

static types::Function::ReturnValue sci_getfieldUserType(types::typed_list &in, int /*_iRetCount*/, types::typed_list &out)
{
    types::UserType* pUT = in[1]->getAs<types::UserType>();

    if (in[0]->isDouble())
    {
        types::Double* pIndex = in[0]->getAs<types::Double>();

        // Extract the properties
        types::typed_list one (1, new types::Double(1));
        types::InternalType* properties = pUT->extract(&one);
        if (!properties->isString())
        {
            Scierror(999, _("%s: Could not read the argument #%d properties.\n"), "getfield", 2);
            one[0]->killMe();
            return types::Function::Error;
        }
        one[0]->killMe();

        types::String* propertiesStr = properties->getAs<types::String>();

        // Checking the index validity
        int index = pIndex->getFirst();
        if (floor(index) != index)
        {
            Scierror(111, 1);
            properties->killMe();
            return types::Function::Error;
        }
        if (index < 1 || index > 1 + propertiesStr->getSize())
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: At most %d expected.\n"), "getfield", 1, 1 + propertiesStr->getSize());
            properties->killMe();
            return types::Function::Error;
        }

        if (index == 1)
        {
            // Return the properties
            types::String* ret = new types::String(1, 1 + propertiesStr->getSize());
            ret->set(0, pUT->getTypeStr().c_str());
            for (int i = 0; i < propertiesStr->getSize(); ++i)
            {
                ret->set(i + 1, propertiesStr->get(i));
            }
            out.push_back(ret);
        }
        else
        {
            // Return property number 'index-2'
            types::InternalType* field;
            pUT->extract(propertiesStr->get(index - 2), field);
            out.push_back(field);
        }

        properties->killMe();
        return types::Function::OK;
    }
    else
    {
        Scierror(92, 1);
        return types::Function::Error;
    }
}
