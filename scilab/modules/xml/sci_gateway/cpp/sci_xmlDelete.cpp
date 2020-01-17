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
#include "XMLValidation.hxx"

extern "C"
{
#include "gw_xml.h"
#include "Scierror.h"
#include "api_scilab.h"
#include "xml_mlist.h"
#include "localization.h"
#include "strcmp.h"
}

using namespace org_modules_xml;

int sci_xmlDelete(char *fname, void* pvApiCtx)
{
    int id;
    SciErr err;
    int *addr = 0;

    org_modules_xml::XMLDocument * doc = 0;
    XMLValidation *vf = 0;
    char *com = 0;

    CheckLhs(0, 1);

    if (Rhs == 0)
    {
        Scierror(74, 1);
        return 0;
    }

    err = getVarAddressFromPosition(pvApiCtx, 1, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 1);
        return 0;
    }

    if (isStringType(pvApiCtx, addr))
    {
        if (!checkVarDimension(pvApiCtx, addr, 1, 1))
        {
            Scierror(102, 1);
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, addr, &com) != 0)
        {
            Scierror(1);
            return 0;
        }
        if (!balisc_strcmp(com, "all"))
        {
            org_modules_xml::XMLDocument::closeAllDocuments();
            XMLValidation::closeAllValidationFiles();
        }
        freeAllocatedSingleString(com);
    }
    else
    {
        for (int pos = 1; pos <= Rhs; pos++)
        {
            err = getVarAddressFromPosition(pvApiCtx, pos, &addr);
            if (err.iErr)
            {
                printError(&err, 0);
                Scierror(47, pos);
                return 0;
            }

            if (isXMLDoc(addr, pvApiCtx))
            {
                id = getXMLObjectId(addr, pvApiCtx);
                doc = XMLObject::getFromId < org_modules_xml::XMLDocument > (id);
                if (!doc)
                {
                    Scierror(160, _("XML document"));
                    return 0;
                }
                delete doc;
            }
            else if (isXMLValid(addr, pvApiCtx))
            {
                id = getXMLObjectId(addr, pvApiCtx);
                vf = XMLObject::getFromId < XMLValidation > (id);
                if (!vf)
                {
                    Scierror(160, _("XML validation file"));
                    return 0;
                }
                delete vf;
            }
            else
            {
                Scierror(90, 1, _("XMLDoc"));
                return 0;
            }
        }
    }

    LhsVar(1) = 0;
    PutLhsVar();
    return 0;
}
