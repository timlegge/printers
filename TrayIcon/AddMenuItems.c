/* 
**TrayIcon Application **

Tray Icon Application shell that can be used to create
a real tray application

Copyright (C) 1998 - 2020 Timothy Legge

Licensed under MIT or GPL-2.0-or-later

Contact Information:

  Timothy Legge
  Moncton, NB

  timlegge@gmail.com

$Revision$
$Author$
$Date$

*/
#include <windows.h>
#include "include\trayicon.h"

extern int iLastItemChecked;
extern int iNbrMenuItemstoAdd;

int AddMenuItems(HMENU hMenu, int x, LPTSTR tmpPrinter);

int AddItemsToMenu(HMENU hMenu)
{
	
	int numItems;
	int  x =0;	/*	Looper used for Adding 
				and deleting Menu Items */
	
	
	for(numItems=0;numItems < 3; numItems++)
	{
		
		AddMenuItems(hMenu, x, "MenuItem");
		
		
		if(x==iLastItemChecked-3)
		{
			CheckMenuItem(hMenu, MENU_OFFSET+x, MF_CHECKED);
		}
		x++;
	}
	
	iNbrMenuItemstoAdd = 3;
	
	return 0;
}


AddMenuItems(HMENU hMenu, int x, LPTSTR tmpMenuItem)
{
	InsertMenu( 
		hMenu,  // handle of menu 
		x,  // menu item that new menu item precedes 
		MF_BYPOSITION ,  // menu item flags 
		MENU_OFFSET+x,		// Menu ID
		tmpMenuItem); // menu item identifier or handle of drop-down menu or submenu
	
	return 1;
}
