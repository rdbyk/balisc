/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Calixte DENIZET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#ifndef __GW_XML_H__
#define __GW_XML_H__

#include "c_gateway_prototype.h"

STACK_GATEWAY_PROTOTYPE (sci_xmlRead);
STACK_GATEWAY_PROTOTYPE (sci_xmlDelete);
STACK_GATEWAY_PROTOTYPE (sci_xmlDump);
STACK_GATEWAY_PROTOTYPE (sci_xmlGetOpenDocs);
STACK_GATEWAY_PROTOTYPE (sci_xmlXPath);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLDoc_e);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLElem_e);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLNs_e);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLAttr_e);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLList_e);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLDoc_p);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLElem_p);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLNs_p);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLList_p);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLAttr_p);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLSet_p);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLList_size);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLSet_size);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLAttr_size);
STACK_GATEWAY_PROTOTYPE (sci_percent_c_i_XMLDoc);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLElem_i_XMLDoc);
STACK_GATEWAY_PROTOTYPE (sci_percent_c_i_XMLElem);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLElem_i_XMLElem);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLAttr_i_XMLElem);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLList_i_XMLElem);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLNs_i_XMLElem);
STACK_GATEWAY_PROTOTYPE (sci_percent_c_i_XMLAttr);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLElem_i_XMLList);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLDoc_i_XMLList);
STACK_GATEWAY_PROTOTYPE (sci_percent_c_i_XMLList);
STACK_GATEWAY_PROTOTYPE (sci_percent_s_i_XMLList);
STACK_GATEWAY_PROTOTYPE (sci_percent_foo_i_XMLList);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLList_i_XMLList);
STACK_GATEWAY_PROTOTYPE (sci_xmlReadStr);
STACK_GATEWAY_PROTOTYPE (sci_xmlFormat);
STACK_GATEWAY_PROTOTYPE (sci_xmlElement);
STACK_GATEWAY_PROTOTYPE (sci_xmlDocument);
STACK_GATEWAY_PROTOTYPE (sci_xmlNs);
STACK_GATEWAY_PROTOTYPE (sci_xmlAddNs);
STACK_GATEWAY_PROTOTYPE (sci_xmlGetNsByHref);
STACK_GATEWAY_PROTOTYPE (sci_xmlGetNsByPrefix);
STACK_GATEWAY_PROTOTYPE (sci_xmlWrite);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLList_length);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLAttr_length);
STACK_GATEWAY_PROTOTYPE (sci_xmlDTD);
STACK_GATEWAY_PROTOTYPE (sci_xmlSchema);
STACK_GATEWAY_PROTOTYPE (sci_xmlRelaxNG);
STACK_GATEWAY_PROTOTYPE (sci_xmlValidate);
STACK_GATEWAY_PROTOTYPE (sci_percent_XMLValid_p);
STACK_GATEWAY_PROTOTYPE (sci_xmlIsValidObject);
STACK_GATEWAY_PROTOTYPE (sci_xmlAsNumber);
STACK_GATEWAY_PROTOTYPE (sci_xmlAsText);
STACK_GATEWAY_PROTOTYPE (sci_xmlRemove);
STACK_GATEWAY_PROTOTYPE (sci_xmlSetAttributes);
STACK_GATEWAY_PROTOTYPE (sci_xmlName);
STACK_GATEWAY_PROTOTYPE (sci_xmlAppend);
STACK_GATEWAY_PROTOTYPE (sci_htmlRead);
STACK_GATEWAY_PROTOTYPE (sci_htmlReadStr);
STACK_GATEWAY_PROTOTYPE (sci_htmlWrite);
STACK_GATEWAY_PROTOTYPE (sci_htmlDump);

#endif /* __GW_XML_H__ */
