/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Bruno JOFRET
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

#ifndef __LU_H__
#define __LU_H__

#define spINSIDE_SPARSE
#include "spConfig.h"
#include "spmatrix.h"
#include "spDefs.h"

#include "machine.h"
#include "localization.h"
#include "sci_malloc.h"

int addluptr (char *ptr); /* */
int getluptr (int sel, char **ptr);
int removeluptr (int sel);
void resetluptr (void); /* to be used to free the lu pointer table */

void C2F(lufact1)(double *val, int *lln, int *col, int *n, int *nel,
                                int *fmatindex, double *eps, double *releps, int *nrank, int *ierr);

void C2F(lusolve1)(int *fmatindex, double *b, double *x, int *ierr);

void C2F(ludel1)(int *fmatindex, int *ierr);

void C2F(lusiz1)(int *fmatindex, int* lsize, int* usize, int *ierr);

void C2F(luget1)(int *fmatindex, int *indP, double *P,
                               int *indl, double *l, int *indu, double *u,
                               int *indQ, double *Q, int *ierr);
#endif /* !__LU_H__ */
