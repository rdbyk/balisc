/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
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

#ifndef __FUNCTIONS_GW_HXX__
#define __FUNCTIONS_GW_HXX__

#include "cpp_gateway_prototype.hxx"

CPP_GATEWAY_PROTOTYPE_EXPORT(sci_exec);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_execstr);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_funclist);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_whereis);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_macrovar);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_macrofile);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_libraryinfo);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_librarieslist);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_testGVN);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_testAnalysis);

#endif /* __FUNCTIONS_GW_HXX__ */
