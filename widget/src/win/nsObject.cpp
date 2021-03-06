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


#include "nsObject.h"


CList nsObject::s_liveChain;
PRMonitor *nsObject::s_liveChainMutex = PR_NewMonitor();

#ifdef _DEBUG
int32 nsObject::s_nObjects = 0;
#endif

/**
 * constructor
 */
nsObject::nsObject()
{
    //
    // Add the new object the chain of allocated nsObjects
    //
    PR_EnterMonitor(s_liveChainMutex);
    s_liveChain.Append(m_link);
    PR_ExitMonitor(s_liveChainMutex);
#ifdef _DEBUG
    s_nObjects++;
#endif
}


/**
 * destructor
 */
nsObject::~nsObject()
{
#ifdef _DEBUG
    s_nObjects--;
#endif
    //
    // Remove from the chain of allocated nsObjects
    //
    PR_EnterMonitor(s_liveChainMutex);
    m_link.Remove();
    PR_ExitMonitor(s_liveChainMutex);
}


/**
 * static utility. Delete all live objects
 */

void nsObject::DeleteAllObjects(void)
{
    PR_EnterMonitor(s_liveChainMutex);

    while (!s_liveChain.IsEmpty()) {
        nsObject *pnsObject;

        pnsObject = (nsObject*)OBJECT_PTR_FROM_CLIST(nsObject, s_liveChain.next);

        // Remove the event from the chain...
        pnsObject->m_link.Remove();
        delete pnsObject;
    }

    PR_ExitMonitor(s_liveChainMutex);
}

