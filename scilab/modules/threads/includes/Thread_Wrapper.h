/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - INRIA - Bruno JOFRET
 * Copyright (C) 2008-2008 - INRIA - Allan CORNET
 * Copyright (C) 2011-2011 - DIGITEO - Bruno JOFRET
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

/*
** Thread wrapper to have an easy way to manage
** those features on each platform
*/

#ifndef __THREAD_WRAPPER_H__
#define __THREAD_WRAPPER_H__

/*
** WINDOWS
*/
#ifdef _MSC_VER
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x500
#endif
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX

typedef DWORD                           __threadKey;
typedef HANDLE                          __threadId;
typedef HANDLE                          __threadLock;
typedef CRITICAL_SECTION                __threadSignalLock;
typedef HANDLE                          __threadSignal;
#define __StaticInitLock                NULL

#define __StaticInitThreadSignal        NULL

#else
/*
** LINUX & Mac
*/
#include <pthread.h>
#include <signal.h>
#include <stdlib.h> // malloc

typedef pthread_t                       __threadKey;
typedef pthread_t                       __threadId;
typedef pthread_mutex_t                 __threadLock;
typedef pthread_mutex_t                 __threadSignalLock;
typedef pthread_cond_t                  __threadSignal;
#define __StaticInitLock                PTHREAD_MUTEX_INITIALIZER

#define __StaticInitThreadSignal        PTHREAD_COND_INITIALIZER
#endif

void __InitLock(__threadLock *lockName);

void __Lock(__threadLock *lockName);

void __UnLock(__threadLock *lockName);

void __InitSignalLock(__threadSignalLock *lockName);

void __LockSignal(__threadSignalLock *lockName);

void __UnLockSignal(__threadSignalLock *lockName);

void __InitSignal(__threadSignal *signalName);

void __Signal(__threadSignal *signalName);

void __Wait(__threadSignal *signalName, __threadSignalLock *lockName);

void __CreateThread(__threadId *threadId, __threadKey *threadKey, void * (*functionName) (void *));

void __CreateThreadWithParams(__threadId *threadId, __threadKey *threadKey, void * (*functionName) (void *), void *params);

void __WaitThreadDie(__threadId threadId);

void __Terminate(__threadId threadId);

__threadId __GetCurrentThreadId();

__threadKey __GetCurrentThreadKey();

void __SuspendThread(__threadId ThreadId);

void __ResumeThread(__threadId ThreadId);

#endif /* !__THREAD_WRAPPER_H__ */

