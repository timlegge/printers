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
#include <stdio.h>
#include "include\resource.h"

int iLastItemChecked;

int MenuItemClicked(UINT iMenuItemSelected, HMENU hMenu)
{

	char tmpString[25];
	sprintf(tmpString, "Menu Item #%i selected\n", iMenuItemSelected);
	
	MessageBox(
				HWND_DESKTOP,
				tmpString,
				"TrayIcon Application", MB_OK);
	
	if(iMenuItemSelected != IDM_EXIT && iMenuItemSelected != IDM_ABOUT)
		iLastItemChecked = iMenuItemSelected ;
	
	return 0;
}

