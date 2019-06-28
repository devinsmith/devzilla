/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is Netscape Communications
 * Corporation.  Portions created by Netscape are Copyright (C) 1998
 * Netscape Communications Corporation.  All Rights Reserved.
 */
#define NS_IMPL_IDS
#include "nsIPref.h"
#include "nsRepository.h"
#include "nsWidgetsCID.h"
#include "nsGfxCIID.h"
#include "nsIWebShell.h"
#include "nsIDocumentLoader.h"

#ifdef XP_PC

#define WIDGET_DLL "raptorwidget.dll"
#define GFXWIN_DLL "raptorgfxwin.dll"
#define WEB_DLL    "raptorweb.dll"
#define PREF_DLL   "xppref32.dll"

#else

#ifdef XP_MAC

#define WIDGET_DLL		"WIDGET_DLL"
#define GFXWIN_DLL		"GFXWIN_DLL"
#define WEB_DLL				"WEB_DLL"
#define PREF_DLL   "PREF_DLL"

#else

// XP_UNIX
#define WIDGET_DLL "libwidgetmotif.so"
#define GFXWIN_DLL "libgfxmotif.so"
#define WEB_DLL    "libraptorwebwidget.so"
#define PREF_DLL   "./libpref.so"
#endif // XP_MAC

#endif // XP_PC

static NS_DEFINE_IID(kCWindowCID, NS_WINDOW_CID);
static NS_DEFINE_IID(kCAppShellCID, NS_APPSHELL_CID);
static NS_DEFINE_IID(kCWindowIID, NS_WINDOW_CID);
static NS_DEFINE_IID(kCChildIID, NS_CHILD_CID);
static NS_DEFINE_IID(kCDeviceContextIID, NS_DEVICE_CONTEXT_CID);
static NS_DEFINE_IID(kWebShellCID, NS_WEB_SHELL_CID);
static NS_DEFINE_IID(kCDocumentLoaderCID, NS_DOCUMENTLOADER_CID);
static NS_DEFINE_IID(kCMenuBarCID, NS_MENUBAR_CID);
static NS_DEFINE_IID(kCMenuCID, NS_MENU_CID);
static NS_DEFINE_IID(kCMenuItemCID, NS_MENUITEM_CID);

extern "C" void
NS_SetupRegistry()
{
  nsRepository::RegisterFactory(kCWindowIID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCChildIID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCAppShellCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCDeviceContextIID, GFXWIN_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kWebShellCID, WEB_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCDocumentLoaderCID, WEB_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kPrefCID, PREF_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCMenuBarCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCMenuCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCMenuItemCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
}
