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


#include "nsIAppShellService.h"
#include "nsISupportsArray.h"
#include "nsIComponentManager.h"
#include "nsIURL.h"
#include "nsIServiceManager.h"
#include "nsIEventQueueService.h"
#include "nsXPComCIID.h"
#include "nsXPComFactory.h"    /* template implementation of a XPCOM factory */

#include "nsIAppShell.h"
#include "nsIWidget.h"
#include "nsIWebShellWindow.h"
#include "nsWebShellWindow.h"

#include "nsWidgetsCID.h"

/* Define Class IDs */
static NS_DEFINE_IID(kAppShellCID,         NS_APPSHELL_CID);

/* Define Interface IDs */

static NS_DEFINE_IID(kIFactoryIID,         NS_IFACTORY_IID);
static NS_DEFINE_IID(kIAppShellServiceIID, NS_IAPPSHELL_SERVICE_IID);
static NS_DEFINE_IID(kIAppShellIID,          NS_IAPPSHELL_IID);
static NS_DEFINE_IID(kIWebShellWindowIID,    NS_IWEBSHELL_WINDOW_IID);


class nsAppShellService : public nsIAppShellService
{
public:
  nsAppShellService(void);

  NS_DECL_ISUPPORTS

  NS_IMETHOD Initialize(void);
  NS_IMETHOD Run(void);
  NS_IMETHOD Shutdown(void);
  NS_IMETHOD CreateTopLevelWindow(nsIWebShellWindow * aParent,
                                  nsIURL* aUrl, 
                                  nsString& aControllerIID,
                                  nsIWebShellWindow*& aResult, nsIStreamObserver* anObserver,
                                  nsIXULWindowCallbacks *aCallbacks,
                                  PRInt32 aInitialWidth, PRInt32 aInitialHeight);

  NS_IMETHOD CloseTopLevelWindow(nsIWebShellWindow* aWindow);
  NS_IMETHOD RegisterTopLevelWindow(nsIWebShellWindow* aWindow);
  NS_IMETHOD UnregisterTopLevelWindow(nsIWebShellWindow* aWindow);


protected:
  virtual ~nsAppShellService();

  nsIAppShell* mAppShell;
  nsISupportsArray* mWindowList;
};


nsAppShellService::nsAppShellService()
{
  NS_INIT_REFCNT();

  mAppShell     = nsnull;
  mWindowList   = nsnull;
}

nsAppShellService::~nsAppShellService()
{
  NS_IF_RELEASE(mAppShell);
  NS_IF_RELEASE(mWindowList);
}


/*
 * Implement the nsISupports methods...
 */
NS_IMPL_ISUPPORTS(nsAppShellService, kIAppShellServiceIID);


NS_IMETHODIMP
nsAppShellService::Initialize(void)
{
  nsresult rv;

  rv = NS_NewISupportsArray(&mWindowList);
  if (NS_FAILED(rv)) {
    goto done;
  }

  // Create widget application shell
  rv = nsComponentManager::CreateInstance(kAppShellCID, nsnull, kIAppShellIID,
                                    (void**)&mAppShell);
  if (NS_FAILED(rv)) {
    goto done;
  }

  rv = mAppShell->Create(0, nsnull);

done:
  return rv;
}


NS_IMETHODIMP
nsAppShellService::Run(void)
{
  return mAppShell->Run();
}

NS_IMETHODIMP
nsAppShellService::Shutdown(void)
{
  return NS_OK;
}

/*
 * Create a new top level window and display the given URL within it...
 *
 * @param aParent - parent for the window to be created (generally null;
 *                  included for compatibility with dialogs).
 *                  (currently unused).
 * @param aURL - location of XUL window contents description
 * @param aControllerIID - currently provided as an argument. in the future,
 *                         this will be specified by the XUL document itself.
 *                         (currently unused, but please specify the same
 *                         hardwired IID as others are using).
 * @param anObserver - a stream observer to give to the new window
 * @param aConstructionCallbacks - methods which will be called during
 *                                 window construction. can be null.
 * @param aInitialWidth - width of window, in pixels (currently unused)
 * @param aInitialHeight - height of window, in pixels (currently unused)
 */
NS_IMETHODIMP
nsAppShellService::CreateTopLevelWindow(nsIWebShellWindow *aParent,
                                        nsIURL* aUrl, nsString& aControllerIID,
                                        nsIWebShellWindow*& aResult, nsIStreamObserver* anObserver,
                                        nsIXULWindowCallbacks *aCallbacks,
                                        PRInt32 aInitialWidth, PRInt32 aInitialHeight)
{
  nsresult rv;
  nsWebShellWindow* window;

  window = new nsWebShellWindow();
  if (nsnull == window) {
    rv = NS_ERROR_OUT_OF_MEMORY;
  } else {
    // temporarily disabling parentage because non-Windows platforms
    // seem to be interpreting it in unexpected ways.
    rv = window->Initialize((nsIWebShellWindow *) nsnull, mAppShell, aUrl, aControllerIID,
                            anObserver, aCallbacks,
                            aInitialWidth, aInitialHeight);
    if (NS_SUCCEEDED(rv)) {
      rv = window->QueryInterface(kIWebShellWindowIID, (void **) &aResult);
      mWindowList->AppendElement((nsIWebShellContainer*)window);
      //aResult = window->GetWidget();
      window->Show(PR_TRUE);
    }
  }

  return rv;
}


NS_IMETHODIMP
nsAppShellService::CloseTopLevelWindow(nsIWebShellWindow* aWindow)
{
  return aWindow->Close();
}

/*
 * Register a new top level window (created elsewhere)
 */
static NS_DEFINE_IID(kIWebShellContainerIID,  NS_IWEB_SHELL_CONTAINER_IID);
NS_IMETHODIMP
nsAppShellService::RegisterTopLevelWindow(nsIWebShellWindow* aWindow)
{
  nsresult rv;

  nsIWebShellContainer* wsc;
  rv = aWindow->QueryInterface(kIWebShellContainerIID, (void **) &wsc);
  if (NS_SUCCEEDED(rv)) {
    mWindowList->AppendElement(wsc);
    NS_RELEASE(wsc);
  }
  return rv;
}


NS_IMETHODIMP
nsAppShellService::UnregisterTopLevelWindow(nsIWebShellWindow* aWindow)
{
  nsresult rv;

  nsIWebShellContainer* wsc;
  rv = aWindow->QueryInterface(kIWebShellContainerIID, (void **) &wsc);
  if (NS_SUCCEEDED(rv)) {
    mWindowList->RemoveElement(wsc);
    NS_RELEASE(wsc);
  }
  if (0 == mWindowList->Count())
    mAppShell->Exit();
  return rv;
}


NS_EXPORT nsresult NS_NewAppShellService(nsIAppShellService** aResult)
{
  if (nsnull == aResult) {
    return NS_ERROR_NULL_POINTER;
  }

  *aResult = new nsAppShellService();
  if (nsnull == *aResult) {
    return NS_ERROR_OUT_OF_MEMORY;
  }

  NS_ADDREF(*aResult);
  return NS_OK;
}

//----------------------------------------------------------------------

// Entry point to create nsAppShellService factory instances...
NS_DEF_FACTORY(AppShellService,nsAppShellService)

nsresult NS_NewAppShellServiceFactory(nsIFactory** aResult)
{
  nsresult rv = NS_OK;
  nsIFactory* inst = new nsAppShellServiceFactory;
  if (nsnull == inst) {
    rv = NS_ERROR_OUT_OF_MEMORY;
  }
  else {
    NS_ADDREF(inst);
  }
  *aResult = inst;
  return rv;
}
