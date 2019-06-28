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

#ifdef NGPREFS
#define INITGUID
#endif
#include "nsViewerApp.h"
#include "nsBrowserWindow.h"
#include "nsWidgetsCID.h"
#include "nsIAppShell.h"
#include "nsIPref.h"
#include "nsRepository.h"
#include "prprf.h"
#include "plstr.h"
#include "prenv.h"

#include "nsRect.h" // Where does this get included?

#define DIALOG_FONT      "Helvetica"
#define DIALOG_FONT_SIZE 10

extern nsresult NS_NewBrowserWindowFactory(nsIFactory** aFactory);
extern "C" void NS_SetupRegistry();

static NS_DEFINE_IID(kAppShellCID, NS_APPSHELL_CID);
static NS_DEFINE_IID(kBrowserWindowCID, NS_BROWSER_WINDOW_CID);

static NS_DEFINE_IID(kIAppShellIID, NS_IAPPSHELL_IID);
static NS_DEFINE_IID(kIBrowserWindowIID, NS_IBROWSER_WINDOW_IID);
static NS_DEFINE_IID(kISupportsIID, NS_ISUPPORTS_IID);



nsViewerApp::nsViewerApp()
{
  char * text = getenv("NGLAYOUT_HOME");

  mStartURL = text ? text : "http://developer.netscape.com/software/communicator/ngl/index.html";

  mAllowPlugins = PR_TRUE;
  mIsInitialized = false;

}

nsViewerApp::~nsViewerApp()
{
  if (mPrefs != nsnull) {
  }
}

NS_IMPL_THREADSAFE_ADDREF(nsViewerApp)
NS_IMPL_THREADSAFE_RELEASE(nsViewerApp)

nsresult
nsViewerApp::QueryInterface(REFNSIID aIID, void** aInstancePtrResult)
{
  NS_PRECONDITION(nsnull != aInstancePtrResult, "null pointer");
  if (nsnull == aInstancePtrResult) {
    return NS_ERROR_NULL_POINTER;
  }

  return NS_NOINTERFACE;
}

nsresult
nsViewerApp::SetupRegistry()
{
  NS_SetupRegistry();

  // Register our browser window factory
  nsIFactory* bwf;
  NS_NewBrowserWindowFactory(&bwf);
  nsRepository::RegisterFactory(kBrowserWindowCID, bwf, PR_FALSE);

  return NS_OK;
}

nsresult
nsViewerApp::Initialize(int argc, char** argv)
{
  nsresult rv;

  rv = SetupRegistry();
  if (rv != NS_OK) {
    return rv;
  }

  // Create widget application shell
  rv = nsRepository::CreateInstance(kAppShellCID, nsnull, kIAppShellIID,
      (void**)&mAppShell);

  if (rv != NS_OK) {
    return rv;
  }
  mAppShell->Create(&argc, argv);

  // Load preferences
  rv = nsRepository::CreateInstance(kPrefCID, NULL, kIPrefIID,
      (void **)&mPrefs);

  if (rv != NS_OK) {
    return rv;
  }
  mPrefs->Startup("prefs.js");

  mIsInitialized = true;

  // Open first window (used to be in main()).
  nsIBrowserWindow *newInterface = NULL;
  OpenWindow((PRUint32)~0, newInterface);
  if (newInterface) {
    nsBrowserWindow *newWindow = (nsBrowserWindow*)newInterface; // hack

    newWindow->Show();
  }

  return rv;
}

NS_IMETHODIMP
nsViewerApp::OpenWindow(PRUint32 aNewChromeMask, nsIBrowserWindow*& aNewWindow)
{
  // Create browser window
  nsBrowserWindow* bw = nsnull;
  nsresult rv = nsRepository::CreateInstance(kBrowserWindowCID, nsnull,
                                             kIBrowserWindowIID,
                                             (void**) &bw);
  bw->SetApp(this);
  bw->Init(mAppShell, mPrefs, nsRect(0, 0, 620, 400), aNewChromeMask, mAllowPlugins);

  aNewWindow = bw;

  return NS_OK;
}

nsresult
nsViewerApp::Run()
{
  return mAppShell->Run();
}
