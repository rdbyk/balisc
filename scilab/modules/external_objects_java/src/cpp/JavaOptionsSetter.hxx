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

/*--------------------------------------------------------------------------*/

#ifndef __JAVAOPTIONSSETTER_HXX__
#define __JAVAOPTIONSSETTER_HXX__

#include "ScilabOptionsSetter.hxx"

using namespace org_modules_external_objects;

namespace org_scilab_modules_external_objects_java
{

class JavaOptionsHelper;

class JavaOptionsSetter : public ScilabOptionsSetter
{

public:

    static const unsigned int SHOWPRIVATE;

    JavaOptionsSetter(JavaOptionsHelper & _helper, unsigned int _type);

    JavaOptionsSetter(const JavaOptionsSetter & setter);

    ~JavaOptionsSetter() { }

    void set(const bool state);

    bool get() const;
};
}

#endif // __JAVAOPTIONSSETTER_HXX__
