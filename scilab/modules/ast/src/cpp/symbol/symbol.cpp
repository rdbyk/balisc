/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007-2008 - INRIA - Bruno JOFRET
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

#ifndef SYMBOL_HXX
#define SYMBOL_HXX

#include "symbol.hxx"

symbol::Symbol::string_set_type symbol::Symbol::_set;

namespace symbol
{
wchar_t **Symbol::getAll()
{
    string_set_type::const_iterator it;
    wchar_t **resultVector = new wchar_t*[getSize()];
    int i = 0;

    for (it = _set.begin() ; it != _set.end() ; ++it, ++i)
    {
        resultVector[i] = const_cast<wchar_t*>(it->c_str());
    }

    return resultVector;
}
}

#endif // !SYMBOL_SYMBOL_HXX
