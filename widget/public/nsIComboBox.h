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

#ifndef nsIComboBox_h__
#define nsIComboBox_h__

#include "nsIListWidget.h"
#include "nsString.h"

// {961085F6-BD28-11d1-97EF-00609703C14E}
#define NS_ICOMBOBOX_IID \
{ 0x961085f6, 0xbd28, 0x11d1, { 0x97, 0xef, 0x0, 0x60, 0x97, 0x3, 0xc1, 0x4e } }


/**
 * Initialize combobox data
 */

struct nsComboBoxInitData : public nsWidgetInitData {
  nsComboBoxInitData()
    : mDropDownHeight(0)
  {
  }

  PRUint32 mDropDownHeight; // in pixels
};

/**
 * Single selection drop down list. See nsIListWidget for capabilities 
 */

class nsIComboBox : public nsISupports {
public:
    /**
     * Set an item at the specific position
     *
     * @param   aItem     the item name. The item has to be null terminated
     * @param   aPosition the position the item should be inserted at
     *                    0 is at the top of the list
     *                    -1 is at the end of the list
     */
    NS_IMETHOD AddItemAt(nsString &aItem, PRInt32 aPosition) = 0;

    /**
     * Finds the first occurrence of the specified item
     *
     * @param   aItem     the string to be filled
     * @param   aStartPos the starting position (index)
     * @return  PR_TRUE if successful, PR_FALSE otherwise
     *
     */
    virtual PRInt32  FindItem(nsString &aItem, PRInt32 aStartPos) = 0;

    /**
     * Returns the number of items in the list
     *
     * @return  the number of items
     *
     */
    virtual PRInt32  GetItemCount() = 0;

    /**
     * Remove the first occurrence of the specified item
     *
     * @param   aPosition the item position
     *                    0 is at the top of the list
     *                    -1 is at the end of the list
     *
     * @return  PR_TRUE if successful, PR_FALSE otherwise
     *
     */
    virtual PRBool RemoveItemAt(PRInt32 aPosition) = 0;

    /**
     * Gets an item at a specific location
     *
     * @param   anItem    on return contains the string of the item at that position
     * @param   aPosition the Position of the item
     *
     */
     virtual PRBool GetItemAt(nsString& anItem, PRInt32 aPosition) = 0;

    /**
     * Gets the selected item for a single selection list
     *
     * @param   aItem  on return contains the string of the selected item
     *
     */
     NS_IMETHOD GetSelectedItem(nsString &aItem) = 0;

    /**
     * Returns with the index of the selected item
     *
     * @return  PRInt32, index of selected item
     *
     */
    virtual PRInt32 GetSelectedIndex()  = 0;

    /**
     * Select the item at the specified position
     *
     * @param   PRInt32, the item position
     *                   0 is at the top of the list
     *                   -1 is at the end of the list
     *
     */
    NS_IMETHOD SelectItem(PRInt32 aPosition)  = 0;

    /**
     * Deselects all the items in the list
     *
     */
    NS_IMETHOD Deselect()  = 0;
};


#endif // nsIComboBox_h__



