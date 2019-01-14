/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Cedric DELAMARRE
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

#include "history_manager_gw.hxx"
#include "function.hxx"
#include "HistoryManager.hxx"
#include "double.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
#include "sci_malloc.h"
}

types::Function::ReturnValue sci_removelinehistory(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() == 1)
    {
        if ((in[0]->isDouble() == false) || (in[0]->getAs<types::Double>()->isScalar() == false))
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: A double expected.\n"), "removelinehistory", 1);
            return types::Function::Error;
        }

        types::Double* pDbl = in[0]->getAs<types::Double>();
        int size = HistoryManager::getInstance()->getNumberOfLines() - 1;

        if ((pDbl->getFirst() < 0) || (pDbl->getFirst() > size))
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: Must be in the interval [%d, %d].\n"), "removelinehistory", 1, 0, size);
            return types::Function::Error;
        }
        char* pcLigne = HistoryManager::getInstance()->getNthLine(pDbl->getFirst());
        if (HistoryManager::getInstance()->isBeginningSessionLine(pcLigne))
        {
            do
            {
                HistoryManager::getInstance()->deleteNthLine(pDbl->getFirst());
                FREE(pcLigne);
                pcLigne = HistoryManager::getInstance()->getNthLine(pDbl->getFirst());
                size = HistoryManager::getInstance()->getNumberOfLines();
            }
            while ((!HistoryManager::getInstance()->isBeginningSessionLine(pcLigne)) && (pDbl->getFirst() < size));
        }
        else
        {
            HistoryManager::getInstance()->deleteNthLine(pDbl->getFirst());
        }
        FREE(pcLigne);
    }
    else
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), "removelinehistory", 1);
        return types::Function::Error;
    }
    return types::Function::OK;
}
