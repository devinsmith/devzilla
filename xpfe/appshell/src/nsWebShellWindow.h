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

#ifndef nsWebShellWindow_h__
#define nsWebShellWindow_h__

#include "nsISupports.h"
#include "nsIWebShellWindow.h"
#include "nsIBrowserWindow.h"
#include "nsGUIEvent.h"
#include "nsIWebShell.h"  
#include "nsIDocumentLoaderObserver.h"
#include "nsIDocumentObserver.h"
#include "nsVoidArray.h"
#include "nsIMenu.h"

// can't use forward class decl's because of template bugs on Solaris 
#include "nsIDOMDocument.h"
#include "nsIDOMNode.h"

#include "nsCOMPtr.h"

/* Forward declarations.... */
struct PLEvent;

class nsIURL;
class nsIAppShell;
class nsIContent;
class nsIDocument;
class nsIDOMCharacterData;
class nsIDOMElement;
class nsIDOMWindow;
class nsIDOMHTMLImageElement;
class nsIDOMHTMLInputElement;
class nsIStreamObserver;
class nsIWidget;
class nsIWidgetController;
class nsIXULWindowCallbacks;
class nsVoidArray;

class nsWebShellWindow : public nsIWebShellWindow,
                         public nsIWebShellContainer,
			 public nsIBrowserWindow,
                         public nsIDocumentLoaderObserver,
                         public nsIDocumentObserver
{
public:
  nsWebShellWindow();

  // nsISupports interface...
  NS_DECL_ISUPPORTS


  // nsIWebShellContainer interface...
  NS_IMETHOD WillLoadURL(nsIWebShell* aShell,
                         const PRUnichar* aURL,
                         nsLoadType aReason);

  NS_IMETHOD BeginLoadURL(nsIWebShell* aShell,
                          const PRUnichar* aURL);

  NS_IMETHOD ProgressLoadURL(nsIWebShell* aShell,
                             const PRUnichar* aURL,
                             PRInt32 aProgress,
                             PRInt32 aProgressMax);

  NS_IMETHOD EndLoadURL(nsIWebShell* aShell,
                        const PRUnichar* aURL,
                        PRInt32 aStatus);

  NS_IMETHOD NewWebShell(PRUint32 aChromeMask,
                         PRBool aVisible,
                         nsIWebShell *&aNewWebShell);

  NS_IMETHOD FindWebShellWithName(const PRUnichar* aName,
                                  nsIWebShell*& aResult);

  NS_IMETHOD FocusAvailable(nsIWebShell* aFocusedWebShell, PRBool& aFocusTaken);


  // nsIWebShellWindow methods...
  NS_IMETHOD Show(PRBool aShow);
  NS_IMETHOD Close();
  NS_IMETHOD GetWidget(nsIWidget *& aWidget);

  // nsWebShellWindow methods...
  nsresult Initialize(nsIWebShellWindow * aParent, nsIAppShell* aShell, nsIURL* aUrl,
                      nsString& aControllerIID, nsIStreamObserver* anObserver,
                      nsIXULWindowCallbacks *aCallbacks,
                      PRInt32 aInitialWidth, PRInt32 aInitialHeight);
  nsIWidget* GetWidget(void) { return mWindow; }

  // nsIDocumentLoaderObserver
  NS_IMETHOD OnStartDocumentLoad(nsIDocumentLoader* loader, 
                                 nsIURL* aURL, const char* aCommand);
  NS_IMETHOD OnEndDocumentLoad(nsIDocumentLoader* loader, 
                               nsIURL *aUrl, PRInt32 aStatus);
  NS_IMETHOD OnStartURLLoad(nsIDocumentLoader* loader, 
                            nsIURL* aURL, const char* aContentType, 
                            nsIContentViewer* aViewer);
  NS_IMETHOD OnProgressURLLoad(nsIDocumentLoader* loader, 
                               nsIURL* aURL, PRUint32 aProgress, 
                               PRUint32 aProgressMax);
  NS_IMETHOD OnStatusURLLoad(nsIDocumentLoader* loader, 
                             nsIURL* aURL, nsString& aMsg);
  NS_IMETHOD OnEndURLLoad(nsIDocumentLoader* loader, 
                          nsIURL* aURL, PRInt32 aStatus);
  NS_IMETHOD HandleUnknownContentType(nsIDocumentLoader* loader, 
                                      nsIURL* aURL,
                                      const char *aContentType,
                                      const char *aCommand );


protected:
  virtual ~nsWebShellWindow();

  void                    ExitModalLoop() { mContinueModalLoop = PR_FALSE; }
  static nsEventStatus PR_CALLBACK HandleEvent(nsGUIEvent *aEvent);

  nsIWidget*   mWindow;
  nsIWebShell* mWebShell;
  PRBool                  mContinueModalLoop;
  PRBool                  mChromeInitialized;
};


#endif /* nsWebShellWindow_h__ */
