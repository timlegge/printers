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

