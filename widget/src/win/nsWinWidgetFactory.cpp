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

// Force references to all of the symbols that we want exported from
// the dll that are located in the .lib files we link with
//
#include <stdio.h>

#include "nsIFactory.h"
#include "nsISupports.h"
#include "nscore.h"
#include "nsWidgetsCID.h"

#include "nsToolkit.h"
#include "nsWindow.h"
#include "nsAppShell.h"

static NS_DEFINE_IID(kCWindow,        NS_WINDOW_CID);
static NS_DEFINE_IID(kCAppShell,      NS_APPSHELL_CID);
static NS_DEFINE_IID(kCToolkit,       NS_TOOLKIT_CID);

static NS_DEFINE_IID(kISupportsIID,   NS_ISUPPORTS_IID);
static NS_DEFINE_IID(kIFactoryIID,    NS_IFACTORY_IID);


class nsWidgetFactory : public nsIFactory
{
public:
  // nsISupports methods
  NS_DECL_ISUPPORTS

  // nsIFactory methods
  NS_IMETHOD CreateInstance(nsISupports *aOuter,
             const nsIID &aIID,
             void **aResult);

  NS_IMETHOD LockFactory(PRBool aLock);

  nsWidgetFactory(const nsCID &aClass);
  virtual ~nsWidgetFactory();

private:
    nsCID mClassID;
};

NS_IMPL_ADDREF(nsWidgetFactory)
NS_IMPL_RELEASE(nsWidgetFactory)

nsWidgetFactory::nsWidgetFactory(const nsCID &aClass)
{
  NS_INIT_REFCNT();
  mClassID = aClass;
}

nsWidgetFactory::~nsWidgetFactory()
{
  NS_ASSERTION(mRefCnt == 0, "Reference count not zero in destructor");
}

nsresult nsWidgetFactory::QueryInterface(const nsIID &aIID,
                                         void **aResult)
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

nsresult nsWidgetFactory::CreateInstance( nsISupports* aOuter,
                                          const nsIID &aIID,
                                          void **aResult)
{
  if (aResult == NULL) {
    return NS_ERROR_NULL_POINTER;
  }
  *aResult = NULL;
  if (nsnull != aOuter) {
    return NS_ERROR_NO_AGGREGATION;
  }

  nsISupports *inst = nsnull;
  if (mClassID.Equals(kCWindow)) {
    inst = (nsISupports*)new nsWindow();
  }
#if 0
  else if (mClassID.Equals(kCChild)) {
    inst = (nsISupports*)new ChildWindow();
  }
  else if (mClassID.Equals(kCButton)) {
    inst = (nsISupports*)(nsWindow*)new nsButton();
  }
  else if (mClassID.Equals(kCCheckButton)) {
    inst = (nsISupports*)(nsWindow*)new nsCheckButton();
  }
  else if (mClassID.Equals(kCCombobox)) {
    inst = (nsISupports*)(nsWindow*)new nsComboBox();
  }
  else if (mClassID.Equals(kCRadioButton)) {
    inst = (nsISupports*)(nsWindow*)new nsRadioButton();
  }
  //else if (mClassID.Equals(kCRadioGroup)) {
  //    inst = (nsISupports*)(nsObject*)new nsRadioGroup();
  //}
  else if (mClassID.Equals(kCFileOpen)) {
    inst = (nsISupports*)new nsFileWidget();
  }
  else if (mClassID.Equals(kCListbox)) {
    inst = (nsISupports*)(nsWindow*)new nsListBox();
  }
  else if (mClassID.Equals(kCHorzScrollbar)) {
    inst = (nsISupports*)(nsWindow*)new nsScrollbar(PR_FALSE);
  }
  else if (mClassID.Equals(kCVertScrollbar)) {
    inst = (nsISupports*)(nsWindow*)new nsScrollbar(PR_TRUE);
  }
  else if (mClassID.Equals(kCTextArea)) {
    inst = (nsISupports*)(nsWindow*)new nsTextAreaWidget();
  }
  else if (mClassID.Equals(kCTextField)) {
    inst = (nsISupports*)(nsWindow*)new nsTextWidget();
  }
  else if (mClassID.Equals(kCTabWidget)) {
    inst = (nsISupports*)(nsWindow*)new nsTabWidget();
  }
  else if (mClassID.Equals(kCTooltipWidget)) {
    inst = (nsISupports*)(nsWindow*)new nsTooltipWidget();
  }
#endif
  else if (mClassID.Equals(kCAppShell)) {
    inst = (nsISupports*)new nsAppShell();
  }
  else if (mClassID.Equals(kCToolkit)) {
    inst = (nsISupports*)new nsToolkit();
  }
#if 0
  else if (mClassID.Equals(kCLookAndFeel)) {
    inst = (nsISupports*)new nsLookAndFeel();
  }
  else if (mClassID.Equals(kCDialog)) {
    inst = (nsISupports*)(nsWindow*)new nsDialog();
  }
  else if (mClassID.Equals(kCLabel)) {
    inst = (nsISupports*)(nsWindow*)new nsLabel();
  }
  else if (mClassID.Equals(kCMenuBar)) {
    inst = (nsISupports*)new nsMenuBar();
  }
  else if (mClassID.Equals(kCMenu)) {
    inst = (nsISupports*)new nsMenu();
  }
  else if (mClassID.Equals(kCMenuItem)) {
    inst = (nsISupports*)new nsMenuItem();
  }
  else if (mClassID.Equals(kCImageButton)) {
    inst = (nsISupports*)(nsWindow*)new nsImageButton();
  }
  else if (mClassID.Equals(kCMenuButton)) {
    inst = (nsISupports*)(nsWindow*)new nsMenuButton();
  }
  else if (mClassID.Equals(kCToolBar)) {
    inst = (nsISupports*)(nsWindow*)new nsToolbar();
  }
  else if (mClassID.Equals(kCToolBarManager)) {
    inst = (nsISupports*)(nsWindow*)new nsToolbarManager();
  }
  else if (mClassID.Equals(kCToolBarItemHolder)) {
    inst = (nsISupports*)(nsIToolbarItemHolder *) new nsToolbarItemHolder();
  }
  else if (mClassID.Equals(kCPopUpMenu)) {
    inst = (nsISupports*)new nsPopUpMenu();
  }
  else if (mClassID.Equals(kCTreeView)) {
    inst = (nsISupports*)(nsWindow*)new nsTreeView();
  }
  /* */
#endif

  if (inst == NULL) {
      return NS_ERROR_OUT_OF_MEMORY;
  }

  nsresult res = inst->QueryInterface(aIID, aResult);

  if (res != NS_OK) {
    // We didn't get the right interface, so clean up  
    delete inst;
  }

  return res;
}

nsresult nsWidgetFactory::LockFactory(PRBool aLock)  
{
  // Not implemented in simplest case.
  return NS_OK;
}

extern "C" NS_WIDGET nsresult NSGetFactory(const nsCID &aClass, nsISupports *servMgr, nsIFactory **aFactory)
{
  if (aFactory == nsnull) {
    return NS_ERROR_NULL_POINTER;
  }

  *aFactory = new nsWidgetFactory(aClass);
  if (aFactory == nsnull) {
    return NS_ERROR_OUT_OF_MEMORY;
  }
  return (*aFactory)->QueryInterface(kIFactoryIID, (void **)aFactory);
}
