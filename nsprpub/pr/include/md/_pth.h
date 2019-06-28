/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 * 
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 * 
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

#ifndef nspr_pth_defs_h_
#define nspr_pth_defs_h_

/*
** Appropriate definitions of entry points not used in a pthreads world
*/
#define _PR_MD_BLOCK_CLOCK_INTERRUPTS()
#define _PR_MD_UNBLOCK_CLOCK_INTERRUPTS()
#define _PR_MD_DISABLE_CLOCK_INTERRUPTS()
#define _PR_MD_ENABLE_CLOCK_INTERRUPTS()

/* In good standards fashion, the DCE threads (based on posix-4) are not
 * quite the same as newer posix implementations.  These are mostly name
 * changes and small differences, so macros usually do the trick
 */
#ifdef _PR_DCETHREADS
#define PTHREAD_MUTEXATTR_INIT        pthread_mutexattr_create
#define PTHREAD_MUTEXATTR_DESTROY     pthread_mutexattr_delete
#define PTHREAD_MUTEX_INIT(m, a)      pthread_mutex_init(&(m), a)
#define PTHREAD_MUTEX_IS_LOCKED(m)    (0 == pthread_mutex_trylock(&(m)))
#define PTHREAD_CONDATTR_INIT         pthread_condattr_create
#define PTHREAD_COND_INIT(m, a)       pthread_cond_init(&(m), a)
#define PTHREAD_CONDATTR_DESTROY      pthread_condattr_delete

/* Notes about differences between DCE threads and pthreads 10:
 *   1. pthread_mutex_trylock returns 1 when it locks the mutex
 *      0 when it does not.  The latest pthreads has a set of errno-like
 *      return values.
 *   2. return values from pthread_cond_timedwait are different.
 *
 *
 *
 */
#else
#define PTHREAD_MUTEXATTR_INIT        pthread_mutexattr_init
#define PTHREAD_MUTEXATTR_DESTROY     pthread_mutexattr_destroy
#define PTHREAD_MUTEX_INIT(m, a)      pthread_mutex_init(&(m), &(a))
#define PTHREAD_MUTEX_IS_LOCKED(m)    (EBUSY == pthread_mutex_trylock(&(m)))
#define PTHREAD_CONDATTR_INIT         pthread_condattr_init
#define PTHREAD_CONDATTR_DESTROY      pthread_condattr_destroy
#define PTHREAD_COND_INIT(m, a)       pthread_cond_init(&(m), &(a))
#endif

/* The pthread_t handle used to identify a thread can vary in size
 * with different implementations of pthreads.  This macro defines
 * a way to get a unique identifier from the handle.  This may be
 * more of a problem as we adapt to more pthreads implementations.
 */
#define PTHREAD_ZERO_THR_HANDLE(t)        (t) = 0
#define PTHREAD_THR_HANDLE_IS_ZERO(t)     (t) == 0
#define PTHREAD_COPY_THR_HANDLE(st, dt)   (dt) = (st)

#if defined(_PR_DCETHREADS)
#define PTHREAD_ATTR_INIT            pthread_attr_create
#define PTHREAD_ATTR_DESTROY         pthread_attr_delete
#define PTHREAD_CREATE(t, a, f, r)   pthread_create(t, a, f, r) 
#define PTHREAD_KEY_CREATE           pthread_keycreate
#define PTHREAD_ATTR_SETSCHEDPOLICY  pthread_attr_setsched
#define PTHREAD_ATTR_GETSTACKSIZE(a, s) \
                                     (*(s) = pthread_attr_getstacksize(*(a)), 0)
#define PTHREAD_GETSPECIFIC(k, r) \
		pthread_getspecific((k), (pthread_addr_t *) &(r))
#elif defined(_PR_PTHREADS)
#define PTHREAD_ATTR_INIT            pthread_attr_init
#define PTHREAD_ATTR_DESTROY         pthread_attr_destroy
#define PTHREAD_CREATE(t, a, f, r)   pthread_create(t, &a, f, r) 
#define PTHREAD_KEY_CREATE           pthread_key_create
#define PTHREAD_ATTR_SETSCHEDPOLICY  pthread_attr_setschedpolicy
#define PTHREAD_ATTR_GETSTACKSIZE(a, s) pthread_attr_getstacksize(a, s)
#define PTHREAD_GETSPECIFIC(k, r)    (r) = pthread_getspecific(k)
#else
#error "Cannot determine pthread strategy"
#endif

/*
 * See if we have the privilege to set the scheduling policy and
 * priority of threads.  Returns 0 if privilege is available.
 * Returns EPERM otherwise.
 */

#ifdef AIX
#define PT_PRIVCHECK()    privcheck(SET_PROC_RAC)
#elif defined(HPUX) && !defined(_PR_DCETHREADS)
PR_EXTERN(PRIntn) pt_hpux_privcheck(void);
#define PT_PRIVCHECK()    pt_hpux_privcheck()
#else
#define PT_PRIVCHECK()    0
#endif  /* AIX */

#if defined(_PR_DCETHREADS)
#define PTHREAD_EXPLICIT_SCHED      PTHREAD_DEFAULT_SCHED
#endif

/*
 * pthread_mutex_trylock returns different values in DCE threads and
 * pthreads.
 */
#if defined(_PR_DCETHREADS)
#define PT_TRYLOCK_SUCCESS 1
#define PT_TRYLOCK_BUSY    0
#else
#define PT_TRYLOCK_SUCCESS 0
#define PT_TRYLOCK_BUSY    EBUSY
#endif

/*
 * These platforms don't have pthread_atfork()
 */
#if defined(_PR_DCETHREADS) || defined(FREEBSD) \
	|| (defined(LINUX) && defined(__alpha)) \
	|| defined(NETBSD) || defined(OPENBSD)
#define PT_NO_ATFORK
#endif

/*
 * These platforms don't have sigtimedwait()
 */
#if (defined(AIX) && !defined(AIX4_3)) || defined(LINUX) \
	|| defined(FREEBSD) || defined(NETBSD) || defined(OPENBSD)
#define PT_NO_SIGTIMEDWAIT
#endif

#define PT_PRIO_MIN            sched_get_priority_min(SCHED_OTHER)
#define PT_PRIO_MAX            sched_get_priority_max(SCHED_OTHER)

/* Needed for garbage collection -- Look at PR_Suspend/PR_Resume implementation */
#define PTHREAD_YIELD()                 pthread_yield()

/*
** And when you really wanted hardcore locking w/o any fluff ...
**
**          ... and why would you want that????
*/
#define _PR_LOCK_LOCK(_lock)      pthread_mutex_lock(&_lock->mutex);
#define _PR_LOCK_UNLOCK(_lock)    pthread_mutex_unlock(&_lock->mutex);

#define _MD_INIT_LOCKS()

#endif /* nspr_pth_defs_h_ */
