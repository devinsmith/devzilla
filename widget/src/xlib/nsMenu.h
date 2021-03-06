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

#ifndef nsMenu_h__
#define nsMenu_h__

#include "nsWidget.h"
#include "nsIMenu.h"
#include "nsISupportsArray.h"

class nsIMenuListener;

/**
 * Native Win32 button wrapper
 */

class nsMenu : public nsIMenu, public nsIMenuListener
{

public:
  nsMenu();
  virtual ~nsMenu();

  NS_DECL_ISUPPORTS
  
  // nsIMenuListener interface
  nsEventStatus MenuItemSelected(const nsMenuEvent & aMenuEvent);
  nsEventStatus MenuSelected(const nsMenuEvent & aMenuEvent);
  nsEventStatus MenuDeselected(const nsMenuEvent & aMenuEvent);
  nsEventStatus MenuConstruct(const nsMenuEvent & aMenuEvent,
                              nsIWidget         * aParentWindow, 
                              void              * menubarNode,
                              void              * aWebShell);
  nsEventStatus MenuDestruct(const nsMenuEvent & aMenuEvent);

  
  NS_IMETHOD Create(nsISupports * aParent, const nsString &aLabel);


  // nsIMenu Methods
  NS_IMETHOD GetParent(nsISupports *&aParent);
  NS_IMETHOD GetLabel(nsString &aText);
  NS_IMETHOD SetLabel(const nsString &aText);

  NS_IMETHOD AddItem(nsISupports * aItem);

  NS_IMETHOD AddSeparator();
  NS_IMETHOD GetItemCount(PRUint32 &aCount);
  NS_IMETHOD GetItemAt(const PRUint32 aPos, nsISupports *& aMenuItem);
  NS_IMETHOD InsertItemAt(const PRUint32 aPos, nsISupports * aMenuItem);
  NS_IMETHOD RemoveItem(const PRUint32 aPos);
  NS_IMETHOD RemoveAll();
  NS_IMETHOD GetNativeData(void** aData);

  NS_IMETHOD AddMenuListener(nsIMenuListener * aMenuListener);
  NS_IMETHOD RemoveMenuListener(nsIMenuListener * aMenuListener);

  //
  NS_IMETHOD AddMenuItem(nsIMenuItem * aMenuItem);
  NS_IMETHOD AddMenu(nsIMenu * aMenu);
  NS_IMETHOD InsertSeparator(const PRUint32 aCount);

#if 0
  NS_IMETHOD SetDOMNode(nsIDOMNode * menuNode);
  NS_IMETHOD SetDOMElement(nsIDOMElement * menuElement);
  NS_IMETHOD SetWebShell(nsIWebShell * aWebShell);
#endif

  // Native Impl Methods
  // These are not ref counted
  nsIMenu    * GetMenuParent()    { return mMenuParent;    } 
  nsIMenuBar * GetMenuBarParent() { return mMenuBarParent; }

protected:
  nsIMenuBar * GetMenuBar(nsIMenu * aMenu);
  nsIWidget *  GetParentWidget();

  nsString     mLabel;

  nsIMenuBar * mMenuBarParent;
  nsIMenu    * mMenuParent;

  nsISupportsArray * mItems;
  nsIMenuListener * mListener;

};

#endif // nsMenu_h__
