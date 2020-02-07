// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005 - INRIA - Allan CORNET
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

if (isdef("genlib") == %f) then
    exec(SCI + "/modules/functions/scripts/buildmacros/loadgenlib.sce");
end
//------------------------------------
genlib("optimizationlib","SCI/modules/optimization/macros",%f,%t);
genlib("neldermeadlib","SCI/modules/optimization/macros/neldermead",%f,%t);
genlib("optimbaselib","SCI/modules/optimization/macros/optimbase",%f,%t);
genlib("optimsimplexlib","SCI/modules/optimization/macros/optimsimplex",%f,%t);
genlib("genetic_algorithmslib","SCI/modules/optimization/macros/genetic",%f,%t);
//------------------------------------
