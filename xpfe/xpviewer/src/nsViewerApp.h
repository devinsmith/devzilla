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
#ifndef nsViewerApp_h___
#define nsViewerApp_h___

#include "nsIAppShell.h"
#include "nsString.h"
#include "nsCRT.h"
#include "nsVoidArray.h"

class nsIPref;
class nsIBrowserWindow;

class nsViewerApp
{
public:
  nsViewerApp();
  virtual ~nsViewerApp();

  // nsISupports
  NS_DECL_ISUPPORTS

  NS_IMETHOD SetupRegistry();
  NS_IMETHOD Initialize(int argc, char** argv);
  NS_IMETHOD OpenWindow(PRUint32 aNewChromeMask, nsIBrowserWindow*& aNewWindow);

  NS_IMETHOD Run();

protected:
  nsIAppShell* mAppShell;
  nsIPref* mPrefs;
  nsString mStartURL;
  PRBool mAllowPlugins;
  bool mIsInitialized;
};


#endif /* nsViewerApp_h___ */

