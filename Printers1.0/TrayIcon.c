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
#include <windowsx.h>	/* Used for GET_WM_COMMAND_ID
							To get the MESSAGE to close
							the about dialog box */
#include <stdio.h>		/* Defines sprintf function */
#include <string.h>
#include <direct.h>		/* Get the working Directory */
#include "include\resource.h"
#include "include\TrayIcon.h"


LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int ShowMenu(HWND hwnd, HMENU hMenu, POINT pt);
BOOL AddTaskBarIcon(HWND hwnd, UINT uID, LPSTR lpszTip) ;
//BOOL ModifyTaskBarIcon(HWND hwnd, UINT uID, LPSTR lpszTip); 
/* 
Modify the code in the following function to 
add items to the menu
*/
extern int AddItemsToMenu(HMENU hMenu);

/* 
Modify the code in the following function to 
perform an action when the item is clicked
*/
extern int MenuItemClicked(UINT ServerNumber, HMENU hMenu);

HINSTANCE			ghThisInst;		// Global value for this instance of the Application
HICON				hIcon; // Handle to the Tray Icon
NOTIFYICONDATA		tnd; // Structure for the Tray Icon Data
char szClassName[] = "Printers";	//Class Name
int iNbrMenuItemstoAdd;	// Number of menu items to add
short osver;  // Operating System Version

/* =================================
= Beginning of global variable     =  
= section for variables specific   =
= to each use of application using =
= the TrayIcon menu				   =
 ================================*/



/* ===============================
= End of global variable section =  
= for variables specific		 =
= to each use of application using =
= the TrayIcon menu				   =
 ================================*/


int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	char pszTip[28] = "Change Default Printer";// Tooltip displayed over Icon
	
	MSG msg;					// Message to be used in main message loop
	HWND hwnd;					// Handle to the Window
	WNDCLASS wcl;				// Structure for the Window class information
	OSVERSIONINFO		osvinfo;// Get the OS version for NT compatability
	ghThisInst = hThisInst;		// Set global value for this instance of the Application
	
	osvinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
    if(!GetVersionEx(&osvinfo))
        return FALSE;
	if(osvinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		if((osvinfo.dwMajorVersion > 4) || 
			((osvinfo.dwMajorVersion ==4) && (osvinfo.dwMinorVersion >0)))
		{
			osver = cWin98;
		}
		else osver = cWin95;
	}
	else if (osvinfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		osver = cWinNT;
	}
	else
	{
		return 0;
	}
	
	
	
	/*	Set the information for the
	Window Class Structure */
	wcl.hInstance = hThisInst;			// Instance Handle
	wcl.lpszClassName = szClassName;	// Class Name
	wcl.lpfnWndProc = WindowFunc;		// Name of Call Back Window Function
	wcl.style = 0;
	wcl.hIcon = NULL;					// No Icon for the Window
	wcl.hCursor = NULL;					// No Cursor for the Window
	wcl.lpszMenuName = NULL;			// No Main Menu
	wcl.cbClsExtra = 0;					
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = NULL;
	
	if(!RegisterClass (&wcl)) return 0;	// Register Window Class
	
	// Create the window, but do not display it.
	hwnd = CreateWindow(
		szClassName,
		"",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hThisInst,
		NULL);
	
	hIcon = LoadIcon(hThisInst, (const char *) ID_MYICON);	// Load the Icon and get the handle
	
	AddTaskBarIcon(hwnd, IDC_UPDATE, pszTip); 
	
	//Enter main message loop for the application
	
	
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
	}
	
	
	return msg.wParam;
}

LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	HMENU static hMenu;	// Handle to the pop-up menu
	POINT point;	// Point to hold co-ordinate to display menu
	int result;  // Result of calling ModifyINI function
	char pszTip[28] = "Change Default Printer";// Tooltip displayed over Icon
	static UINT s_uTaskbarRestart;
	
	//LPCTSTR tempchar;
	
	switch (message)
	{
	case WM_COMMAND:	// Received when pop-up menu clicked
		
		switch(LOWORD (wParam))	// Menu Item ID
		{
		case IDM_EXIT:	// When Exit Menu Item Clicked
			
			// If icon exists destroy it
			if(hIcon)	
			{
				Shell_NotifyIcon(NIM_DELETE, &tnd);
				DestroyMenu(hMenu);
				DestroyIcon(hIcon);
			}
			// Put end program message on Queue
			PostQuitMessage(0);
			return 0;
			
		case IDM_ABOUT:
			DialogBox(ghThisInst, MAKEINTRESOURCE(IDD_DIALOG), NULL, AboutProc);
			return 0;
			
		default:
		/* The default section is executed when one of the 
		other menu selections is selected 
			That is, not Exit or About */
			
			result = MenuItemClicked((UINT) LOWORD (wParam), hMenu);
			
			if(result != 0)
				MessageBox(
				HWND_DESKTOP,
				"Error clicking menu item\nReport to tlegge@fundy.net\n(ModifyINI)",
				"Printers", MB_OK);
			return 0;
		}
		break;
		
		
		/*	Message received when the
		window is created */
		case WM_CREATE:
			
			hMenu = LoadMenu(ghThisInst, "MENU"); // Load the Pop-up Menu
			hMenu = GetSubMenu(hMenu, 0);
			s_uTaskbarRestart = RegisterWindowMessage(TEXT("TaskbarCreated"));
			break;
			
			/*	Message received when 
			Tray Icon gets focus */
			
		case MYWM_NOTIFYICON:
			switch (lParam)
			{
			/*	Display the Menu When 
			Right or left Button clicked on
				the Icon */
			case WM_RBUTTONDOWN:	
				GetCursorPos(&point);
				result = ShowMenu(hwnd, hMenu, point);
				return 0;
				
			case WM_LBUTTONDOWN:
				GetCursorPos(&point);
				result = ShowMenu(hwnd, hMenu, point);
				return 0;
			}
			return 0;
			default:
				if(message == s_uTaskbarRestart)
				{
					//MessageBox(HWND_DESKTOP, "Explorer crashed redraw icon", "Printers", MB_OK);
					AddTaskBarIcon(hwnd, IDC_UPDATE, pszTip);
				}
				break;
				
	}
	
	return DefWindowProc(hwnd, message, wParam, lParam);
}

int ShowMenu(HWND hwnd, HMENU hMenu, POINT pt)
{
	int  x =0;
	/*	Looper used for Adding 
	and deleting Menu Items */
	
	/*	Loop to delete the Last Menu Items 
	in case it has changed since the 
	Application started */
	
	for(x=0;x<iNbrMenuItemstoAdd;x++)
	{
		DeleteMenu(
			hMenu,  // handle of menu 
			x+MENU_OFFSET,  // menu item that new menu item precedes 
			MF_BYCOMMAND  // menu item flags 
			); 
	}
	
	/*===============================
	= The next line calls a function 
	= to add the new menu items
	= it is specific to each application,
	= but includes 
	= InsertMenu( 
	= 	hMenu,  // handle of menu 
	= 	x,  // menu item that new menu item precedes 
	=	MF_BYPOSITION ,  // menu item flags 
	=	MENU_OFFSET+x,		// Menu ID
	=	ServerName); // menu item identifier or handle of drop-down menu or submenu
	=
	= and 
	= CheckMenuItem(hMenu, MENU_OFFSET+x, MF_CHECKED);
	= 
	=============================*/
	AddItemsToMenu(hMenu);
	
	/* Menu must be refreshed after modifications */
	DrawMenuBar(
		hwnd  // handle to window with menu bar to redraw 
		); 
	
	SetForegroundWindow(hwnd);
	
	/* Display the pop-up menu */
	
	TrackPopupMenu(
		hMenu,	// Menu handle
#if (WINVER >= 0x400)
		TPM_TOPALIGN |
#endif
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,	// Flags as per docs
		pt.x,	// X Co-ordinate
		pt.y, //+ScreenY,
		0, 
		hwnd,	// Parent Window
		NULL);				
	
	PostMessage(hwnd, WM_NULL, 0, 0);
	
	return 0;
}


/*======================================
= AboutProc
=
= Called when the about menu item is
= selected.  It displays an about box
= with choice of:
=		1) <OK> - Closes the Dialog and 
=			deletes the readme if it exists
=		2) <Details> - Creates and opens
=			notepad readme.txt
======================================*/
BOOL CALLBACK AboutProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char static tmpFileName[_MAX_PATH];
	char buffer[_MAX_PATH];
	HINSTANCE hInst=0;
	char cDetails[869]="";
	FILE *fDetails;
	int count=0;
	
	
	switch(uMsg)
	{
	case WM_COMMAND:
		switch(GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			fDetails=fopen(tmpFileName, "w");
			if(fDetails){
				fclose(fDetails);
				DeleteFile(tmpFileName);
			}
			EndDialog(hDlg, TRUE);
			break;
			
		case IDC_DETAILS:
			LoadString(ghThisInst, IDS_DETAILS, cDetails, 869);
			
			/* Display the Readme */
			_getcwd( buffer, _MAX_PATH ); // Get Current Directory
			
			// Create the File Name
			sprintf(tmpFileName, "%s\\%s%s", buffer, ReadMeFileName,ReadMeFileNameExt);
			
			while((fDetails=fopen(tmpFileName, "r+"))!=NULL)
			{
				sprintf(tmpFileName, "%s\\%s%i%s", buffer, ReadMeFileName, count, ReadMeFileNameExt);
				count++;
			}
			
			fDetails=fopen(tmpFileName, "w");
			fwrite( cDetails, sizeof( char ), 869, fDetails );
			fclose(fDetails);
			
			// Open the file
			hInst = ShellExecute(
				hDlg,  // handle to parent window 
				"open",  // pointer to string that specifies operation to perform 
				tmpFileName,  // pointer to filename or folder name string 
				NULL,  // pointer to string that specifies executable-file parameters 
				buffer,  // pointer to string that specifies default directory 
				SW_SHOWDEFAULT  // whether file is shown when opened 
				);
			
			
			break;
		}
		break;
	}
	return 0;
	
}

// MyTaskBarAddIcon - adds an icon to the taskbar status area. 
// Returns TRUE if successful, or FALSE otherwise. 
// hwnd - handle to the window to receive callback messages. 
// uID - identifier of the icon. 
// hicon - handle to the icon to add. 
// lpszTip - tooltip text. 
BOOL AddTaskBarIcon(HWND hwnd, UINT uID, LPSTR lpszTip) 
{ 
    BOOL res; 
		
    tnd.cbSize = sizeof(NOTIFYICONDATA); 
    tnd.hWnd = hwnd; 
    tnd.uID = uID; 
    tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
    tnd.uCallbackMessage = MYWM_NOTIFYICON; 
    tnd.hIcon = hIcon; 
    if (lpszTip) 
        lstrcpyn(tnd.szTip, lpszTip, sizeof(tnd.szTip)); 
    else 
        tnd.szTip[0] = '\0'; 
	
    res = Shell_NotifyIcon(NIM_ADD, &tnd); 
	
    if (hIcon) 
        DestroyIcon(hIcon); 
	
    return res; 
} 

