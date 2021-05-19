// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Calixte DENIZET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2019 - Samuel GOUGEON
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function xmlSetValues(xpath, kv, doc)
	// Sets attribute=values pairs for a given tag in a XML document.
	// - xpath is something like "//web/body/proxy", the target must be a single node/tag
	// - kv is a matrix of strings 2xN: keys are in the first row and values in the
	//   seconde one.
	// - doc (optional): the prefs xml document where to set the values
	//                   (take care: in this case xmlWrite is not called)
	//

	fname = "xmlSetValues"

    if (nargin <> 2 && nargin <> 3) then
        error(73, 2, 3);
    end

    if type(xpath) <> 10 then
        error(91, 1);
    end

    if type(kv) <> 10 then
        error(91, 2);
    end

    if (size(kv, "r") ~= 2) then
        error(100, 2, _("2xN matrix"));
    end

    if nargin == 2 then
        try
            doc = xmlRead(SCIHOME + "/XConfiguration.xml");
        catch
            error(_("%s: Invalid XConfiguration.xml file.\n"), fname);
        end
    elseif typeof(doc) ~= "XMLDoc" then
        error(90, 3, _("XMLDoc"));
    end

    try
        xp = xmlXPath(doc, xpath);
    catch
        if nargin == 2 then
            xmlDelete(doc);
        end
        error(110, 1,_("valid XPath"));
    end

    if xp.size ~= 1 then
        if nargin == 2 then
            xmlDelete(doc);
        end
        error(110, 1,_("valid XPath"));
    end

    node = xp(1);
    if node.type ~= "XML_ELEMENT_NODE" then
        if nargin == 2 then
            xmlDelete(doc);
        end
        error(_("%s: Target node is not a XML_ELEMENT_NODE."), fname);
    end

    attr = node.attributes;
    for i = 1:size(kv, "c")
        v = attr(kv(1, i));
        if v ~= [] then
            attr(kv(1, i)) = kv(2, i);
        else
            if nargin == 2 then
                xmlDelete(doc);
            end
            error(_("%s: Invalid attribute name: %s."), fname, kv(1, i));
        end
    end

    if nargin == 2 then
        xmlWrite(doc);
        xmlDelete(doc);
    end
endfunction
