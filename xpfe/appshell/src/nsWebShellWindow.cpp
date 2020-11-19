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


#include "nsWebShellWindow.h"
#include "nsCOMPtr.h"

#include "nsIComponentManager.h"
#include "nsIServiceManager.h"
#include "nsIURL.h"

#include "nsGUIEvent.h"
#include "nsWidgetsCID.h"
#include "nsIWidget.h"
#include "nsIAppShell.h"

#include "nsIAppShellService.h"
#include "nsAppShellCIDs.h"

/* Define Class IDs */
static NS_DEFINE_IID(kWindowCID,           NS_WINDOW_CID);
static NS_DEFINE_IID(kWebShellCID,         NS_WEB_SHELL_CID);
static NS_DEFINE_IID(kAppShellServiceCID,  NS_APPSHELL_SERVICE_CID);

/* Define Interface IDs */
static NS_DEFINE_IID(kISupportsIID,           NS_ISUPPORTS_IID);
static NS_DEFINE_IID(kIWebShellWindowIID,     NS_IWEBSHELL_WINDOW_IID);
static NS_DEFINE_IID(kIWidgetIID,             NS_IWIDGET_IID);
static NS_DEFINE_IID(kIWebShellIID,           NS_IWEB_SHELL_IID);
static NS_DEFINE_IID(kIWebShellContainerIID,  NS_IWEB_SHELL_CONTAINER_IID);

static NS_DEFINE_IID(kIAppShellServiceIID,    NS_IAPPSHELL_SERVICE_IID);


#include "nsIWebShell.h"


nsWebShellWindow::nsWebShellWindow()
{
  NS_INIT_REFCNT();

  mWebShell = nsnull;
  mWindow   = nsnull;
  mContinueModalLoop = PR_FALSE;
}


nsWebShellWindow::~nsWebShellWindow()
{
  if (nsnull != mWebShell) {
    mWebShell->Destroy();
    NS_RELEASE(mWebShell);
  }

  NS_IF_RELEASE(mWindow);
}


NS_IMPL_ADDREF(nsWebShellWindow);
NS_IMPL_RELEASE(nsWebShellWindow);

nsresult
nsWebShellWindow::QueryInterface(REFNSIID aIID, void** aInstancePtr)
{
  nsresult rv = NS_NOINTERFACE;

  if (NULL == aInstancePtr) {
    return NS_ERROR_NULL_POINTER;
  }
  if ( aIID.Equals(kIWebShellWindowIID) ) {
    *aInstancePtr = (void*) ((nsIWebShellWindow*)this);
    NS_ADDREF_THIS();  
    return NS_OK;
  }
  if (aIID.Equals(kIWebShellContainerIID)) {
    *aInstancePtr = (void*)(nsIWebShellContainer*)this;
    NS_ADDREF_THIS();
    return NS_OK;
  }
/*
  if (aIID.Equals(kIDocumentLoaderObserverIID)) {
    *aInstancePtr = (void*) ((nsIDocumentLoaderObserver*)this);
    NS_ADDREF_THIS();
    return NS_OK;
  }
	if ( aIID.Equals(kIBrowserWindowIID) ) {
    *aInstancePtr = (void*) (nsIBrowserWindow*) this;
    NS_ADDREF_THIS();
    return NS_OK;
  }
*/
  if (aIID.Equals(kISupportsIID)) {
    *aInstancePtr = (void*)(nsISupports*)(nsIWebShellContainer*)this;
    NS_ADDREF_THIS();
    return NS_OK;
  }
  return rv;
}


nsresult nsWebShellWindow::Initialize(nsIWebShellWindow* aParent,
                                      nsIAppShell* aShell, nsIURL* aUrl, 
                                      nsString& aControllerIID, nsIStreamObserver* anObserver,
                                      nsIXULWindowCallbacks *aCallbacks,
                                      PRInt32 aInitialWidth, PRInt32 aInitialHeight)
{
  nsresult rv;

  nsString urlString;
  nsIWidget *parentWidget;
  const char *tmpStr = NULL;
  nsIID iid;
  char str[40];

  aUrl->GetSpec(&tmpStr);
  urlString = tmpStr;

  // XXX: need to get the default window size from prefs...
  nsRect r(0, 0, aInitialWidth, aInitialHeight);
  
  nsWidgetInitData initData;


  if (nsnull == aUrl) {
    rv = NS_ERROR_NULL_POINTER;
    return rv;
  }

  // Create top level window
  rv = nsComponentManager::CreateInstance(kWindowCID, nsnull, kIWidgetIID,
                                    (void**)&mWindow);
  if (NS_OK != rv) {
    return rv;
  }

  initData.mBorderStyle = eBorderStyle_window;

  if (!aParent || NS_FAILED(aParent->GetWidget(parentWidget)))
    parentWidget = nsnull;

  mWindow->SetClientData(this);
  mWindow->Create(parentWidget,                       // Parent nsIWidget
                  r,                                  // Widget dimensions
                  nsWebShellWindow::HandleEvent,      // Event handler function
                  nsnull,                             // Device context
                  aShell,                             // Application shell
                  nsnull,                             // nsIToolkit
                  &initData);                         // Widget initialization data
  mWindow->GetClientBounds(r);
  mWindow->SetBackgroundColor(NS_RGB(192,192,192));

  // Create web shell
  rv = nsComponentManager::CreateInstance(kWebShellCID, nsnull,
                                    kIWebShellIID,
                                    (void**)&mWebShell);
  if (NS_OK != rv) {
    return rv;
  }

  r.x = r.y = 0;
  rv = mWebShell->Init(mWindow->GetNativeData(NS_NATIVE_WIDGET), 
                       r.x, r.y, r.width, r.height,
                       nsScrollPreference_kNeverScroll, 
                       PR_TRUE,                     // Allow Plugins 
                       PR_TRUE);
  mWebShell->SetContainer(this);
  //mWebShell->SetObserver((nsIStreamObserver*)this);
///  webShell->SetPrefs(aPrefs);

  mWebShell->LoadURL(urlString);
  mWebShell->Show();

  mWindow->Show(PR_TRUE);

  return rv;
}


/*
 * Close the window
 */
NS_METHOD
nsWebShellWindow::Close()
{
  ExitModalLoop();
  if ( mWebShell ) {
    mWebShell->Destroy();
    NS_IF_RELEASE(mWebShell);
  }

  NS_IF_RELEASE(mWindow);
  nsIAppShellService* appShell;
  nsresult rv = nsServiceManager::GetService(kAppShellServiceCID,
                                  kIAppShellServiceIID,
                                  (nsISupports**)&appShell);
  if (NS_FAILED(rv))
    return rv;
  
  rv = appShell->UnregisterTopLevelWindow(this);
  nsServiceManager::ReleaseService(kAppShellServiceCID, appShell);
  return rv;
}


/*
 * Event handler function...
 *
 * This function is called to process events for the nsIWidget of the 
 * nsWebShellWindow...
 */
nsEventStatus PR_CALLBACK
nsWebShellWindow::HandleEvent(nsGUIEvent *aEvent)
{
  nsEventStatus result = nsEventStatus_eIgnore;
  nsIWebShell* webShell = nsnull;

  // Get the WebShell instance...
  if (nsnull != aEvent->widget) {
    void* data;

    aEvent->widget->GetClientData(data);
    if (nsnull != data) {
      webShell = ((nsWebShellWindow*)data)->mWebShell;
    }
  }

  if (nsnull != webShell) {
    switch(aEvent->message) {
      /*
       * For size events, the WebShell must be resized to fill the entire
       * client area of the window...
       */
      case NS_SIZE: {
        nsSizeEvent* sizeEvent = (nsSizeEvent*)aEvent;  
        webShell->SetBounds(0, 0, sizeEvent->windowSize->width, sizeEvent->windowSize->height);
        result = nsEventStatus_eConsumeNoDefault;
        break;
      }
      /*
       * Notify the ApplicationShellService that the window is being closed...
       */
      case NS_DESTROY:
        break;
    }
  }
  return nsEventStatus_eIgnore;
}

NS_IMETHODIMP
nsWebShellWindow::WillLoadURL(nsIWebShell* aShell, const PRUnichar* aURL,
                              nsLoadType aReason)
{
  return NS_OK;
}

NS_IMETHODIMP 
nsWebShellWindow::BeginLoadURL(nsIWebShell* aShell, const PRUnichar* aURL)
{
  return NS_OK;
}

NS_IMETHODIMP 
nsWebShellWindow::ProgressLoadURL(nsIWebShell* aShell, const PRUnichar* aURL,
                                  PRInt32 aProgress, PRInt32 aProgressMax)
{
  return NS_OK;
}

NS_IMETHODIMP 
nsWebShellWindow::EndLoadURL(nsIWebShell* aShell, const PRUnichar* aURL,
                             PRInt32 aStatus)
{
  return NS_OK;
}

NS_IMETHODIMP 
nsWebShellWindow::NewWebShell(PRUint32 aChromeMask, PRBool aVisible,
                              nsIWebShell *&aNewWebShell)
{
  return NS_ERROR_FAILURE;
}


NS_IMETHODIMP nsWebShellWindow::FindWebShellWithName(const PRUnichar* aName,
                                                     nsIWebShell*& aResult)
{
  aResult = nsnull;
  return NS_OK;
}

NS_IMETHODIMP 
nsWebShellWindow::FocusAvailable(nsIWebShell* aFocusedWebShell)
{
  return NS_OK;
}

//----------------------------------------
// nsIWebShellWindow methods...
//----------------------------------------
NS_IMETHODIMP
nsWebShellWindow::Show(PRBool aShow)
{
  mWebShell->Show(); // crimminy -- it doesn't take a parameter!
  mWindow->Show(aShow);
  return NS_OK;
}

