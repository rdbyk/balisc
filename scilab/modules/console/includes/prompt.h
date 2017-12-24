/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Sylvestre LEDRU
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

#ifndef _PROMPT_H_
#define _PROMPT_H_

#include "machine.h"            /* C2F */

/* Define prompts of Scilab */
#ifdef SCIPROMPT
#undef SCIPROMPT
#endif
#define SCIPROMPT "--> "
#define SCIPROMPTDEBUG "debug> "
#define SCIPROMPTBREAK "break> "

#ifdef SCIPROMPT_PAUSE
#undef SCIPROMPT_PAUSE
#endif
#define SCIPROMPT_PAUSE ">> "

#ifdef SCIPROMPT_INTERRUPT
#undef SCIPROMPT_INTERRUPT
#endif
#define SCIPROMPT_INTERRUPT "-%d-> "

void setPreviousLevel(int pause);
const char* GetCurrentPrompt();
void SetTemporaryPrompt(const char* tempPrompt);
const char* GetTemporaryPrompt(void);
void ClearTemporaryPrompt(void);

#endif /* _PROMPT_H_ */
