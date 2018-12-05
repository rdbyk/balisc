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

#ifndef __COVERAGE_GW_HXX__
#define __COVERAGE_GW_HXX__

#include "cpp_gateway_prototype.hxx"

class CoverageModule
{
private:
    CoverageModule() {};
    ~CoverageModule() {};

public:
    static int Load();
    static int Unload()
    {
        return 1;
    }
};

CPP_GATEWAY_PROTOTYPE_EXPORT(sci_covStart);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_covWrite);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_covStop);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_covMerge);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_profileEnable);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_profileDisable);
CPP_GATEWAY_PROTOTYPE_EXPORT(sci_profileGetInfo);

#endif /* __COVERAGE_GW_HXX__ */

