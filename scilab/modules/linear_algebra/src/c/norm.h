/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2013 - Scilab Enterprises - Paul Bignier
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

#include <string.h>         // strcmp
#include "core_math.h"      // Abs, pow, Min and Max
#include "machine.h"        // C2F
#include "localization.h"   // Translations
#include "doublecomplex.h"  // Type doublecomplex

double normString (double *A, int iRows, int iCols, char *flag);
double normStringC (doublecomplex *A, int iRows, int iCols, char *flag);
double normP (double *A, int iRows, int iCols, double p);
double normPC (doublecomplex *A, int iRows, int iCols, double p);

#ifdef _MSC_VER
int la_isinf(double dbl);
#else
#define la_isinf isinf
#endif
