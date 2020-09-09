/* 
**Default Printer **

Tray Icon Application that changes 
the Default Printer Printer easily

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
#include <tchar.h>
#include "include\trayicon.h"

extern int iNbrMenuItemstoAdd;
extern short osver;
extern TCHAR DefaultPrinter[MAX_PATH];
extern short osver;


int MenuItemClicked(UINT iMenuItemSelected, HMENU hMenu)
{
	
	LPPRINTER_INFO_2	ppinfo2; /* Structure for Printer Information */
	DWORD dwNeeded;
	DWORD dwReturned ; // Number of Printers installed
	BOOL bErr;
	LPTSTR tmpPrinter = malloc(MAX_PATH);
	LPTSTR lpMappedPort;
	LPTSTR infobuff;
	TCHAR pszTip[28] = _T(""); // Tooltip displayed over Icon
	int  x =0;	
	/*	Looper used for Adding 
	and deleting Menu Items */
	HKEY hKey;
	LRESULT tempretn;
	DWORD lpcbData;
	iMenuItemSelected=iMenuItemSelected-MENU_OFFSET;
	
	if(osver==cWin95||osver==cWin98)
	{
		EnumPrinters (PRINTER_ENUM_LOCAL,  NULL, 2, "", 0, &dwNeeded, &dwReturned);
		//ppinfo2 = (LPPRINTER_INFO_2) HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, );
		ppinfo2 = malloc(dwNeeded);
		if (ppinfo2)
		{
			bErr = EnumPrinters(PRINTER_ENUM_LOCAL , NULL, 2, (LPBYTE) ppinfo2, dwNeeded, &dwNeeded, &dwReturned);
			if(!bErr)
			{
				MessageBox(HWND_DESKTOP, _T("Enumerating Printers Failed") , _T("Change Default Printer"), MB_OK);
				return FALSE;
			}
			_stprintf(tmpPrinter, "%s,%s,%s", ppinfo2[iMenuItemSelected].pPrinterName, ppinfo2[iMenuItemSelected].pDriverName, ppinfo2[iMenuItemSelected].pPortName);
			WriteProfileString(_T("windows"), _T("device"), tmpPrinter);
			tempretn = SendMessageTimeout(HWND_BROADCAST, WM_WININICHANGE, 0L, (LPARAM)(LPCTSTR) _T("windows"), SMTO_NORMAL, 1000, NULL);
			//HeapFree( GetProcessHeap(), 0, ppinfo2 ); 
			free(ppinfo2);
			
		}
		
	}
	/* Modification 02/24/1999 to check the 
	Networked connections for Windows NT */
	else if (osver==cWinNT)
	{
		iMenuItemSelected=iMenuItemSelected+MENU_OFFSET;
		
		infobuff = malloc(255);
		GetMenuString(hMenu, iMenuItemSelected, infobuff, 255, MF_BYCOMMAND);
		
		tempretn = RegOpenKeyEx(HKEY_CURRENT_USER,  // handle of open key 
			_T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Devices"), // address of name of subkey to open 
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
		
		//lpMappedPort = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, lpcbData);
		lpMappedPort = malloc(lpcbData);
		
		tempretn = RegQueryValueEx(hKey, // handle of key to query 
			infobuff, // address of name of value to query 
			NULL,  // reserved 
			NULL, // address of buffer for value type 
			lpMappedPort,  // address of data buffer 
			&lpcbData  // address of data buffer size 
			); 
		
		RegCloseKey(hKey);
		
		_stprintf(tmpPrinter, "%s,%s", infobuff, lpMappedPort);
		//HeapFree( GetProcessHeap(), 0, lpMappedPort); 
		free(infobuff);
		free(lpMappedPort);
		WriteProfileString(_T("windows"), _T("device"), tmpPrinter);
		SendMessageTimeout(HWND_BROADCAST, WM_WININICHANGE, 0L, 0L, SMTO_NORMAL, 1000, NULL);
	}
	
	/* Free the memory that was allocated */
	free(tmpPrinter);
	return 0;
}

