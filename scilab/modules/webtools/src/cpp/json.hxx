/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2016 - Scilab Enterprises - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 */

#ifndef __JSON_HXX__
#define __JSON_HXX__

#include "api_scilab.h"
#include "internal.hxx"

//api C++
std::string toJSON(types::InternalType* it, int indent = 0);
types::InternalType* fromJSON(const std::string& s);

//api C
std::string toJSON(scilabEnv env, scilabVar var, int indent = 0);
scilabVar fromJSON(scilabEnv env, const std::string& s);

#endif /* !__JSON_HXX__ */
