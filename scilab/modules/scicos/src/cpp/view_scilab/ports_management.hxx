/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2014 - Scilab Enterprises - Paul Bignier
 *  Copyright (C) 2014 - Scilab Enterprises - Clement DAVID
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

#ifndef PORTS_MANAGEMENT_HXX_
#define PORTS_MANAGEMENT_HXX_

#include <cmath>

#include <deque>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

#include "internal.hxx"
#include "bool.hxx"
#include "double.hxx"
#include "string.hxx"

#include "utilities.hxx"
#include "Controller.hxx"
#include "controller_helpers.hxx"
#include "model/Port.hxx"
#include "LinkAdapter.hxx"

extern "C" {
#include "sci_malloc.h"
#include "charEncoding.h"
#include "localization.h"
}

namespace org_scilab_modules_scicos
{
namespace view_scilab
{

/*
 * Utilities function to emit the error messages
 */
template<object_properties_t p>
std::string adapterName(const object_properties_t /*port_kind*/)
{
    switch (p)
    {
        case CONNECTED_SIGNALS:
        case IMPLICIT:
        case LABEL:
        case STYLE:
            return "graphics";
        case DATATYPE_ROWS:
        case DATATYPE_COLS:
        case DATATYPE_TYPE:
        case FIRING:
            return "model";
        default:
            return "";
    }
}

template<object_properties_t p>
std::string adapterFieldName(const object_properties_t port_kind)
{
    std::string postfix;
    switch (p)
    {
        case CONNECTED_SIGNALS:
        {
            switch (port_kind)
            {
                case INPUTS:
                    return "pin";
                case OUTPUTS:
                    return "pout";
                case EVENT_INPUTS:
                    return "pein";
                case EVENT_OUTPUTS:
                    return "peout";
                default:
                    break;
            }
        }
        break;
        case IMPLICIT:
            postfix = "_implicit";
            break;
        case LABEL:
            postfix = "_label";
            break;
        case STYLE:
            postfix = "_style";
            break;
        case DATATYPE_TYPE:
            postfix = "typ";
            break;
        case DATATYPE_ROWS:
            postfix = "2";
            break;
        case DATATYPE_COLS:
            break;
        case FIRING:
            return "firing";
        default:
            break;
    }

    std::string prefix;
    switch (port_kind)
    {
        case INPUTS:
            prefix = "in";
            break;
        case OUTPUTS:
            prefix = "out";
            break;
        case EVENT_INPUTS:
            prefix = "evtin";
            break;
        case EVENT_OUTPUTS:
            prefix = "evtout";
            break;
        default:
            break;
    }

    return prefix + postfix;
}

/*
 * Return a Scilab encoded value for a property.
 */
template<typename Adaptor, object_properties_t p>
types::InternalType* get_ports_property(const Adaptor& adaptor, const object_properties_t port_kind, const Controller& controller)
{
    model::Block* adaptee = adaptor.getAdaptee();

    // Retrieve the identifiers
    std::vector<ScicosID> ids;
    controller.getObjectProperty(adaptee, port_kind, ids);

    // Translate identifiers: shared variables
    int i = 0;
    size_t datatypeIndex = -1;
    // Translate identifiers to return values
    switch (p)
    {
        case STYLE:
        case LABEL:
        {
            if (ids.empty())
            {
                return new types::String(L"");
            }
            types::String* o = new types::String((int)ids.size(), 1);
            for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it, ++i)
            {
                std::string s;
                controller.getObjectProperty(*it, PORT, p, s);
                o->set(i, s.data());
            }
            return o;
        }
        case DATATYPE_TYPE:
            // The type defaults to [1] if no port has been defined
            if (ids.empty())
            {
                return new types::Double(1);
            }
            datatypeIndex++;
        // no break
        case DATATYPE_COLS:
            datatypeIndex++;
        // no break
        case DATATYPE_ROWS:
        {
            datatypeIndex++;
            double* data;
            types::Double* o = new types::Double((int)ids.size(), 1, &data);
            for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it, ++i)
            {
                std::vector<int> v;
                controller.getObjectProperty(*it, PORT, DATATYPE, v);
                data[i] = v[datatypeIndex];
            }
            return o;
        }
        case FIRING:
        {
            double* data;
            types::Double* o = new types::Double((int)ids.size(), 1, &data);
            for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it, ++i)
            {
                controller.getObjectProperty(*it, PORT, p, data[i]);
            }
            return o;
        }
        case IMPLICIT:
        {
            if (ids.empty())
            {
                // When no port is present, return an empty matrix
                return types::Double::Empty();
            }

            types::String* o = new types::String((int)ids.size(), 1);
            for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it, ++i)
            {
                bool v;
                controller.getObjectProperty(*it, PORT, p, v);
                o->set(i, (v == false) ? L"E" : L"I");
            }
            return o;
        }
        case CONNECTED_SIGNALS:
        {
            double* v;
            types::Double* o = new types::Double((int)ids.size(), 1, &v);

            std::vector<ScicosID> children;

            ScicosID parentBlock;
            controller.getObjectProperty(adaptee, PARENT_BLOCK, parentBlock);
            if (parentBlock == ScicosID())
            {
                // Adding to a diagram
                ScicosID parentDiagram;
                controller.getObjectProperty(adaptee, PARENT_DIAGRAM, parentDiagram);

                controller.getObjectProperty(parentDiagram, DIAGRAM, CHILDREN, children);
            }
            else
            {
                // Adding to a superblock
                controller.getObjectProperty(parentBlock, BLOCK, CHILDREN, children);
            }

            for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it, ++i)
            {
                ScicosID id;
                controller.getObjectProperty(*it, PORT, p, id);

                if (id == ScicosID())
                {
                    // Unconnected port, no need to search in 'children'
                    v[i] = 0;
                }
                else
                {
                    std::vector<ScicosID>::iterator found = std::find(children.begin(), children.end(), id);
                    if (found != children.end())
                    {
                        v[i] = static_cast<double>(std::distance(children.begin(), found)) + 1;
                    }
                    else
                    {
                        // connected link not found ; discard it !
                        v[i] = 0;
                    }
                }
            }
            return o;
        }
        default:
            return 0;
    }
}

/*
 * Set a Scilab encoded values as a property.
 *
 * \note this method will ignore or return false if one of the ports does not exist, depending on the property set.
 */
template<typename Adaptor, object_properties_t p>
bool set_ports_property(const Adaptor& adaptor, const object_properties_t port_kind, Controller& controller, types::InternalType* v)
{
    model::Block* adaptee = adaptor.getAdaptee();

    // Retrieve the ports identifiers
    std::vector<ScicosID> ids;
    controller.getObjectProperty(adaptee, port_kind, ids);

    if (v->getType() == types::InternalType::ScilabString)
    {
        types::String* current = v->getAs<types::String>();

        // Translate identifiers: shared variables
        int i = 0;
        // Translate identifiers from values
        switch (p)
        {
            case STYLE:
            case LABEL:
            {
                for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it, ++i)
                {
                    char* c_str = NULL;
                    if (i >= current->getSize())
                    {
                        // If the input isn't large enough, fill each port with empty strings
                        c_str = wide_string_to_UTF8(L"");
                    }
                    else
                    {
                        c_str = wide_string_to_UTF8(current->get(i));
                    }
                    controller.setObjectProperty(*it, PORT, p, std::string(c_str));
                    FREE(c_str);
                }
                return true;
            }
            case IMPLICIT:
            {
                int maxSize = static_cast<int>(ids.size());
                if (current->getSize() < maxSize)
                {
                    maxSize = current->getSize();
                }

                std::wstring Explicit = L"E";
                std::wstring Implicit = L"I";
                for (; i < maxSize; ++i)
                {
                    if (current->get(i) == Implicit)
                    {
                        controller.setObjectProperty(ids[i], PORT, p, true);
                    }
                    else if (current->get(i) == Explicit)
                    {
                        controller.setObjectProperty(ids[i], PORT, p, false);
                    }
                    else
                    {
                        std::string adapter = adapterName<p>(port_kind);
                        std::string field = adapterFieldName<p>(port_kind);
                        get_or_allocate_logger()->log(LOG_WARNING, _("Wrong value for field %s.%s: '%s' unrecognized, only expected '%s' or '%s' vector. Switching to '%s'.\n"), adapter.data(), field.data(), current->get(i), Explicit.c_str(), Implicit.c_str(), Explicit.c_str());
                        controller.setObjectProperty(ids[i], PORT, p, false);
                    }
                }
                for (i = maxSize; i < (int)ids.size(); ++i)
                {
                    // Tag the missing ports as Explicit. This is done to fix the resizing of pin & pout.
                    controller.setObjectProperty(ids[i], PORT, p, false);
                }
                return true;
            }
            default:
                std::string adapter = adapterName<p>(port_kind);
                std::string field = adapterFieldName<p>(port_kind);
                get_or_allocate_logger()->log(LOG_ERROR, _("Wrong type for field %s.%s.\n"), adapter.data(), field.data());
                return false;
        }
    }
    else if (v->getType() == types::InternalType::ScilabDouble)
    {
        types::Double* current = v->getAs<types::Double>();

        // Translate identifiers: shared variables
        int i = 0;
        size_t datatypeIndex = -1;
        // Translate identifiers from values
        switch (p)
        {
            case FIRING:
                if (current->isEmpty())
                {
                    return true;
                }

                if (current->getSize() < static_cast<int>(ids.size()))
                {
                    std::string adapter = adapterName<p>(port_kind);
                    std::string field = adapterFieldName<p>(port_kind);
                    get_or_allocate_logger()->log(LOG_ERROR, _("Wrong dimension for field %s.%s: %d-by-%d expected.\n"), adapter.data(), field.data(), ids.size(), 1);
                    return false;
                }

                for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it, ++i)
                {
                    double firing = current->get(i);

                    controller.setObjectProperty(*it, PORT, p, firing);
                }
                return true;
            case STYLE:
            case LABEL:
                // Do nothing, because if the sizes match, then there are already zero concerned ports, so no ports to update
                return true;

            case DATATYPE_TYPE:
                datatypeIndex++;
            // no break
            case DATATYPE_COLS:
                datatypeIndex++;
            // no break
            case DATATYPE_ROWS:
            {
                datatypeIndex++;

                // ignore the set without error
                if (current->getSize() != static_cast<int>(ids.size()))
                {
                    return true;
                }

                for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it, ++i)
                {
                    std::vector<int> newDataType;
                    controller.getObjectProperty(*it, PORT, DATATYPE, newDataType);

                    double data = current->get(i);
                    if (std::floor(data) != data)
                    {
                        std::string adapter = adapterName<p>(port_kind);
                        std::string field = adapterFieldName<p>(port_kind);
                        get_or_allocate_logger()->log(LOG_ERROR, _("Wrong value for field %s.%s: Round number expected.\n"), adapter.data(), field.data());
                        return false;
                    }

                    newDataType[datatypeIndex] = static_cast<int>(data);
                    controller.setObjectProperty(*it, PORT, DATATYPE, newDataType);
                }
                return true;
            }

            case IMPLICIT:
                // Do nothing, because if the sizes match, then there are already zero concerned ports, so no ports to update
                return true;

            default:
                std::string adapter = adapterName<p>(port_kind);
                std::string field = adapterFieldName<p>(port_kind);
                get_or_allocate_logger()->log(LOG_ERROR, _("Wrong type for field %s.%s .\n"), adapter.data(), field.data());
                return false;
        }

    }
    else if (v->getType() == types::InternalType::ScilabBool)
    {
        switch (p)
        {
            case FIRING:
                // firing=%f is interpreted as "no initial event on the corresponding port", so set a negative value.
                for (std::vector<ScicosID>::iterator it = ids.begin(); it != ids.end(); ++it)
                {
                    controller.setObjectProperty(*it, PORT, p, -1.);
                }
                return true;
            default:
                std::string adapter = adapterName<p>(port_kind);
                std::string field = adapterFieldName<p>(port_kind);
                get_or_allocate_logger()->log(LOG_ERROR, _("Wrong type for field %s.%s .\n"), adapter.data(), field.data());
                return false;
        }
    }
    std::string adapter = adapterName<p>(port_kind);
    std::string field = adapterFieldName<p>(port_kind);
    get_or_allocate_logger()->log(LOG_ERROR, _("Wrong type for field %s.%s .\n"), adapter.data(), field.data());
    return false;
}

/**
 * Fill \a newPorts with \a d values checking content if possible.
 *
 * \param newPorts new ports children's value to be filled
 * \param d the C-array values to set
 * \return true on success, false otherwise
 */
inline void fillNewPorts(std::deque<int>& newPorts, const double* d)
{
    for (std::deque<int>::iterator it = newPorts.begin(); it != newPorts.end(); ++it, ++d)
    {
        *it = static_cast<int>(*d);
    }
}

/**
 * Set the port value
 *
 * \param oldPortObject the old port object
 * \param controller current transaction instance
 * \param children all object in the current layer (diagram or superblock)
 */
template<object_properties_t p>
inline bool updateNewPort(model::Port* oldPortObject, int newPort, Controller& controller, const std::vector<ScicosID>& children)
{
    // update the p property, using newPort as a value
    int datatypeIndex = -1;
    switch (p)
    {
        case DATATYPE_TYPE:
            datatypeIndex++;
        // no break
        case DATATYPE_COLS:
            datatypeIndex++;
        // no break
        case DATATYPE_ROWS:
        {
            datatypeIndex++;
            std::vector<int> datatype;
            controller.getObjectProperty(oldPortObject, DATATYPE, datatype);
            datatype[datatypeIndex] = newPort;
            return controller.setObjectProperty(oldPortObject, DATATYPE, datatype) != FAIL;
        }
        case CONNECTED_SIGNALS:
            if (0 <= newPort && newPort < children.size())
            {
                return controller.setObjectProperty(oldPortObject, p,
                                                    children[newPort]) != FAIL;
            }
            else
            {
                return false;
            }
        default:
            return controller.setObjectProperty(oldPortObject, p, newPort) != FAIL;
    }
}

/**
 * Add a new port
 *
 * \param newPortObject the old port object
 * \param newPort new port children's index or value
 * \param controller current transaction instance
 * \return true on success, false otherwise
 */
template<object_properties_t p>
inline bool addNewPort(model::Port* newPortObject, int newPort, Controller& controller)
{
    // set the requested property, using newPort as a value
    int datatypeIndex = -1;
    switch (p)
    {
        case DATATYPE_TYPE:
            datatypeIndex++;
        // no break
        case DATATYPE_COLS:
            datatypeIndex++;
        // no break
        case DATATYPE_ROWS:
        {
            datatypeIndex++;
            std::vector<int> datatype;
            controller.getObjectProperty(newPortObject, DATATYPE, datatype);
            datatype[datatypeIndex] = newPort;
            return controller.setObjectProperty(newPortObject, DATATYPE, datatype) != FAIL;
        }
        case CONNECTED_SIGNALS:
            return controller.setObjectProperty(newPortObject, p, (ScicosID) newPort) != FAIL;
        default:
            return controller.setObjectProperty(newPortObject, p, newPort) != FAIL;
    }
}

/**
 * Update the ports with a specific property.
 *
 * Create ports if needed, remove ports if needed and set a default property on each port.
 */
template<typename Adaptor, object_properties_t p>
bool update_ports_property(const Adaptor& adaptor, const object_properties_t port_kind, Controller& controller, types::InternalType* v)
{
    model::Block* adaptee = adaptor.getAdaptee();

    if (v->getType() != types::InternalType::ScilabDouble)
    {
        std::string adapter = adapterName<p>(port_kind);
        std::string field = adapterFieldName<p>(port_kind);
        get_or_allocate_logger()->log(LOG_ERROR, _("Wrong type for field %s.%s: Real matrix expected.\n"), adapter.data(), field.data());
        return false;
    }
    types::Double* value = v->getAs<types::Double>();

    ScicosID parentBlock;
    controller.getObjectProperty(adaptee, PARENT_BLOCK, parentBlock);
    ScicosID parentDiagram;
    controller.getObjectProperty(adaptee, PARENT_DIAGRAM, parentDiagram);

    std::vector<ScicosID> children;
    if (parentBlock != ScicosID())
    {
        // Adding to a superblock
        controller.getObjectProperty(parentBlock, BLOCK, CHILDREN, children);
    }
    else
    {
        // Adding to a diagram
        controller.getObjectProperty(parentDiagram, DIAGRAM, CHILDREN, children);
    }

    std::deque<int> newPorts (value->getSize());

    // retrieve old data
    std::vector<ScicosID> previousPorts;
    controller.getObjectProperty(adaptee, port_kind, previousPorts);
    std::deque<model::Port*> oldPorts;
    for (ScicosID pre : previousPorts)
    {
        oldPorts.emplace_back(controller.getBaseObject<model::Port>(pre));
    }

    double* d = value->getReal();
    fillNewPorts(newPorts, d);

    std::vector<model::BaseObject*> deletedObjects;

    // updated ports
    while (!oldPorts.empty() && !newPorts.empty())
    {
        model::Port* oldPort = oldPorts.front();
        oldPorts.pop_front();
        int newPort = newPorts.front();
        newPorts.pop_front();

        if (!updateNewPort<p>(oldPort, newPort, controller, children))
        {
            return false;
        }
    }

    // removed ports
    if (!oldPorts.empty())
    {
        previousPorts.erase(previousPorts.end() - oldPorts.size(), previousPorts.end());

        while (!oldPorts.empty())
        {
            model::Port* oldPort = oldPorts.front();
            oldPorts.pop_front();

            ScicosID signal;
            controller.getObjectProperty(oldPort, CONNECTED_SIGNALS, signal);
            if (signal != ScicosID())
            {
                model::Link* signalObject = controller.getBaseObject<model::Link>(signal);

                // the link is connected, disconnect the other side
                ScicosID oldSignalSrc;
                controller.getObjectProperty(signalObject, SOURCE_PORT, oldSignalSrc);
                ScicosID oldSignalDst;
                controller.getObjectProperty(signalObject, DESTINATION_PORT, oldSignalDst);

                ScicosID unconnected = 0;
                if (oldSignalSrc == oldPort->id())
                {
                    controller.setObjectProperty(oldSignalDst, PORT, CONNECTED_SIGNALS, unconnected);
                }
                else     // oldSignalDst == oldPort
                {
                    controller.setObjectProperty(oldSignalSrc, PORT, CONNECTED_SIGNALS, unconnected);
                }

                children.erase(std::find(children.begin(), children.end(), signalObject->id()));
                deletedObjects.push_back(signalObject);
            }

            deletedObjects.push_back(oldPort);
        }

        controller.setObjectProperty(adaptee, port_kind, previousPorts);
    }

    // added ports
    if (!newPorts.empty())
    {
        while (!newPorts.empty())
        {
            int newPort = newPorts.front();
            newPorts.pop_front();

            model::Port* createdPort = controller.createBaseObject<model::Port>(PORT);
            controller.setObjectProperty(createdPort, SOURCE_BLOCK, adaptee->id());
            switch (port_kind)
            {
                case INPUTS:
                    controller.setObjectProperty(createdPort, PORT_KIND, static_cast<int>(PORT_IN));
                    break;
                case OUTPUTS:
                    controller.setObjectProperty(createdPort, PORT_KIND, static_cast<int>(PORT_OUT));
                    break;
                case EVENT_INPUTS:
                    controller.setObjectProperty(createdPort, PORT_KIND, static_cast<int>(PORT_EIN));
                    break;
                case EVENT_OUTPUTS:
                    controller.setObjectProperty(createdPort, PORT_KIND, static_cast<int>(PORT_EOUT));
                    break;
                default:
                    // should never happen
                    assert(!"Not managed kind of port");
                    return false;
            }
            addNewPort<p>(createdPort, newPort, controller);
            previousPorts.push_back(createdPort->id());
        }

        controller.setObjectProperty(adaptee, port_kind, previousPorts);
    }

    // remove objects from the model after de-association
    for (auto o : deletedObjects)
    {
        controller.deleteBaseObject(o);
    }

    return true;
}

} /* namespace view_scilab */
} /* namespace org_scilab_modules_scicos */

#endif /* PORTS_MANAGEMENT_HXX_ */
