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
#include "nsIFactory.h"
#include "nsRepository.h"
#include "nscore.h"
#include "nsIComponentManager.h"
#include "nsAppShellCIDs.h"
#include "nsICmdLineService.h"

/* extern the factory entry points... */
nsresult NS_NewAppShellServiceFactory(nsIFactory** aFactory);


static NS_DEFINE_IID(kAppShellServiceCID, NS_APPSHELL_SERVICE_CID);
static NS_DEFINE_IID(kCmdLineServiceCID,  NS_COMMANDLINE_SERVICE_CID);

/*
 * Global entry point to register all components in the registry...
 */
extern "C" NS_EXPORT nsresult
NSRegisterSelf(nsISupports* serviceMgr, const char *path)
{
    nsComponentManager::RegisterComponent(kAppShellServiceCID, NULL, NULL, path, PR_TRUE, PR_TRUE);
    nsComponentManager::RegisterComponent(kCmdLineServiceCID,  NULL, NULL, path, PR_TRUE, PR_TRUE);

   return NS_OK;
}

/*
 * Global entry point to unregister all components in the registry...
 */
extern "C" NS_EXPORT nsresult
NSUnregisterSelf(nsISupports* serviceMgr, const char *path)
{
    nsComponentManager::UnregisterFactory(kAppShellServiceCID, path);
    nsComponentManager::UnregisterFactory(kCmdLineServiceCID,  path);

    return NS_OK;
}


/*
 * Global entry point to create class factories for the components
 * available withing the DLL...
 */
#if defined(XP_MAC) && defined(MAC_STATIC)
extern "C" NS_APPSHELL nsresult 
NSGetFactory_APPSHELL_DLL(nsISupports* serviceMgr,
                          const nsCID &aClass,
                          const char *aClassName,
                          const char *aProgID,
                          nsIFactory **aFactory)
#else
extern "C" NS_APPSHELL nsresult
NSGetFactory(nsISupports* serviceMgr,
             const nsCID &aClass,
             const char *aClassName,
             const char *aProgID,
             nsIFactory **aFactory)
#endif
{
  nsresult rv = NS_ERROR_FACTORY_NOT_REGISTERED;

  if (nsnull == aFactory) {
    return NS_ERROR_NULL_POINTER;
  }

  if (aClass.Equals(kAppShellServiceCID)) {
    rv = NS_NewAppShellServiceFactory(aFactory);
  }
  else if (aClass.Equals(kCmdLineServiceCID)) {
    rv = NS_NewCmdLineServiceFactory(aFactory);
  }

  return rv;
}

