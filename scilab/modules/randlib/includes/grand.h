/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - INRIA
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

#ifndef SCI_GRAND
#define SCI_GRAND

#include "machine.h"

int C2F(setgmn) (double *meanv, double *covm, int *ldcovm, int *p, double *parm, int *ierr);
double C2F(genbet) (double *aa, double *bb);
double C2F(genchi) (double *df);
double C2F(genexp) (double *av);
double C2F(genf) (double *dfn, double *dfd);
double C2F(gengam) (double *a, double *r__);
double C2F(gennch) (double *df, double *xnonc);
double C2F(gennf) (double *dfn, double *dfd, double *xnonc);
double C2F(gennor) (double *av, double *sd);
double C2F(sdot) (int *n, double *sx, int *incx, double *sy, int *incy);
double C2F(sexpo) (void);
double C2F(sgamma) (double *a);
double C2F(snorm) (void);
double igngeom(double p);
int C2F(genmn) (double *parm, double *x, double *work);
int C2F(genmul) (int *n, double *p, int *ncat, int *ix);
int C2F(genprm) (double *array, int *larray);
int C2F(ignbin) (int *n, double *pp);
int C2F(ignnbn) (int *n, double *p);
int C2F(ignpoi) (double *mu);
int C2F(phrtsd) (char *phrase, int *phrasel, int *seed1, int *seed2, int phrase_len);
int C2F(spofa) (double *a, int *lda, int *n, int *info);
double C2F(ranf)(void);
double ignlgi(void);
double C2F(ignuin)(double *a, double *b);

#endif /** SCI_GRAND   **/

