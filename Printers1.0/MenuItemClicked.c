/* 
**Default Printer **

Tray Icon Application that changes 
the Default Printer Printer easily

Copyright (C) 1998, 2000 Timothy Legge
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

  tlegge@fundy.net

$Revision$
$Author$
$Date$

*/


#include <windows.h>
#include <stdio.h>
#include "include\trayicon.h"

extern int iNbrMenuItemstoAdd;
extern short osver;
extern char DefaultPrinter[255];
extern short osver;


int MenuItemClicked(UINT iMenuItemSelected, HMENU hMenu)
{
	
	LPPRINTER_INFO_2	ppinfo2; /* Structure for Printer Information */
	DWORD dwNeeded;
	DWORD dwReturned ; // Number of Printers installed
	BOOL bErr;
	LPTSTR tmpPrinter="";
	char pszTip[28] = ""; // Tooltip displayed over Icon
	int  x =0;	
	/*	Looper used for Adding 
	and deleting Menu Items */
	HKEY hKey;
	LRESULT tempretn;
	LPTSTR lpMappedPort;
	DWORD lpcbData;
	
	
	LPTSTR infobuff="";
	iMenuItemSelected=iMenuItemSelected-MENU_OFFSET;
	
	if(osver==cWin95||osver==cWin98)
	{
		EnumPrinters (PRINTER_ENUM_LOCAL,  NULL, 2, "", 0, &dwNeeded, &dwReturned);
		ppinfo2 = (LPPRINTER_INFO_2) HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, dwNeeded);
		if (ppinfo2)
		{
			bErr = EnumPrinters(PRINTER_ENUM_LOCAL , NULL, 2, (LPBYTE) ppinfo2, dwNeeded, &dwNeeded, &dwReturned);
			if(!bErr)
			{
				MessageBox(HWND_DESKTOP, "Enumerating Printers Failed" , "Change Default Printer", MB_OK);
				return FALSE;
			}
			sprintf(tmpPrinter, "%s,%s,%s", ppinfo2[iMenuItemSelected].pPrinterName, ppinfo2[iMenuItemSelected].pDriverName, ppinfo2[iMenuItemSelected].pPortName);
			WriteProfileString("windows", "device", tmpPrinter);
			tempretn = SendMessageTimeout(HWND_BROADCAST, WM_WININICHANGE, 0L, (LPARAM)(LPCTSTR)"windows", SMTO_NORMAL, 1000, NULL);
			HeapFree( GetProcessHeap(), 0, ppinfo2 ); 
			
		}
		
	}
	/* Modification 02/24/1999 to check the 
	Networked connections for Windows NT */
	else if (osver==cWinNT)
	{
		iMenuItemSelected=iMenuItemSelected+MENU_OFFSET;
		
		
		GetMenuString(hMenu, iMenuItemSelected, infobuff, 255, MF_BYCOMMAND);
		
		tempretn = RegOpenKeyEx(HKEY_CURRENT_USER,  // handle of open key 
			"Software\\Microsoft\\Windows NT\\CurrentVersion\\Devices", // address of name of subkey to open 
			0,  // reserved 
			KEY_QUERY_VALUE , // security access mask 
			&hKey // address of handle of open key 
			); 
		
		
		tempretn = RegQueryValueEx(hKey, // handle of key to query 
			infobuff, // address of name of value to query 
			NULL,  // reserved 
			NULL, // address of buffer for value type 
			NULL,  // address of data buffer 
			&lpcbData  // address of data buffer size 
			); 
		
		lpMappedPort = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, lpcbData);
		
		tempretn = RegQueryValueEx(hKey, // handle of key to query 
			infobuff, // address of name of value to query 
			NULL,  // reserved 
			NULL, // address of buffer for value type 
			lpMappedPort,  // address of data buffer 
			&lpcbData  // address of data buffer size 
			); 
		
		RegCloseKey(hKey);
		
		sprintf(tmpPrinter, "%s,%s", infobuff, lpMappedPort);
		HeapFree( GetProcessHeap(), 0, lpMappedPort); 
		WriteProfileString("windows", "device", tmpPrinter);
		SendMessageTimeout(HWND_BROADCAST, WM_WININICHANGE, 0L, 0L, SMTO_NORMAL, 1000, NULL);
	}
	
	return 0;
}

