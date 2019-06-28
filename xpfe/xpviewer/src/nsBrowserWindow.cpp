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
#ifdef XP_MAC
#include "nsBrowserWindow.h"
#define NS_IMPL_IDS
#else
#define NS_IMPL_IDS
#include "nsBrowserWindow.h"
#endif
#include "prmem.h"

#include "nsIAppShell.h"
#include "nsIWidget.h"
#include "nsRepository.h"
#include "nsIFactory.h"
#include "nsCRT.h"
#include "nsWidgetsCID.h"
#include "nsViewerApp.h"
#include "nsIMenuBar.h"

// Menus
#include "nsIMenu.h"
#include "nsIMenuItem.h"

#include "resources.h"

static NS_DEFINE_IID(kWebShellCID, NS_WEB_SHELL_CID);
static NS_DEFINE_IID(kWindowCID, NS_WINDOW_CID);
static NS_DEFINE_IID(kMenuBarCID, NS_MENUBAR_CID);
static NS_DEFINE_IID(kMenuCID, NS_MENU_CID);
static NS_DEFINE_IID(kMenuItemCID, NS_MENUITEM_CID);


static NS_DEFINE_IID(kIBrowserWindowIID, NS_IBROWSER_WINDOW_IID);
static NS_DEFINE_IID(kIFactoryIID, NS_IFACTORY_IID);
static NS_DEFINE_IID(kISupportsIID, NS_ISUPPORTS_IID);
static NS_DEFINE_IID(kIWebShellIID, NS_IWEB_SHELL_IID);
static NS_DEFINE_IID(kIWidgetIID, NS_IWIDGET_IID);
static NS_DEFINE_IID(kIMenuBarIID, NS_IMENUBAR_IID);
static NS_DEFINE_IID(kIMenuIID, NS_IMENU_IID);
static NS_DEFINE_IID(kIMenuItemIID, NS_IMENUITEM_IID);

//----------------------------------------------------------------------
nsVoidArray nsBrowserWindow::gBrowsers;

//----------------------------------------------------------------------
// Note: operator new zeros our memory
nsBrowserWindow::nsBrowserWindow()
{
  AddBrowser(this);
}

//---------------------------------------------------------------
nsBrowserWindow::~nsBrowserWindow()
{
}

NS_IMPL_ADDREF(nsBrowserWindow)
NS_IMPL_RELEASE(nsBrowserWindow)

//----------------------------------------------------------------------
nsresult
nsBrowserWindow::QueryInterface(const nsIID& aIID,
                void** aInstancePtrResult)
{
  NS_PRECONDITION(nsnull != aInstancePtrResult, "null pointer");
  if (nsnull == aInstancePtrResult) {
    return NS_ERROR_NULL_POINTER;
  }

  *aInstancePtrResult = NULL;

  if (aIID.Equals(kIBrowserWindowIID)) {
    *aInstancePtrResult = (void*) ((nsIBrowserWindow*)this);
    NS_ADDREF_THIS();
    return NS_OK;
  }
#if 0
  if (aIID.Equals(kIStreamObserverIID)) {
    *aInstancePtrResult = (void*) ((nsIStreamObserver*)this);
    NS_ADDREF_THIS();
    return NS_OK;
  }
  if (aIID.Equals(kIWebShellContainerIID)) {
    *aInstancePtrResult = (void*) ((nsIWebShellContainer*)this);
    NS_ADDREF_THIS();
    return NS_OK;
  }
  if (aIID.Equals(kINetSupportIID)) {
    *aInstancePtrResult = (void*) ((nsINetSupport*)this);
    NS_ADDREF_THIS();
    return NS_OK;
  }
#endif
  if (aIID.Equals(kISupportsIID)) {
    *aInstancePtrResult = (void*) ((nsISupports*)((nsIBrowserWindow*)this));
    NS_ADDREF_THIS();
    return NS_OK;
  }
  return NS_NOINTERFACE;
}

//---------------------------------------------------------------
static nsEventStatus PR_CALLBACK
HandleBrowserEvent(nsGUIEvent *aEvent)
{
  nsEventStatus result = nsEventStatus_eIgnore;
//  nsBrowserWindow* bw = nsBrowserWindow::FindBrowserFor(aEvent->widget, FIND_WINDOW);

  return result;
}


//----------------------------------------------------------------------
nsresult
nsBrowserWindow::Init(nsIAppShell* aAppShell,
            nsIPref* aPrefs,
            const nsRect& aBounds,
            PRUint32 aChromeMask,
            PRBool aAllowPlugins)
{
  mChromeMask = aChromeMask;
  mAppShell = aAppShell;
  mPrefs = aPrefs;
  mAllowPlugins = aAllowPlugins;

  // Create top level window
  nsresult rv = nsRepository::CreateInstance(kWindowCID, nsnull, kIWidgetIID,
                       (void**)&mWindow);
  if (NS_OK != rv) {
    return rv;
  }

  nsWidgetInitData initData;
  initData.mBorderStyle = eBorderStyle_dialog;

  nsRect r(0, 0, aBounds.width, aBounds.height);
  mWindow->Create((nsIWidget*)NULL, r, HandleBrowserEvent, nsnull, aAppShell, nsnull, &initData);
  mWindow->GetClientBounds(r);
  mWindow->SetBackgroundColor(NS_RGB(192,192,192));

  // Create web shell
  rv = nsRepository::CreateInstance(kWebShellCID, nsnull,
                                    kIWebShellIID,
                                    (void**)&mWebShell);
  if (NS_OK != rv) {
    return rv;
  }
  r.x = r.y = 0;
  rv = mWebShell->Init(mWindow->GetNativeData(NS_NATIVE_WIDGET),
                       r.x, r.y, r.width, r.height,
                       nsScrollPreference_kAuto,
                       aAllowPlugins, PR_TRUE);
  mWebShell->SetContainer((nsIWebShellContainer*) this);
  mWebShell->SetObserver((nsIStreamObserver*)this);
  mWebShell->SetPrefs(aPrefs);
  mWebShell->Show();

  if (NS_CHROME_MENU_BAR_ON & aChromeMask) {
    rv = CreateMenuBar(r.width);
    if (NS_OK != rv) {
      return rv;
    }
  }

  return NS_OK;
}

NS_IMETHODIMP
nsBrowserWindow::Show()
{
  NS_PRECONDITION(nsnull != mWindow, "null window");
  mWindow->Show(PR_TRUE);
  return NS_OK;
}

//---------------------------------------------------------
void
nsBrowserWindow::AddBrowser(nsBrowserWindow* aBrowser)
{
  gBrowsers.AppendElement(aBrowser);
  NS_ADDREF(aBrowser);
}

//---------------------------------------------------------
void
nsBrowserWindow::RemoveBrowser(nsBrowserWindow* aBrowser)
{
  nsViewerApp* app = aBrowser->mApp;
  gBrowsers.RemoveElement(aBrowser);
  NS_RELEASE(aBrowser);
}

//-----------------------------------------------------
//-- Menu Struct
//-----------------------------------------------------
typedef struct _menuBtns {
  const char *title;
  const char *mneu;
  long command;
} MenuBtns;


//-----------------------------------------------------
// XXX This will be moved to nsWidgetSupport
nsIMenu * CreateMenu(nsIMenu * aMenu, const nsString &  aName, char aMneu)
{
  nsIMenu * menu;
  nsresult rv = nsRepository::CreateInstance(kMenuCID,
                       nsnull,
                       kIMenuIID,
                       (void**)&menu);
  if (NS_OK == rv) {
  menu->Create(aMenu, aName);
  }

  return menu;
}

//-----------------------------------------------------
// XXX This will be moved to nsWidgetSupport
nsIMenu * CreateMenu(nsIMenuBar * aMenuBar, const nsString &  aName, char aMneu)
{
  nsIMenu * menu;
  nsresult rv = nsRepository::CreateInstance(kMenuCID,
                       nsnull,
                       kIMenuIID,
                       (void**)&menu);
  if (NS_OK == rv) {
  menu->Create(aMenuBar, aName);
  }

  return menu;
}

nsIMenuItem * CreateMenuItem(nsIMenu * aMenu, const nsString & aName, PRUint32 aCommand)
{
  nsIMenuItem *menuItem = nsnull;

  if (!aName.Equals("-")) {
    nsresult rv = nsRepository::CreateInstance(kMenuItemCID,
        nsnull,
        kIMenuItemIID,
        (void**)&menuItem);

    if (NS_OK == rv) {
      menuItem->Create(aMenu, aName, aCommand);
    }
  } else {
    aMenu->AddSeparator();
  }

  return menuItem;
}

void CreateBrowserMenus(nsIMenuBar * aMenuBar)
{
  nsIMenu * fileMenu = CreateMenu(aMenuBar,  "File", 'F');

  CreateMenuItem(fileMenu, "-", 0);
  CreateMenuItem(fileMenu, "Exit", VIEWER_EXIT);
}

nsresult
nsBrowserWindow::CreateMenuBar(PRInt32 aWidth)
{
  nsIMenuBar * menuBar;
  nsresult rv = nsRepository::CreateInstance(kMenuBarCID,
                       nsnull,
                       kIMenuBarIID,
                       (void**)&menuBar);

  if (nsnull != menuBar) {
    menuBar->Create(mWindow);
    CreateBrowserMenus(menuBar);
  }

  return NS_OK;
}



// Factory code for creating nsBrowserWindow's

class nsBrowserWindowFactory : public nsIFactory
{
public:
  nsBrowserWindowFactory();
  virtual ~nsBrowserWindowFactory();

  // nsISupports methods
  NS_IMETHOD QueryInterface(const nsIID &aIID, void **aResult);
  NS_IMETHOD_(nsrefcnt) AddRef(void);
  NS_IMETHOD_(nsrefcnt) Release(void);

  // nsIFactory methods
  NS_IMETHOD CreateInstance(nsISupports *aOuter,
              const nsIID &aIID,
              void **aResult);

  NS_IMETHOD LockFactory(PRBool aLock);

private:
  nsrefcnt  mRefCnt;
};

nsBrowserWindowFactory::nsBrowserWindowFactory()
{
  mRefCnt = 0;
}

nsBrowserWindowFactory::~nsBrowserWindowFactory()
{
  NS_ASSERTION(mRefCnt == 0, "non-zero refcnt at destruction");
}

nsresult
nsBrowserWindowFactory::QueryInterface(const nsIID &aIID, void **aResult)
{
  if (aResult == NULL) {
    return NS_ERROR_NULL_POINTER;
  }

  // Always NULL result, in case of failure
  *aResult = NULL;

  if (aIID.Equals(kISupportsIID)) {
    *aResult = (void *)(nsISupports*)this;
  } else if (aIID.Equals(kIFactoryIID)) {
    *aResult = (void *)(nsIFactory*)this;
  }

  if (*aResult == NULL) {
    return NS_NOINTERFACE;
  }

  NS_ADDREF_THIS(); // Increase reference count for caller
  return NS_OK;
}

nsrefcnt
nsBrowserWindowFactory::AddRef()
{
  return ++mRefCnt;
}

nsrefcnt
nsBrowserWindowFactory::Release()
{
  if (--mRefCnt == 0) {
  delete this;
  return 0; // Don't access mRefCnt after deleting!
  }
  return mRefCnt;
}

nsresult
nsBrowserWindowFactory::CreateInstance(nsISupports *aOuter,
                     const nsIID &aIID,
                     void **aResult)
{
  nsresult rv;
  nsBrowserWindow *inst;

  if (aResult == NULL) {
  return NS_ERROR_NULL_POINTER;
  }
  *aResult = NULL;
  if (nsnull != aOuter) {
  rv = NS_ERROR_NO_AGGREGATION;
  goto done;
  }

  NS_NEWXPCOM(inst, nsBrowserWindow);
  if (inst == NULL) {
  rv = NS_ERROR_OUT_OF_MEMORY;
  goto done;
  }

  NS_ADDREF(inst);
  rv = inst->QueryInterface(aIID, aResult);
  NS_RELEASE(inst);

done:
  return rv;
}

nsresult
nsBrowserWindowFactory::LockFactory(PRBool aLock)
{
  // Not implemented in simplest case.
  return NS_OK;
}

nsresult
NS_NewBrowserWindowFactory(nsIFactory** aFactory)
{
  nsresult rv = NS_OK;
  nsBrowserWindowFactory* inst;
  NS_NEWXPCOM(inst, nsBrowserWindowFactory);
  if (nsnull == inst) {
    rv = NS_ERROR_OUT_OF_MEMORY;
  }
  else {
    NS_ADDREF(inst);
  }
  *aFactory = inst;

  return rv;
}
