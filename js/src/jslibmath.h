/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
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

/*
 * By default all math calls go to fdlibm.  The defines for each platform
 * remap the math calls to native routines.
 */

#ifndef _LIBMATH_H
#define _LIBMATH_H

#include <math.h>
#include "jsconfig.h"
#ifdef MOZILLA_CLIENT
#include "platform.h"
#endif

/*
 * Use system provided math routines.
 */

#define fd_acos acos
#define fd_asin asin
#define fd_atan atan
#define fd_atan2 atan2
#define fd_ceil ceil
#define fd_copysign copysign
#define fd_cos cos
#define fd_exp exp
#define fd_fabs fabs
#define fd_floor floor
#define fd_fmod fmod
#define fd_log log
#define fd_pow pow
#define fd_sin sin
#define fd_sqrt sqrt
#define fd_tan tan

#endif /* _LIBMATH_H */

