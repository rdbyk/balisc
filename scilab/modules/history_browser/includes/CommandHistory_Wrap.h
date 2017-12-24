/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
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

#ifndef __COMMANDHISTORY_WRAP_H__
#define __COMMANDHISTORY_WRAP_H__

#ifdef __cplusplus

extern "C"
{
#endif

void CommandHistoryAppendLine (char* _pstLine);
void CommandHistoryLoadFromFile (void);
void CommandHistoryInitialize (void);
void CommandHistoryExpandAll (void);
void CommandHistoryReset(void);
void CommandHistoryDeleteLine(int lineNumber);
void CommandHistoryLaunch(void);

#ifdef __cplusplus
};
#endif

#endif /* __COMMANDHISTORY_WRAP_H__ */

