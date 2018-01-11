/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA
 * Copyright (C) DIGITEO - 2012 - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "BOOL.h"
#include "usewmemcmp.h"
#include "vect_and.h"

void vect_and(const int *v, int m, int n, int *r, int opt)
{
    switch (opt)
    {
        case AND_ON_ALL:
        {
#ifdef USE_WMEMCMP
            wchar_t* vv = (wchar_t*)v;
            r[0] = *vv == TRUE && wmemcmp(vv, v + 1, m * n - 1) == 0;
#else
            int k = 0;
            r[0] = TRUE;
            for (k = 0; k < m * n; k++)
            {
                if (!v[k])
                {
                    r[0] = FALSE;
                    break;
                }
            }
#endif /* USE_WMEMCMP */
        }
        break;
        case AND_BY_COLUMNS:
        {
            int l = 0;
            for (l = 0; l < m; l++)
            {
                int k = 0;
                int i = l;

                r[l] = TRUE;
                for (k = 0; k < n; k++)
                {
                    if (!v[i])
                    {
                        r[l] = FALSE;
                        break;
                    }
                    i += m;
                }
            }
        }
        break;
        case AND_BY_ROWS:
        {
            int k = 0;
            for (k = 0; k < n; k++)
            {
#ifdef USE_WMEMCMP
                wchar_t* vr = (wchar_t*)(v + k * m);
                wchar_t* vvr = vr;
                r[k] = *vvr == TRUE && wmemcmp(vvr, vr + 1, m - 1) == 0;
#else
                int l = 0;
                int i = k * m;
                r[k] = TRUE;
                for (l = 0; l < m; l++)
                {
                    if (!v[i++])
                    {
                        r[k] = FALSE;
                        break;
                    }
                }
#endif /* USE_WMEMCMP */
            }
        }
        break;
    }
}
