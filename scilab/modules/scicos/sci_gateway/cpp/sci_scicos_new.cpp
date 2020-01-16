/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2014-2016 - Scilab Enterprises - Clement DAVID
 *
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include <string>
#include <sstream>

#include "gw_scicos.hxx"

#include "types.hxx"
#include "int.hxx"
#include "string.hxx"
#include "tlist.hxx"
#include "mlist.hxx"
#include "list.hxx"
#include "function.hxx"

#include "view_scilab/Adapters.hxx"
#include "view_scilab/BaseAdapter.hxx"
#include "view_scilab/BlockAdapter.hxx"
#include "view_scilab/CprAdapter.hxx"
#include "view_scilab/DiagramAdapter.hxx"
#include "view_scilab/GraphicsAdapter.hxx"
#include "view_scilab/LinkAdapter.hxx"
#include "view_scilab/ModelAdapter.hxx"
#include "view_scilab/ParamsAdapter.hxx"
#include "view_scilab/ScsAdapter.hxx"
#include "view_scilab/StateAdapter.hxx"
#include "view_scilab/TextAdapter.hxx"

#include "utilities.hxx"
#include "Controller.hxx"
#include "model/Annotation.hxx"
#include "model/Block.hxx"
#include "model/Diagram.hxx"
#include "model/Link.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

static const std::string funame = "scicos_new";

using namespace org_scilab_modules_scicos;

template<class Adaptor, class Adaptee>
types::InternalType * alloc_and_set(kind_t k, types::String* type_name, types::typed_list &in)
{
    Controller controller;

    // create the associated object and own it
    ScicosID uid = controller.createObject(k);
    Adaptor* adaptor = new Adaptor(controller, controller.getBaseObject<Adaptee>(uid));

    // the first header entry is the type
    for (int i = 1; i < (int)in.size(); i++)
    {
        std::wstring name (type_name->get(i));
        if (!adaptor->setProperty(name, in[i], controller))
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: unable to set \"%ls\".\n"), funame.data(), i, name.data());
            adaptor->killMe();
            return 0;
        }
    }

    return adaptor;
}

template<class Adaptor, class Adaptee, class T>
types::InternalType * set_tlist(T* as, types::String* type_name, types::typed_list &in)
{
    Controller controller;

    // check header by using a null object
    Adaptor adaptor;
    for (int i = 1; i < (int)in.size(); i++)
    {
        std::wstring name(type_name->get(i));
        if (!adaptor.hasProperty(name))
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: unable to set \"%ls\".\n"), funame.data(), i, name.data());
            return 0;
        }
    }

    // copy the data
    as->set(0, type_name->clone());
    for (int i = 1; i < (int)in.size(); i++)
    {
        as->set(i, in[i]);
    }

    return as;
}

static types::Function::ReturnValue allocate(types::typed_list &in, int /*_iRetCount*/, types::typed_list &out)
{
    types::InternalType* type = in[0];

    types::String* type_name = type->getAs<types::String>();
    if (type_name->getRows() > 1)
    {
        Scierror(999, _("%s: Wrong size for input argument #%d: Row vector expected.\n"), funame.data(), 1);
        return types::Function::Error;
    }

    if (type_name->getCols() != (int) in.size())
    {
        Scierror(999, _("%s: Wrong number of input argument: %d expected.\n"), funame.data(), type_name->getCols());
        return types::Function::Error;
    }

    /*
     * allocate the right adapter then try to set fields values
     */

    const view_scilab::Adapters::adapters_index_t adapter_index = view_scilab::Adapters::instance().lookup_by_typename(type_name->getFirst());
    types::InternalType* returnType;
    switch (adapter_index)
    {
        case view_scilab::Adapters::BLOCK_ADAPTER:
            returnType = alloc_and_set<view_scilab::BlockAdapter, model::Block>(BLOCK, type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::CPR_ADAPTER:
            returnType = set_tlist<view_scilab::CprAdapter, model::Diagram>(new types::TList(), type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::DIAGRAM_ADAPTER:
            returnType = alloc_and_set<view_scilab::DiagramAdapter, model::Diagram>(DIAGRAM, type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::GRAPHIC_ADAPTER:
            returnType = set_tlist<view_scilab::GraphicsAdapter, model::Block>(new types::MList(), type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::LINK_ADAPTER:
            returnType = alloc_and_set<view_scilab::LinkAdapter, model::Link>(LINK, type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::MODEL_ADAPTER:
            returnType = set_tlist<view_scilab::ModelAdapter, model::Block>(new types::MList(), type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::PARAMS_ADAPTER:
            returnType = set_tlist<view_scilab::ParamsAdapter, model::Diagram>(new types::TList(), type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::SCS_ADAPTER:
            returnType = alloc_and_set<view_scilab::ScsAdapter, model::Diagram>(DIAGRAM, type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::STATE_ADAPTER:
            returnType = set_tlist<view_scilab::StateAdapter, model::Diagram>(new types::TList(), type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        case view_scilab::Adapters::TEXT_ADAPTER:
            returnType = alloc_and_set<view_scilab::TextAdapter, model::Annotation>(ANNOTATION, type_name, in);
            if (returnType == nullptr)
            {
                return types::Function::Error;
            }
            break;
        default:
            Scierror(999, _("%s: Wrong value for input argument #%d:  \"%ls\" type is not managed.\n"), funame.data(), 1, type_name->getFirst());
            return types::Function::Error;
    }
    out.push_back(returnType);

    return types::Function::OK;
}

static ScicosID get(types::GenericType* UIDs, int index)
{
    ScicosID ret;

    switch (UIDs->getType())
    {
        case types::InternalType::ScilabString:
        {
            wchar_t* str = UIDs->getAs<types::String>()->get(index);
            std::wistringstream iss(str);
            iss >> std::hex >> ret;
            break;
        }
        case types::InternalType::ScilabInt64:
            ret = UIDs->getAs<types::Int64>()->get(index);
            break;
        default:
            ret = ScicosID();
            break;
    }

    return ret;
}

static types::Function::ReturnValue get(types::GenericType* UIDs, int _iRetCount, types::typed_list &out)
{
    _iRetCount = std::max(1, _iRetCount);

    if (UIDs->getSize() != _iRetCount)
    {
        Scierror(999, _("%s: Wrong size for input argument #%d: %dx%d expected.\n"), funame.data(), 1, _iRetCount, 1);
        return types::Function::Error;
    }


    Controller controller;
    types::Function::ReturnValue retValue = types::Function::OK;
    for (int i = 0; i < _iRetCount; ++i)
    {
        ScicosID uid = get(UIDs, i);

        // create the associated object
        model::BaseObject* o = controller.getBaseObject(uid);
        if (o == nullptr)
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: invalid UID.\n"), funame.data(), 1);
            retValue = types::Function::Error;
            break;
        }

        switch (o->kind())
        {
            case DIAGRAM:
                out.push_back(new view_scilab::DiagramAdapter(controller, controller.referenceBaseObject<model::Diagram>(o)));
                break;
            case BLOCK:
                out.push_back(new view_scilab::BlockAdapter(controller, controller.referenceBaseObject<model::Block>(o)));
                break;
            case LINK:
                out.push_back(new view_scilab::LinkAdapter(controller, controller.referenceBaseObject<model::Link>(o)));
                break;
            default:
                Scierror(999, _("%s: Wrong value for input argument #%d: not handled kind.\n"), funame.data(), 1);
                retValue = types::Function::Error;
                break;
        }
    }

    if (retValue != types::Function::OK)
    {
        // something goes wrong, release the allocated data
        for (types::typed_list::iterator it = out.begin(); it != out.end(); ++it)
        {
            delete *it;
        }
    }

    return retValue;
}

types::Function::ReturnValue sci_scicos_new(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    _iRetCount = std::max(1, _iRetCount);

    if (in.size() < 1)
    {
        Scierror(999, _("%s: Wrong number of input arguments: At least %d expected.\n"), funame.data(), 1);
        return types::Function::Error;
    }
    if (_iRetCount > 1)
    {
        Scierror(999, _("%s: Wrong number of output arguments: %d expected.\n"), funame.data(), 1);
        return types::Function::Error;
    }

    types::InternalType* type = in[0];
    switch (type->getType())
    {
        case types::InternalType::ScilabString:
            if (in.size() == 1)
            {
                return get(type->getAs<types::String>(), _iRetCount, out);
            }
            else
            {
                return allocate(in, _iRetCount, out);
            }
        case types::InternalType::ScilabInt64:
            return get(type->getAs<types::Int64>(), _iRetCount, out);
        default:
            Scierror(999, _("%s: Wrong type for input argument #%d: String or ID expected.\n"), funame.data(), 1);
            return types::Function::Error;
    }
}

