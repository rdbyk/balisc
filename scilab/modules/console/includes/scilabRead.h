/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
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

#ifndef __SCILAB_READ_H__
#define __SCILAB_READ_H__

#include "machine.h"

typedef char* (*SCILAB_INPUT_METHOD)(void);

void C2F(scilabread)(char* strRead, int len);
void setScilabInputMethod(SCILAB_INPUT_METHOD reader);
int scilabRead();

#endif /* !__SCILAB_READ_H__ */
