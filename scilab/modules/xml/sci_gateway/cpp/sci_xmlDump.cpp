/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - Scilab Enterprises - Calixte DENIZET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
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
#include <vector>

#include "XMLObject.hxx"
#include "XMLDocument.hxx"
#include "XMLElement.hxx"
#include "XMLNs.hxx"
#include "XMLAttr.hxx"
#include "SplitString.hxx"

extern "C"
{
#include "gw_xml.h"
#include "Scierror.h"
#include "api_scilab.h"
#include "xml_mlist.h"
#include "localization.h"
}

using namespace org_modules_xml;

int sci_xmlDump(char *fname, void* pvApiCtx)
{
    XMLObject *obj = 0;
    int id;
    int type;
    int b;
    SciErr err;
    int *addr = 0;

    std::vector < std::string > lines;
    std::vector < const char *>clines;
    bool indent = true;

    CheckLhs(0, 1);
    CheckRhs(1, 2);

    err = getVarAddressFromPosition(pvApiCtx, 1, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 1);
        return 0;
    }

    type = isXMLObject(addr, pvApiCtx);
    if (!type)
    {
        Scierror(90, 1, _("XML object"));
        return 0;
    }

    id = getXMLObjectId(addr, pvApiCtx);
    obj = XMLObject::getFromId < XMLObject > (id);
    if (!obj)
    {
        Scierror(160, _("XML object"));
        return 0;
    }

    if (Rhs == 2)
    {
        err = getVarAddressFromPosition(pvApiCtx, 2, &addr);
        if (err.iErr)
        {
            printError(&err, 0);
            Scierror(47, 2);
            return 0;
        }

        if (!isBooleanType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
        {
            Scierror(90, 2, _("boolean"));
            return 0;
        }

        if (getScalarBoolean(pvApiCtx, addr, &b))
        {
            return 0;
        }
        indent = b != 0;
    }

    lines = std::vector < std::string > ();
    SplitString::split(obj->dump(indent), lines);
    clines = std::vector < const char *>(lines.size());

    for (unsigned int i = 0; i < lines.size(); i++)
    {
        clines[i] = lines[i].c_str();
    }

    if (clines.size())
    {
        err = createMatrixOfString(pvApiCtx, Rhs + 1, (int)lines.size(), 1, const_cast < const char * const *>(&(clines[0])));
    }
    else
    {
        err = createMatrixOfDouble(pvApiCtx, Rhs + 1, 0, 0, 0);
    }

    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(1);
        return 0;
    }

    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    return 0;
}
