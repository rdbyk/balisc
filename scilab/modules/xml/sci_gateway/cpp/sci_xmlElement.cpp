/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - Scilab Enterprises - Calixte DENIZET
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

#include "XMLObject.hxx"
#include "XMLDocument.hxx"
#include "XMLElement.hxx"

extern "C"
{
#include "gw_xml.h"
#include "Scierror.h"
#include "api_scilab.h"
#include "xml_mlist.h"
#include "libxml/tree.h"
#include "localization.h"
}

using namespace org_modules_xml;

int sci_xmlElement(char *fname, void* pvApiCtx)
{
    org_modules_xml::XMLDocument * doc = 0;
    XMLElement *elem = 0;
    SciErr err;
    int *addr = 0;
    char *name = 0;

    CheckLhs(1, 1);
    CheckRhs(2, 2);

    err = getVarAddressFromPosition(pvApiCtx, 1, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 1);
        return 0;
    }

    if (!isXMLDoc(addr, pvApiCtx))
    {
        Scierror(90, 1, _("XMLDoc"));
        return 0;
    }

    doc = XMLObject::getFromId < org_modules_xml::XMLDocument > (getXMLObjectId(addr, pvApiCtx));
    if (!doc)
    {
        Scierror(160, _("XML document"));
        return 0;
    }

    err = getVarAddressFromPosition(pvApiCtx, 2, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 2);
        return 0;
    }

    if (!isStringType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
    {
        Scierror(91, 2);
        return 0;
    }

    if (getAllocatedSingleString(pvApiCtx, addr, &name) != 0)
    {
        Scierror(1);
        return 0;
    }

    if ((name[0] == '\0') || xmlValidateName((const xmlChar *)name, 0))
    {
        freeAllocatedSingleString(name);
        Scierror(110, 2, _("valid XML name"));
        return 0;
    }

    elem = new XMLElement(*doc, name);
    freeAllocatedSingleString(name);
    if (!elem->createOnStack(Rhs + 1, pvApiCtx))
    {
        return 0;
    }

    LhsVar(1) = Rhs + 1;
    PutLhsVar();

    return 0;
}
