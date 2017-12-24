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

#ifndef H_CLCG4_H
#define H_CLCG4_H

#define Maxgen  100

typedef enum {InitialSeed, LastSeed, NewSeed} SeedType;

int set_seed_clcg4(int g, double s0, double s1, double s2, double s3);
void get_state_clcg4(int g, double s[4]);
void init_generator_clcg4(int g, SeedType Where);
void advance_state_clcg4(int g, int k);
int set_initial_seed_clcg4(double s0, double s1, double s2, double s3);
unsigned int clcg4(int g);

#endif
