/* 
**Default Printer **

Tray Icon Application that changes 
the Default Printer Printer easily

Copyright (C) 1998 - 2002 Timothy Legge
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
//#define _UNICODE

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "include\trayicon.h"

extern int iNbrMenuItemstoAdd;
extern short osver;
extern TCHAR DefaultPrinter[MAX_PATH];

int AddMenuItems(HMENU hMenu, int x, LPTSTR tmpPrinter);

int AddItemsToMenu(HMENU hMenu)
{
	
	LPPRINTER_INFO_4	ppinfo4; /* Structure for Printer Information */
	LPPRINTER_INFO_5	ppinfo5; /* Structure for Printer Information */
	DWORD dwNeeded;
	DWORD dwReturned ; // Number of Printers installed
	BOOL bErr;
	int numPrinters;
	LPTSTR tmpPrinter;
	TCHAR DefaultPrinter[MAX_PATH];
	int  x =0;	/*	Looper used for Adding 
				and deleting Menu Items */
	
	DWORD errlast;
	
	/* Get the name of the Default Printer */
	GetProfileString(_T("windows"), _T("device"),_T(",,,"), DefaultPrinter, sizeof(DefaultPrinter));
 	_stprintf(DefaultPrinter, "%s", _tcstok(DefaultPrinter, ","));
	
	if(osver==cWin95||osver==cWin98)
	{
		EnumPrinters (PRINTER_ENUM_LOCAL,  NULL, 5, "", 0, &dwNeeded, &dwReturned);
		errlast = GetLastError();
		//ppinfo5 = (LPPRINTER_INFO_5) HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, dwNeeded);
		ppinfo5 = malloc(dwNeeded);
		if (ppinfo5)
		{
			bErr = EnumPrinters(PRINTER_ENUM_LOCAL , NULL, 5, (LPBYTE) ppinfo5, dwNeeded, &dwNeeded, &dwReturned);
			
			if(!bErr)
			{
				MessageBox(HWND_DESKTOP, _T("Enumerating Printers Failed") , _T("Change Default Printer"), MB_OK);
				return FALSE;
			}
		}
		
		
	}
	/* Modification 02/24/1999 to check the 
	Networked connections for Windows NT */
	else if (osver==cWinNT)
	{
		EnumPrinters (PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS,  NULL, 4, "", 0,  &dwNeeded, &dwReturned);
		//ppinfo4 = (LPPRINTER_INFO_4) HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, dwNeeded);
		ppinfo4 = malloc(dwNeeded);
		if (ppinfo4)
		{
			bErr = EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS, NULL, 4, (LPBYTE) ppinfo4, dwNeeded, &dwNeeded, &dwReturned);
			if(!bErr)
			{
				MessageBox(HWND_DESKTOP, _T("Enumerating Printers Failed") , _T("Change Default Printer"), MB_OK);
				return FALSE;
			}
			
		}
		
		
	}
	
	for(numPrinters=0;numPrinters<(int)dwReturned;numPrinters++)
	{
				/*	Loop to Add the Printers to the
		Menu to ensure the menu is up-to-date*/
		
		if(osver==cWin95||osver==cWin98)
		{
			tmpPrinter = ppinfo5[numPrinters].pPrinterName;


		}
		else if (osver==cWinNT)
		{
			tmpPrinter = ppinfo4[numPrinters].pPrinterName;
		}
		
		AddMenuItems(hMenu, x, tmpPrinter);
		
		
		if(_tcscmp(DefaultPrinter, tmpPrinter)==0)
		{
			CheckMenuItem(hMenu, MENU_OFFSET+x, MF_CHECKED);
		}
		x++;
	}
	if(osver==cWin95||osver==cWin98)
		free(ppinfo5);
	else if (osver==cWinNT)
		free(ppinfo4);

	iNbrMenuItemstoAdd = (int)dwReturned;
	
	return 0;
}


AddMenuItems(HMENU hMenu, int x, LPTSTR tmpPrinter)
{
	InsertMenu( 
		hMenu,  // handle of menu 
		x,  // menu item that new menu item precedes 
		MF_BYPOSITION ,  // menu item flags 
		MENU_OFFSET+x,		// Menu ID
		tmpPrinter); // menu item identifier or handle of drop-down menu or submenu
	
	return 1;
}