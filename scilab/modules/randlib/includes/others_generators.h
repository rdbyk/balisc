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

#ifndef SCI_OTHER_GEN
#define SCI_OTHER_GEN

/* header for the Mersenne Twister */
unsigned long int randmt(void);
int set_state_mt_simple(double s);
int set_state_mt(double seed_array[]);
void get_state_mt(double state[]);

/* header for kiss */
unsigned long int kiss(void);
int set_state_kiss(double g1, double g2, double g3, double g4);
void get_state_kiss(double g[]);

/* header for clcg2 */
unsigned long int clcg2(void);
int set_state_clcg2(double g1, double g2);
void get_state_clcg2(double g[]);

/* header for scilab urand */
unsigned long int urandc(void);
int set_state_urand(double g);
void get_state_urand(double g[]);

#endif /** SCI_OTHER_GEN   **/
