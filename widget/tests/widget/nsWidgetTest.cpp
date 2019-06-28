/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
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

#include <stdio.h>
#include <stdlib.h>

#include "nscore.h"
#include "nsError.h"

#include "nsIAppShell.h"
#include "nsRepository.h"
#include "nsWidgetsCID.h"

#ifdef XP_UNIX
#define WIDGET_DLL "libwidgetmotif.so"
#else
#define WIDGET_DLL "raptorwidget.dll"
#endif

const char *gLogFileName   = "selftest.txt";
FILE *gFD = nsnull;

// class ids
static NS_DEFINE_IID(kCAppShellCID, NS_APPSHELL_CID);

// interface ids
static NS_DEFINE_IID(kIAppShellIID,       NS_IAPPSHELL_IID);


nsresult WidgetTest(int * argc, char **argv)
{
  // Open global test log file
  gFD = fopen(gLogFileName, "w");
  if (gFD == nsnull) {
    fprintf(stderr, "Couldn't open file[%s]\n", gLogFileName);
    exit(1);
  }

  nsRepository::RegisterFactory(kCAppShellCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
	

  nsIAppShell *appShell;
  nsRepository::CreateInstance(kCAppShellCID, nsnull, kIAppShellIID, (void**)&appShell);
  if (appShell != nsnull) {
    fputs("Created AppShell\n", stderr);
  } else {
    printf("AppShell is null!\n");
  }

  return appShell->Run();
}

