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
#define NS_IMPL_IDS
#include "nsIPref.h"
#include "nsIComponentManager.h"
#include "nsWidgetsCID.h"
#include "nsGfxCIID.h"
#if 0
#include "nsViewsCID.h"
#endif
#include "nsPluginsCID.h"
#if 0
#include "nsIBrowserWindow.h"
#endif
#include "nsIWebShell.h"
#include "nsIDocumentLoader.h"
#if 0
#include "nsIThrobber.h"
#endif

#include "nsXPComCIID.h"
#if 0
#include "nsParserCIID.h"
#include "nsDOMCID.h"
#include "nsLayoutCID.h"
#endif
#include "nsINetService.h"
#include "nsIPluginManager.h"
#include "nsSpecialSystemDirectory.h"    // For exe dir


#ifdef XP_PC

    #define XPCOM_DLL  "xpcom32.dll"
#define WIDGET_DLL "raptorwidget.dll"
#define GFXWIN_DLL "raptorgfxwin.dll"
#define VIEW_DLL   "raptorview.dll"
#define WEB_DLL    "raptorweb.dll"
#define PLUGIN_DLL "raptorplugin.dll"
#define PREF_DLL   "xppref32.dll"
#define PARSER_DLL "raptorhtmlpars.dll"
#define DOM_DLL    "jsdom.dll"
#define LAYOUT_DLL "raptorhtml.dll"
#define NETLIB_DLL "netlib.dll"

#define APPSHELL_DLL "nsappshell.dll"
#else

#ifdef XP_MAC

#define WIDGET_DLL		"WIDGET_DLL"
#define GFXWIN_DLL		"GFXWIN_DLL"
#define VIEW_DLL			"VIEW_DLL"
#define WEB_DLL				"WEB_DLL"
#define PLUGIN_DLL		"PLUGIN_DLL"
#define PREF_DLL			"PREF_DLL"
#define PARSER_DLL		"PARSER_DLL"
#define DOM_DLL    		"DOM_DLL"
#define LAYOUT_DLL		"LAYOUT_DLL"
#define NETLIB_DLL		"NETLIB_DLL"
#define APPSHELL_DLL "APPSHELL_DLL"
//#define EDITOR_DLL	"EDITOR_DLL"	// temporary


#else

// XP_UNIX
    #define XPCOM_DLL  "libxpcom.so"
//#ifndef WIDGET_DLL
#define WIDGET_DLL "libraptorwidget.so"
///#endif
//#ifndef GFXWIN_DLL
#define GFXWIN_DLL "libraptorgfx.so"
//#endif
//#define VIEW_DLL   "libraptorview.so"
#define WEB_DLL    "libraptorwebwidget.so"
    #define PLUGIN_DLL "libraptorplugin.so"
#define PREF_DLL   "./libpref.so"
//#define PARSER_DLL "libraptorhtmlpars.so"
//#define DOM_DLL    "libjsdom.so"
//#define LAYOUT_DLL "libraptorhtml.so"
#define NETLIB_DLL "libmoznetlib.so"

#define APPSHELL_DLL  "libnsappshell.so"

#endif // XP_MAC

#endif // XP_PC

// Class ID's
static NS_DEFINE_IID(kEventQueueServiceCID, NS_EVENTQUEUESERVICE_CID);
#if 0
static NS_DEFINE_IID(kCFileWidgetCID, NS_FILEWIDGET_CID);
#endif
static NS_DEFINE_IID(kCWindowCID, NS_WINDOW_CID);
#if 0
static NS_DEFINE_IID(kCDialogCID, NS_DIALOG_CID);
static NS_DEFINE_IID(kCLabelCID, NS_LABEL_CID);
#endif
static NS_DEFINE_IID(kCAppShellCID, NS_APPSHELL_CID);
static NS_DEFINE_IID(kCToolkitCID, NS_TOOLKIT_CID);
static NS_DEFINE_IID(kCWindowIID, NS_WINDOW_CID);
#if 0
static NS_DEFINE_IID(kCScrollbarIID, NS_VERTSCROLLBAR_CID);
static NS_DEFINE_IID(kCHScrollbarIID, NS_HORZSCROLLBAR_CID);
static NS_DEFINE_IID(kCButtonCID, NS_BUTTON_CID);
static NS_DEFINE_IID(kCComboBoxCID, NS_COMBOBOX_CID);
static NS_DEFINE_IID(kCListBoxCID, NS_LISTBOX_CID);
static NS_DEFINE_IID(kCRadioButtonCID, NS_RADIOBUTTON_CID);
static NS_DEFINE_IID(kCTextAreaCID, NS_TEXTAREA_CID);
static NS_DEFINE_IID(kCTextFieldCID, NS_TEXTFIELD_CID);
static NS_DEFINE_IID(kCCheckButtonIID, NS_CHECKBUTTON_CID);
#endif
static NS_DEFINE_IID(kCChildIID, NS_CHILD_CID);
static NS_DEFINE_IID(kCRenderingContextIID, NS_RENDERING_CONTEXT_CID);
static NS_DEFINE_IID(kCDeviceContextIID, NS_DEVICE_CONTEXT_CID);
#if 0
static NS_DEFINE_IID(kCFontMetricsIID, NS_FONT_METRICS_CID);
static NS_DEFINE_IID(kCImageIID, NS_IMAGE_CID);
static NS_DEFINE_IID(kCRegionIID, NS_REGION_CID);
static NS_DEFINE_IID(kCBlenderIID, NS_BLENDER_CID);
static NS_DEFINE_IID(kCDeviceContextSpecCID, NS_DEVICE_CONTEXT_SPEC_CID);
static NS_DEFINE_IID(kCDeviceContextSpecFactoryCID, NS_DEVICE_CONTEXT_SPEC_FACTORY_CID);
static NS_DEFINE_IID(kCViewManagerCID, NS_VIEW_MANAGER_CID);
static NS_DEFINE_IID(kCViewCID, NS_VIEW_CID);
static NS_DEFINE_IID(kCScrollingViewCID, NS_SCROLLING_VIEW_CID);
#endif
static NS_DEFINE_IID(kWebShellCID, NS_WEB_SHELL_CID);
static NS_DEFINE_IID(kCDocLoaderServiceCID, NS_DOCUMENTLOADER_SERVICE_CID);
#if 0
static NS_DEFINE_IID(kThrobberCID, NS_THROBBER_CID);
#endif
static NS_DEFINE_IID(kCPluginHostCID, NS_PLUGIN_HOST_CID);
#if 0
static NS_DEFINE_IID(kCParserCID, NS_PARSER_IID);
static NS_DEFINE_IID(kLookAndFeelCID, NS_LOOKANDFEEL_CID);
static NS_DEFINE_IID(kCDOMScriptObjectFactory, NS_DOM_SCRIPT_OBJECT_FACTORY_CID);
static NS_DEFINE_IID(kCDOMNativeObjectRegistry, NS_DOM_NATIVE_OBJECT_REGISTRY_CID);
static NS_DEFINE_IID(kCHTMLDocument, NS_HTMLDOCUMENT_CID);
static NS_DEFINE_IID(kCXMLDocument, NS_XMLDOCUMENT_CID);
static NS_DEFINE_IID(kCImageDocument, NS_IMAGEDOCUMENT_CID);
static NS_DEFINE_IID(kCHTMLImageElementFactory, NS_HTMLIMAGEELEMENTFACTORY_CID);
#endif
static NS_DEFINE_IID(kNetServiceCID, NS_NETSERVICE_CID);
#if 0
static NS_DEFINE_IID(kCImageButtonCID, NS_IMAGEBUTTON_CID);
static NS_DEFINE_IID(kCToolbarCID, NS_TOOLBAR_CID);
static NS_DEFINE_IID(kCToolbarManagerCID, NS_TOOLBARMANAGER_CID);
static NS_DEFINE_IID(kCToolbarItemHolderCID, NS_TOOLBARITEMHOLDER_CID);
static NS_DEFINE_IID(kCPopUpMenuCID, NS_POPUPMENU_CID);
static NS_DEFINE_IID(kCMenuButtonCID, NS_MENUBUTTON_CID);
#endif
static NS_DEFINE_IID(kCMenuBarCID, NS_MENUBAR_CID);
static NS_DEFINE_IID(kCMenuCID, NS_MENU_CID);
static NS_DEFINE_IID(kCMenuItemCID, NS_MENUITEM_CID);

static NS_DEFINE_CID(kCPluginManagerCID,          NS_PLUGINMANAGER_CID);

extern "C" void
NS_SetupRegistry()
{
  // Autoregistration happens here. The rest of RegisterComponent() calls should happen
  // only for dlls not in the components directory.

  // Create exeDir/"components"
  nsSpecialSystemDirectory sysdir(nsSpecialSystemDirectory::OS_CurrentProcessDirectory);
  sysdir += "components";
  const char *componentsDir = sysdir.GetCString(); // native path
  if (componentsDir != NULL)
  {
#ifdef XP_PC
      /* The PC version of the directory from filePath is of the form
       *    /y|/moz/mozilla/dist/bin/components
       * We need to remove the initial / and change the | to :
       * for all this to work with NSPR.      
       */
#endif /* XP_PC */
      printf("nsComponentManager: Using components dir: %s\n", componentsDir);

#ifdef XP_MAC
      nsComponentManager::AutoRegister(nsIComponentManager::NS_Startup, nsnull);
#else
      nsComponentManager::AutoRegister(nsIComponentManager::NS_Startup, componentsDir);
#endif    /* XP_MAC */
      // XXX Look for user specific components
      // XXX UNIX: ~/.mozilla/components
      printf("nsComponentManager: Auto registration complete\n");
  }

  nsComponentManager::RegisterComponent(kEventQueueServiceCID, NULL, NULL, XPCOM_DLL, PR_FALSE, PR_FALSE);
#if 0
  nsRepository::RegisterFactory(kLookAndFeelCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
#endif
  nsComponentManager::RegisterComponent(kCWindowIID, NULL, NULL, WIDGET_DLL, PR_FALSE, PR_FALSE);
#if 0
  nsRepository::RegisterFactory(kCScrollbarIID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCHScrollbarIID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCDialogCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCLabelCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCButtonCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCComboBoxCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCFileWidgetCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCListBoxCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCRadioButtonCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCTextAreaCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCTextFieldCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCCheckButtonIID, WIDGET_DLL, PR_FALSE, PR_FALSE);
#endif
  nsComponentManager::RegisterComponent(kCChildIID, NULL, NULL, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsComponentManager::RegisterComponent(kCAppShellCID, NULL, NULL, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsComponentManager::RegisterComponent(kCToolkitCID, NULL, NULL, WIDGET_DLL, PR_FALSE, PR_FALSE);
#if 0
  nsRepository::RegisterFactory(kCRenderingContextIID, GFXWIN_DLL, PR_FALSE, PR_FALSE);
#endif
  nsComponentManager::RegisterComponent(kCDeviceContextIID, NULL, NULL, GFXWIN_DLL, PR_FALSE, PR_FALSE);
#if 0
  nsRepository::RegisterFactory(kCFontMetricsIID, GFXWIN_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCImageIID, GFXWIN_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCRegionIID, GFXWIN_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCBlenderIID, GFXWIN_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCDeviceContextSpecCID, GFXWIN_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCDeviceContextSpecFactoryCID, GFXWIN_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCViewManagerCID, VIEW_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCViewCID, VIEW_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCScrollingViewCID, VIEW_DLL, PR_FALSE, PR_FALSE);
#endif
  nsComponentManager::RegisterComponent(kWebShellCID, NULL, NULL, WEB_DLL, PR_FALSE, PR_FALSE);
  nsComponentManager::RegisterComponent(kCDocLoaderServiceCID, NULL, NULL, WEB_DLL, PR_FALSE, PR_FALSE);
#if 0
  nsRepository::RegisterFactory(kThrobberCID, WEB_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kPrefCID, PREF_DLL, PR_FALSE, PR_FALSE);
#endif
  nsComponentManager::RegisterComponent(kCPluginHostCID, NULL, NULL, PLUGIN_DLL, PR_FALSE, PR_FALSE);
#if 0
  nsRepository::RegisterFactory(kCParserCID, PARSER_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCDOMScriptObjectFactory, DOM_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCDOMNativeObjectRegistry, DOM_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCHTMLDocument, LAYOUT_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCXMLDocument, LAYOUT_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCImageDocument, LAYOUT_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCHTMLImageElementFactory, LAYOUT_DLL, PR_FALSE, PR_FALSE);
#endif
  nsComponentManager::RegisterComponent(kNetServiceCID, NULL, NULL, NETLIB_DLL, PR_FALSE, PR_FALSE);
#if 0
  nsRepository::RegisterFactory(kCImageButtonCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCToolbarCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCToolbarManagerCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCToolbarItemHolderCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCPopUpMenuCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCMenuButtonCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCMenuBarCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCMenuCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
  nsRepository::RegisterFactory(kCMenuItemCID, WIDGET_DLL, PR_FALSE, PR_FALSE);
#endif
//  nsRepository::RegisterComponent(kCAppShellServiceCID, NULL, NULL, APPSHELL_DLL, PR_FALSE, PR_FALSE);

  nsComponentManager::RegisterComponent(kCPluginManagerCID, NULL, NULL, PLUGIN_DLL,      PR_FALSE, PR_FALSE);
}
