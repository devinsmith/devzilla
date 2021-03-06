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

#include "nsButton.h"

NS_IMPL_ADDREF(nsButton)
NS_IMPL_RELEASE(nsButton)

nsButton::nsButton() : nsWidget() , nsIButton()
{
  NS_INIT_REFCNT();
}

nsButton::~nsButton()
{
}

nsresult nsButton::QueryInterface(const nsIID& aIID, void** aInstancePtr)
{
  if (NULL == aInstancePtr) {
    return NS_ERROR_NULL_POINTER;
  }
  
  static NS_DEFINE_IID(kIButton, NS_IBUTTON_IID);
  if (aIID.Equals(kIButton)) {
    *aInstancePtr = (void*) ((nsIButton*)this);
    NS_ADDREF_THIS();
    return NS_OK;
  }
  
  return nsWidget::QueryInterface(aIID,aInstancePtr);
}

NS_METHOD nsButton::SetLabel (const nsString &aText)
{
  return NS_OK;
}

NS_METHOD nsButton::GetLabel (nsString &aBuffer)
{
  return NS_OK;
}

PRBool nsButton::OnMove(PRInt32, PRInt32)
{
  return PR_FALSE;
}

PRBool nsButton::OnPaint()
{
  return PR_FALSE;
}

PRBool nsButton::OnResize(nsRect &aWindowRect)
{
    return PR_FALSE;
}

NS_METHOD nsButton::Paint(nsIRenderingContext& aRenderingContext,
                          const nsRect& aDirtyRect)
{
  return NS_OK;
}
