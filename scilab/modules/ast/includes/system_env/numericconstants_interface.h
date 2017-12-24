/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2015 - Scilab Enterprises - Antoine ELIAS
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

#include "machine.h"

double nc_eps();
double nc_safe_min();
double nc_base();
double nc_eps_machine();
double nc_num_mantissa_digits();
double nc_rounded();
double nc_exp_min();
double nc_double_min();
double nc_exp_max();
double nc_double_max();

//Fortran
double C2F(nc_eps)();
double C2F(nc_safe_min)();
double C2F(nc_base)();
double C2F(nc_eps_machine)();
double C2F(nc_num_mantissa_digits)();
double C2F(nc_rounded)();
double C2F(nc_exp_min)();
double C2F(nc_double_min)();
double C2F(nc_exp_max)();
double C2F(nc_double_max)();
