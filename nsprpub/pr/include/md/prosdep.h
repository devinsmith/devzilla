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

#ifndef prosdep_h___
#define prosdep_h___

/*
** Get OS specific header information
*/
#include "prtypes.h"

PR_BEGIN_EXTERN_C

#ifdef XP_PC

#include "md/_pcos.h"
#ifdef WINNT
#include "md/_winnt.h"
#include "md/_win32_errors.h"
#elif defined(WIN95)
#include "md/_win95.h"
#include "md/_win32_errors.h"
#elif defined(WIN16)
#include "md/_win16.h"
#elif defined(OS2)
#include "md/_os2.h"
#include "md/_os2_errors.h"
#else
#error unknown Windows platform
#endif

#elif defined XP_MAC

#include "_macos.h"

#elif defined(XP_UNIX)

#include "md/_unixos.h"
#include "md/_unix_errors.h"
#include "md/_linux.h"
#include "md/_nspr_pthread.h"

#else

#error "The platform is not Unix, Windows, or Mac"

#endif

#ifdef _PR_PTHREADS
#include "md/_pth.h"
#endif

PR_END_EXTERN_C

#endif /* prosdep_h___ */
