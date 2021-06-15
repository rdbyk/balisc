//<-- CLI SHELL MODE -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Sylvestre LEDRU <sylvestre.ledru@inria.fr>
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// Switch to french with small code
if setlanguage("fr") then
    if getlanguage() <> "fr_FR" then pause, end
end

// Switch to english with small code
lang="en"; setlanguage(lang); if getlanguage() <> "en_US" then pause, end

// Switch to english with full code
lang="en_US"; setlanguage(lang); if getlanguage() <> "en_US" then pause, end

// Switch to french with full code
if setlanguage("fr_FR") then
    if getlanguage() <> "fr_FR" then pause, end
end
