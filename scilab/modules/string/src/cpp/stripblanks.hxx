/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
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

#ifndef __STRIPBLANKS_HXX__
#define __STRIPBLANKS_HXX__

#include "string.hxx"

/**
* remove blank or tab characters in a string matrix
* @param[in] String: input Strings
* @param[in] Bool: remove TAB if get() != 0
* @return String: output String
*/
types::String * stripblanks(types::String *InputStrings, bool bWithTAB, int flag);

#endif /* __STRIPBLANKS_HXX__ */
