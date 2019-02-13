// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Calixte DENIZET
// Copyright (C) 2017 - Samuel GOUGEON
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function values = xmlGetValues(xpath, attributes, doc)

    if (nargin ~= 2 & nargin ~= 3) then
        error(73, 2, 3);
    end

    if type(xpath) <> 10 then
        error(91, 1);
    end

    if type(attributes) <> 10 then
        error(90, 2, _("matrix of strings"));
    end

    if nargin == 2 then
        doc = SCIHOME + "/XConfiguration.xml"
    end
    doc0 = doc
    delDoc = (nargin == 2 | type(doc0)==10)
    if type(doc)==10 then
        if isfile(doc)
            try
                doc = xmlRead(doc0);
            catch
                error(_("%s: Invalid ""%s"" file.\n"), "xmlGetValues", tokens(doc0,["/" "\"])($));
            end
        else
            error(52, doc);
        end
    elseif typeof(doc) ~= "XMLDoc" then
        error(90, 3, _("XMLDoc"));
    end

    try
        xp = xmlXPath(doc, xpath);
    catch
        if delDoc then
            xmlDelete(doc);
        end
        error(_("%s: Invalid XPath request.\n"), "xmlGetValues");
    end

    if xp.size == 0 then
        if delDoc then
            xmlDelete(doc);
        end
        error(_("%s: Invalid XPath request."), "xmlGetValues");
    end

    values = [];
    for i = 1 : xp.size
        node = xp(i);
        if node.type ~= "XML_ELEMENT_NODE" then
            if delDoc then
                xmlDelete(doc);
            end
            msg = gettext("%s: Target node is not a XML_ELEMENT_NODE.")
            error(msprintf(msg, "xmlGetValues"));
        end

        attr = node.attributes;
        for j = 1:size(attributes,"*")
            a = attributes(j)
            v = attr(a);
            if v ~= [] then
                values(i,j) = v;
            else
                if delDoc then
                    xmlDelete(doc);
                end
                msg = gettext("%s: Invalid attribute name: %s.")
                error(msprintf(msg, "xmlGetValues", a));
            end
        end
    end
    if xp.size==1 then
        values = matrix(values, size(attributes));
    end
    if delDoc then
        xmlDelete(doc);
    end
endfunction
