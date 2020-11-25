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

#include "nsIComponentManager.h"
#include "nsIServiceManager.h"
#include "nsIURL.h"
#include "nsVoidArray.h"

#include "nsGUIEvent.h"
#include "nsWidgetsCID.h"
#include "nsIWidget.h"
#include "nsIAppShell.h"
#include "nsIXULWindowCallbacks.h"

#include "nsIAppShellService.h"
#include "nsIWidgetController.h"
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
static NS_DEFINE_IID(kIDocumentLoaderObserverIID, NS_IDOCUMENT_LOADER_OBSERVER_IID);

#include "nsIWebShell.h"


nsWebShellWindow::nsWebShellWindow()
{
  NS_INIT_REFCNT();

  mWebShell = nsnull;
  mWindow   = nsnull;
  mContinueModalLoop = PR_FALSE;
  mChromeInitialized = PR_FALSE;
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
  if (aIID.Equals(kIDocumentLoaderObserverIID)) {
    *aInstancePtr = (void*) ((nsIDocumentLoaderObserver*)this);
    NS_ADDREF_THIS();
    return NS_OK;
  }
/*
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


  // XXX: need to get the default window size from prefs...
  nsRect r(0, 0, aInitialWidth, aInitialHeight);
  
  nsWidgetInitData initData;


  //if (nsnull == aUrl) {
  //  rv = NS_ERROR_NULL_POINTER;
  //  goto done;
  //}
  if (nsnull != aUrl)  {
    aUrl->GetSpec(&tmpStr);
    urlString = tmpStr;
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
  mWebShell->SetObserver((nsIStreamObserver*)anObserver);
  mWebShell->SetDocLoaderObserver(this);

	// The outermost web shell is always considered to be chrome.
	mWebShell->SetWebShellType(nsWebShellChrome);

  if (nsnull != aUrl)  {
    mWebShell->LoadURL(urlString.GetUnicode());
  }


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
      case NS_DESTROY: {
        void* data;
        aEvent->widget->GetClientData(data);
        if (data)
           ((nsWebShellWindow *)data)->Close();
        break;
      }
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
nsWebShellWindow::EndLoadURL(nsIWebShell* aWebShell, const PRUnichar* aURL,
                             PRInt32 aStatus)
{
  return NS_OK;
}


NS_IMETHODIMP 
nsWebShellWindow::NewWebShell(PRUint32 aChromeMask, PRBool aVisible,
                              nsIWebShell *&aNewWebShell)
{
	// Don't return a web shell, since the shell that will hold our content
  // hasn't been instantiated yet.  We'll have to wait and set up the linkage
  // at a later date.
	aNewWebShell = nsnull;
  return NS_OK;
}


NS_IMETHODIMP nsWebShellWindow::FindWebShellWithName(const PRUnichar* aName,
                                                     nsIWebShell*& aResult)
{
  aResult = nsnull;
  return NS_OK;
}

NS_IMETHODIMP 
nsWebShellWindow::FocusAvailable(nsIWebShell* aFocusedWebShell, PRBool& aFocusTaken)
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


NS_IMETHODIMP 
nsWebShellWindow::GetWidget(nsIWidget *& aWidget)
{
  aWidget = mWindow;
  NS_ADDREF(mWindow);
  return NS_OK;
}

//----------------------------------------
// nsIDocumentLoaderObserver implementation
//----------------------------------------
NS_IMETHODIMP
nsWebShellWindow::OnStartDocumentLoad(nsIDocumentLoader* loader, 
                                      nsIURL* aURL, const char* aCommand)
{
  return NS_OK;
}

NS_IMETHODIMP
nsWebShellWindow::OnEndDocumentLoad(nsIDocumentLoader* loader, 
                                    nsIURL* aURL, PRInt32 aStatus)
{
#if 1
  printf("nsWebShellWindow::OnEndDocumentLoad TODO\n");
#endif

  /* We get notified every time a page/Frame is loaded. But we need to
   * Load the menus, run the startup script etc.. only once. So, Use
   * the mChrome Initialized  member to check whether chrome should be 
   * initialized or not - Radha
   */
  if (mChromeInitialized)
    return NS_OK;

  mChromeInitialized = PR_TRUE;
#if 0
  // register as document listener
  // this is needed for menus
  nsCOMPtr<nsIContentViewer> cv;
  mWebShell->GetContentViewer(getter_AddRefs(cv));
  if (cv) {
   
    nsCOMPtr<nsIDocumentViewer> docv(do_QueryInterface(cv));
    if (!docv)
      return NS_OK;

    nsCOMPtr<nsIDocument> doc;
    docv->GetDocument(*getter_AddRefs(doc));
    if (!doc)
      return NS_OK;

    doc->AddObserver(NS_STATIC_CAST(nsIDocumentObserver*, this));
  }

  ExecuteStartupCode();

  ///////////////////////////////
  // Find the Menubar DOM  and Load the menus, hooking them up to the loaded commands
  ///////////////////////////////
  nsCOMPtr<nsIDOMDocument> menubarDOMDoc(GetNamedDOMDoc(nsAutoString("this"))); // XXX "this" is a small kludge for code reused
  if (menubarDOMDoc)
  {
    #ifdef XP_MAC
    LoadMenus(menubarDOMDoc, mWindow);
    #else
    DynamicLoadMenus(menubarDOMDoc, mWindow);
    #endif
  }

  SetSizeFromXUL();
  SetTitleFromXUL();

#if 0
  nsCOMPtr<nsIDOMDocument> toolbarDOMDoc(GetNamedDOMDoc(nsAutoString("browser.toolbar")));
  nsCOMPtr<nsIDOMDocument> contentDOMDoc(GetNamedDOMDoc(nsAutoString("browser.webwindow")));
  nsCOMPtr<nsIDocument> contentDoc(do_QueryInterface(contentDOMDoc));
  nsCOMPtr<nsIDocument> statusDoc(do_QueryInterface(statusDOMDoc));
  nsCOMPtr<nsIDocument> toolbarDoc(do_QueryInterface(toolbarDOMDoc));

  nsIWebShell* statusWebShell = nsnull;
  mWebShell->FindChildWithName(nsAutoString("browser.status"), statusWebShell);

  PRInt32 actualStatusHeight  = GetDocHeight(statusDoc);
  PRInt32 actualToolbarHeight = GetDocHeight(toolbarDoc);


  PRInt32 height = 0;
  PRInt32 x,y,w,h;
  PRInt32 contentHeight;
  PRInt32 toolbarHeight;
  PRInt32 statusHeight;

  mWebShell->GetBounds(x, y, w, h);
  toolbarWebShell->GetBounds(x, y, w, toolbarHeight);
  contentWebShell->GetBounds(x, y, w, contentHeight);
  statusWebShell->GetBounds(x, y, w, statusHeight); 

  //h = toolbarHeight + contentHeight + statusHeight;
  contentHeight = h - actualStatusHeight - actualToolbarHeight;

  toolbarWebShell->GetBounds(x, y, w, h);
  toolbarWebShell->SetBounds(x, y, w, actualToolbarHeight);

  contentWebShell->GetBounds(x, y, w, h);
  contentWebShell->SetBounds(x, y, w, contentHeight);

  statusWebShell->GetBounds(x, y, w, h);
  statusWebShell->SetBounds(x, y, w, actualStatusHeight);
#endif
#endif
  return NS_OK;
}

NS_IMETHODIMP 
nsWebShellWindow::OnStartURLLoad(nsIDocumentLoader* loader, 
                                 nsIURL* aURL, 
                                 const char* aContentType, 
                                 nsIContentViewer* aViewer)
{
  return NS_OK;
}

NS_IMETHODIMP
nsWebShellWindow::OnProgressURLLoad(nsIDocumentLoader* loader, 
                                    nsIURL* aURL, 
                                    PRUint32 aProgress, 
                                    PRUint32 aProgressMax)
{
  return NS_OK;
}

NS_IMETHODIMP
nsWebShellWindow::OnStatusURLLoad(nsIDocumentLoader* loader, 
                                  nsIURL* aURL, nsString& aMsg)
{
  return NS_OK;
}

NS_IMETHODIMP
nsWebShellWindow::OnEndURLLoad(nsIDocumentLoader* loader, 
                               nsIURL* aURL, PRInt32 aStatus)
{
  return NS_OK;
}

NS_IMETHODIMP
nsWebShellWindow::HandleUnknownContentType(nsIDocumentLoader* loader, 
                                           nsIURL* aURL,
                                           const char *aContentType,
                                           const char *aCommand )
{
  return NS_OK;
}



