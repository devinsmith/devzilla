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

#include "xp_core.h"			//this is a hack to get it to build. MMP
#include "nscore.h"
#include "nsIFactory.h"
#include "nsISupports.h"
#include "nsGfxCIID.h"
#include "nsFontMetricsMotif.h"
#include "nsRenderingContextMotif.h"
#include "nsImageMotif.h"
#include "nsDeviceContextMotif.h"
#include "nsRegionMotif.h"

static NS_DEFINE_IID(kCFontMetrics, NS_FONT_METRICS_CID);
static NS_DEFINE_IID(kCRenderingContext, NS_RENDERING_CONTEXT_CID);
static NS_DEFINE_IID(kCImage, NS_IMAGE_CID);
static NS_DEFINE_IID(kCDeviceContext, NS_DEVICE_CONTEXT_CID);
static NS_DEFINE_IID(kCRegion, NS_REGION_CID);

static NS_DEFINE_IID(kISupportsIID, NS_ISUPPORTS_IID);
static NS_DEFINE_IID(kIFactoryIID, NS_IFACTORY_IID);

class nsGfxFactoryMotif : public nsIFactory
{
  public:
    // nsISupports methods
    NS_IMETHOD QueryInterface(const nsIID &aIID,
                                       void **aResult);
    NS_IMETHOD_(nsrefcnt) AddRef(void);
    NS_IMETHOD_(nsrefcnt) Release(void);

    // nsIFactory methods
    NS_IMETHOD CreateInstance(nsISupports *aOuter,
                                       const nsIID &aIID,
                                       void **aResult);

    NS_IMETHOD LockFactory(PRBool aLock);

    nsGfxFactoryMotif(const nsCID &aClass);
    virtual ~nsGfxFactoryMotif();

  private:
    nsrefcnt  mRefCnt;
    nsCID     mClassID;
};

nsGfxFactoryMotif::nsGfxFactoryMotif(const nsCID &aClass)
{
  mRefCnt = 0;
  mClassID = aClass;
}

nsGfxFactoryMotif::~nsGfxFactoryMotif()
{
  NS_ASSERTION(mRefCnt == 0, "non-zero refcnt at destruction");
}

nsresult nsGfxFactoryMotif::QueryInterface(const nsIID &aIID,
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

  AddRef(); // Increase reference count for caller
  return NS_OK;
}

nsrefcnt nsGfxFactoryMotif::AddRef()
{
  return ++mRefCnt;
}

nsrefcnt nsGfxFactoryMotif::Release()
{
  if (--mRefCnt == 0) {
    delete this;
    return 0; // Don't access mRefCnt after deleting!
  }
  return mRefCnt;
}

nsresult nsGfxFactoryMotif::CreateInstance(nsISupports *aOuter,
                                          const nsIID &aIID,
                                          void **aResult)
{
  if (aResult == NULL) {
    return NS_ERROR_NULL_POINTER;
  }

  *aResult = NULL;

  nsISupports *inst = nsnull;
  if (mClassID.Equals(kCFontMetrics)) {
    inst = (nsISupports *)new nsFontMetricsMotif();
  }
  else if (mClassID.Equals(kCDeviceContext)) {
    inst = (nsISupports *)new nsDeviceContextMotif();
  }
  else if (mClassID.Equals(kCRenderingContext)) {
    inst = (nsISupports *)new nsRenderingContextMotif();
  }
  else if (mClassID.Equals(kCImage)) {
    inst = (nsISupports *)new nsImageMotif();
  }
  else if (mClassID.Equals(kCRegion)) {
    inst = (nsISupports *)new nsRegionMotif();
  }

  if (inst == NULL) {
    return NS_ERROR_OUT_OF_MEMORY;
  }

  nsresult res = inst->QueryInterface(aIID, aResult);

  if (res != NS_OK) {
    // We didn't get the right interface, so clean up
    delete inst;
  }
//  else {
//    inst->Release();
//  }

  return res;
}

nsresult nsGfxFactoryMotif::LockFactory(PRBool aLock)  
{  
  // Not implemented in simplest case.  
  return NS_OK;
} 

// return the proper factory to the caller
extern "C" NS_GFXNONXP nsresult NSGetFactory(nsISupports* servMgr,
                                             const nsCID &aClass,
                                             const char *aClassName,
                                             const char *aProgID,
                                             nsIFactory **aFactory)
{
  if (nsnull == aFactory) {
    return NS_ERROR_NULL_POINTER;
  }

  *aFactory = new nsGfxFactoryMotif(aClass);

  if (nsnull == aFactory) {
    return NS_ERROR_OUT_OF_MEMORY;
  }

  return (*aFactory)->QueryInterface(kIFactoryIID, (void**)aFactory);
}
