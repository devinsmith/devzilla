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
#ifndef Window_h__
#define Window_h__

#include "nsISupports.h"

#include "nsToolkit.h"
#include "nsIWidget.h"
#include "nsIEnumerator.h"
#include "nsIAppShell.h"

#include "nsIMouseListener.h"
#include "nsIEventListener.h"
#include "nsString.h"

#include "Xm/Xm.h"

#include "nsXtManageWidget.h"

class nsFont;

#define NSRGB_2_COLOREF(color) \
            RGB(NS_GET_R(color),NS_GET_G(color),NS_GET_B(color))


/**
 * Native Motif window wrapper. 
 */

class nsWindow : public nsIWidget
{
public:
      // nsIWidget interface

    nsWindow();
    virtual ~nsWindow();

    // nsISupports
    NS_DECL_ISUPPORTS
#if 0

    virtual void ConvertToDeviceCoordinates(nscoord &aX, nscoord &aY);
 


    NS_IMETHOD            PreCreateWidget(nsWidgetInitData *aWidgetInitData) { return NS_OK; }
#endif
    // nsIWidget interface
    NS_IMETHOD            Create(nsIWidget *aParent,
                                     const nsRect &aRect,
                                     EVENT_CALLBACK aHandleEventFunction,
                                     nsIDeviceContext *aContext,
                                     nsIAppShell *aAppShell = nsnull,
                                     nsIToolkit *aToolkit = nsnull,
                                     nsWidgetInitData *aInitData = nsnull);
    NS_IMETHOD            Create(nsNativeWidget aParent,
                                     const nsRect &aRect,
                                     EVENT_CALLBACK aHandleEventFunction,
                                     nsIDeviceContext *aContext,
                                     nsIAppShell *aAppShell = nsnull,
                                     nsIToolkit *aToolkit = nsnull,
                                     nsWidgetInitData *aInitData = nsnull);
    NS_IMETHOD              GetClientData(void*& aClientData);
    NS_IMETHOD              SetClientData(void* aClientData);
#if 0
    NS_IMETHOD            Destroy();
    virtual nsIWidget*      GetParent(void);
    virtual nsIEnumerator*  GetChildren();
#endif
    virtual void            AddChild(nsIWidget* aChild);
    virtual void            RemoveChild(nsIWidget* aChild);
    NS_IMETHOD            Show(PRBool bState);
#if 0
    NS_IMETHOD            IsVisible(PRBool & aState);

    NS_IMETHOD            Move(PRUint32 aX, PRUint32 aY);
#endif
    NS_IMETHOD            Resize(PRUint32 aWidth,
                                   PRUint32 aHeight,
                                   PRBool   aRepaint);
    NS_IMETHOD            Resize(PRUint32 aX,
                                   PRUint32 aY,
                                   PRUint32 aWidth,
                                   PRUint32 aHeight,
                                   PRBool   aRepaint);
#if 0
    NS_IMETHOD            Enable(PRBool bState);
    NS_IMETHOD            SetFocus(void);
#endif
    NS_IMETHOD            GetBounds(nsRect &aRect);
#if 0
    virtual nscolor         GetForegroundColor(void);
    NS_IMETHOD            SetForegroundColor(const nscolor &aColor);
    virtual nscolor         GetBackgroundColor(void);
#endif
    NS_IMETHOD            SetBackgroundColor(const nscolor &aColor);
#if 0
    virtual nsIFontMetrics* GetFont(void);
    NS_IMETHOD            SetFont(const nsFont &aFont);
    virtual nsCursor        GetCursor();
#endif
    NS_IMETHOD            SetCursor(nsCursor aCursor);
#if 0
    NS_IMETHOD            Invalidate(PRBool aIsSynchronous);
    NS_IMETHOD            Invalidate(const nsRect &aRect, PRBool aIsSynchronous);
    NS_IMETHOD            Update();
#endif
    virtual void*           GetNativeData(PRUint32 aDataType);
#if 0
    virtual nsIRenderingContext* GetRenderingContext();
    NS_IMETHOD            SetColorMap(nsColorMap *aColorMap);
    virtual nsIDeviceContext* GetDeviceContext();
    virtual nsIAppShell *   GetAppShell();
    NS_IMETHOD            Scroll(PRInt32 aDx, PRInt32 aDy, nsRect *aClipRect);
#endif
    virtual nsIToolkit*     GetToolkit();
#if 0
    NS_IMETHOD            SetBorderStyle(nsBorderStyle aBorderStyle); 
#endif
    NS_IMETHOD            SetTitle(const nsString& aTitle);
#if 0
    NS_IMETHOD            SetTooltips(PRUint32 aNumberOfTips,nsRect* aTooltipAreas[]);   
    NS_IMETHOD            RemoveTooltips();
    NS_IMETHOD            UpdateTooltips(nsRect* aNewTips[]);
    NS_IMETHOD            WidgetToScreen(const nsRect& aOldRect, nsRect& aNewRect);
    NS_IMETHOD            ScreenToWidget(const nsRect& aOldRect, nsRect& aNewRect);
    NS_IMETHOD            AddMouseListener(nsIMouseListener * aListener);
    NS_IMETHOD            AddEventListener(nsIEventListener * aListener);
    NS_IMETHOD            BeginResizingChildren(void);
    NS_IMETHOD            EndResizingChildren(void);
    NS_IMETHOD            SetMenuBar(nsIMenuBar * aMenuBar); 
    NS_IMETHOD            GetPreferredSize(PRInt32& aWidth, PRInt32& aHeight);
    NS_IMETHOD            SetPreferredSize(PRInt32 aWidth, PRInt32 aHeight);
#endif
    NS_IMETHOD            DispatchEvent(nsGUIEvent* event, nsEventStatus & aStatus);
    NS_IMETHOD            GetClientBounds(nsRect &aRect);
    NS_IMETHOD            GetBorderSize(PRInt32 &aWidth, PRInt32 &aHeight);
#if 0
    NS_IMETHOD            Paint(nsIRenderingContext& aRenderingContext, const nsRect& aDirtyRect);

#endif
    virtual PRBool IsChild() { return(PR_FALSE); };

    // Utility methods
    void     SetBounds(const nsRect &aRect);
    PRBool   ConvertStatus(nsEventStatus aStatus);
    virtual  PRBool OnPaint(nsPaintEvent &event);
#if 0
    virtual  void   OnDestroy();
#endif
    PRBool   OnKey(PRUint32 aEventType, PRUint32 aKeyCode, nsKeyEvent* aEvent);
#if 0
    PRBool   DispatchFocus(nsGUIEvent &aEvent);
    virtual  PRBool OnScroll(nsScrollbarEvent & aEvent, PRUint32 cPos);
    void     SetIgnoreResize(PRBool aIgnore);
    PRBool   IgnoreResize();
#endif
    PRUint32 GetYCoord(PRUint32 aNewY);
    PRBool   DispatchMouseEvent(nsMouseEvent& aEvent);
    virtual  PRBool OnResize(nsSizeEvent &aEvent);

     // Resize event management
    void   SetResizeRect(nsRect& aRect);
    void   SetResized(PRBool aResized);
    void   GetResizeRect(nsRect* aRect);
    PRBool GetResized();
    char gInstanceClassName[256];
protected:
  void   InitCallbacks(char * aName = nsnull);
  PRBool DispatchWindowEvent(nsGUIEvent* event);

  void CreateGC();
  void CreateWindow(nsNativeWidget aNativeParent, nsIWidget *aWidgetParent,
                      const nsRect &aRect,
                      EVENT_CALLBACK aHandleEventFunction,
                      nsIDeviceContext *aContext,
                      nsIAppShell *aAppShell,
                      nsIToolkit *aToolkit,
                      nsWidgetInitData *aInitData);

  void CreateMainWindow(nsNativeWidget aNativeParent, nsIWidget *aWidgetParent,
                      const nsRect &aRect,
                      EVENT_CALLBACK aHandleEventFunction,
                      nsIDeviceContext *aContext,
                      nsIAppShell *aAppShell,
                      nsIToolkit *aToolkit,
                      nsWidgetInitData *aInitData);

  void CreateChildWindow(nsNativeWidget aNativeParent, nsIWidget *aWidgetParent,
                      const nsRect &aRect,
                      EVENT_CALLBACK aHandleEventFunction,
                      nsIDeviceContext *aContext,
                      nsIAppShell *aAppShell,
                      nsIToolkit *aToolkit,
                      nsWidgetInitData *aInitData);


  void InitToolkit(nsIToolkit *aToolkit, nsIWidget * aWidgetParent);
  void InitDeviceContext(nsIDeviceContext *aContext, Widget aWidgetParent);
#if 0

  virtual void            UpdateVisibilityFlag();
  virtual void            UpdateDisplay();
#endif
protected:
  EVENT_CALLBACK mEventCallback;
  nsIDeviceContext *mContext;
#if 0
  nsIFontMetrics *mFontMetrics;
#endif
  nsIAppShell *mAppShell;
  nsIMouseListener * mMouseListener;
  nsIEventListener * mEventListener;
  nsToolkit   *mToolkit;
public:
  Widget mWidget;
protected:
  nscolor     mBackground;
  nscolor     mForeground;
  nsCursor    mCursor;
#if 0
  nsBorderStyle mBorderStyle;
#endif
  nsRect      mBounds;
  PRBool      mIgnoreResize;
  PRBool      mShown;
#if 0
  PRBool      mVisible;
  PRBool      mDisplayed;
#endif
  void*       mClientData;
#if 0
  // XXX Temporary, should not be caching the font
  nsFont *    mFont;
  PRInt32     mPreferredWidth;
  PRInt32     mPreferredHeight;

#endif
  // Resize event management
  nsRect mResizeRect;
  int mResized;
  PRBool mLowerLeft;

private:
  GC mGC;
};

//
// A child window is a window with different style
//
class ChildWindow : public nsWindow {
  public:
    ChildWindow() {};
    virtual PRBool IsChild() { return(PR_TRUE); };
};

#endif // Window_h__
