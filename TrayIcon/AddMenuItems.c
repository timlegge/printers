/* 
**TrayIcon Application **

Tray Icon Application shell that can be used to create
a real tray application

Copyright (C) 1998, 2002 Timothy Legge
Please see copying.txt for additional information

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Contact Information:

  Timothy Legge
  Moncton, NB

  tlegge@rogers.com


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