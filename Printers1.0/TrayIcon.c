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

#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <windowsx.h>	/* Used for GET_WM_COMMAND_ID
							To get the MESSAGE to close
							the about dialog box */
#include <tchar.h>
#include <stdio.h>		/* Defines sprintf function */
#include <string.h>
#include <direct.h>		/* Get the working Directory */

#include "include\resource.h"
#include "include\TrayIcon.h"


#define USECLIPBOARD

LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK HoverTextWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int ShowMenu(HWND hwnd, HMENU hMenu, POINT pt);
BOOL AddTaskBarIcon(HWND hwnd, UINT uID, LPSTR lpszTip) ;
BOOL bFileCreated = FALSE; 


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
TCHAR szClassName[] = TEXT("Printers");	//Class Name
int iNbrMenuItemstoAdd;	// Number of menu items to add
short osver;  // Operating System Version

/* =================================
= Beginning of global variable     =  
= section for variables specific   =
= to each use of application using =
= the TrayIcon menu				   =
 ================================*/
#ifdef USECLIPBOARD
#else
	FILE *fDetails;
#endif

/* ===============================
= End of global variable section =  
= for variables specific		 =
= to each use of application using =
= the TrayIcon menu				   =
 ================================*/


int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	TCHAR pszTip[28] = TEXT("Change Default Printer");// Tooltip displayed over Icon
	
	MSG msg;					// Message to be used in main message loop
	HWND hwnd;					// Handle to the Window
	WNDCLASSEX wcl;				// Structure for the Window class information
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
	

//	InitCommonControls();  /* Not needed? */
	
	/*	Set the information for the
	Window Class Structure */
	wcl.cbSize   = sizeof(WNDCLASSEX);
	wcl.style = CS_HREDRAW | CS_VREDRAW ;
	wcl.lpfnWndProc = WindowFunc;		// Name of Call Back Window Function
	wcl.cbClsExtra = 0;					
	wcl.cbWndExtra = 0;
	wcl.hInstance = hThisInst;			// Instance Handle
	wcl.hIcon = NULL;					// No Icon for the Window
	wcl.hCursor = NULL;					// No Cursor for the Window
	wcl.hbrBackground = NULL;	
	wcl.lpszMenuName = NULL;			// No Main Menu	
	wcl.lpszClassName = szClassName;	// Class Name
	wcl.hIconSm = NULL;

	if(!RegisterClassEx (&wcl)) return 0;	// Register Window Class
	
/*-----------------------------
HoverText based on code from 
Philip Jones (found via google)
used with permission 
-------------------------------*/
	// create custom window class for hover buttons in dialog
	wcl.cbSize		= sizeof(WNDCLASSEX);
	wcl.style       = CS_HREDRAW | CS_VREDRAW ;
	wcl.lpfnWndProc = HoverTextWndProc ;
	wcl.cbClsExtra  = wcl.cbWndExtra = 0 ;
	wcl.hInstance   = hThisInst;
	wcl.hIcon       = NULL ;
	wcl.hCursor     = LoadCursor(hThisInst, IDC_HAND); 
	if(wcl.hCursor == NULL)
		wcl.hCursor = LoadImage (hThisInst, MAKEINTRESOURCE(IDC_LINK),IMAGE_CURSOR, 		   0, 0, LR_DEFAULTSIZE); 
	wcl.hbrBackground = (HBRUSH) GetSysColorBrush(COLOR_BTNFACE) ;
	wcl.lpszMenuName  = NULL ;
	wcl.lpszClassName = TEXT ("HoverText") ;
	wcl.hIconSm   = NULL;

	if(!RegisterClassEx (&wcl)) return 0;


/*-----------------------------
End HoverText based on code from 
Philip Jones (found via google)
used with permission 
-------------------------------*/
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
	TCHAR pszTip[28] = TEXT("Change Default Printer");// Tooltip displayed over Icon
	static UINT s_uTaskbarRestart;
	TCHAR DefaultPrinter[255];
	
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

			DialogBox(ghThisInst, MAKEINTRESOURCE(IDD_DIALOG), hwnd, AboutProc);
			return 0;
			
		default:
		/* The default section is executed when one of the 
		other menu selections is selected 
			That is, not Exit or About */
			
			result = MenuItemClicked((UINT) LOWORD (wParam), hMenu);
			
			if(result != 0)
				MessageBox(
				HWND_DESKTOP,
				TEXT("Error clicking menu item\nReport to tlegge@fundy.net\n(ModifyINI)"),
				TEXT("Printers"), MB_OK);
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
		
		case WM_WININICHANGE:
			/* Get the current Default Printer 
			to update the Tool Tip */

			/* Get the name of the Default Printer */
			GetProfileString(TEXT("windows"), TEXT("device"), TEXT(",,,"), DefaultPrinter, sizeof(DefaultPrinter));
 			_stprintf(DefaultPrinter, TEXT("%s"), _tcstok(DefaultPrinter, TEXT(",")));

			/* Display the default printer in the tooltip */
				if (DefaultPrinter)
					lstrcpyn(tnd.szTip, DefaultPrinter, sizeof(tnd.szTip));
				else 
					lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
	
				Shell_NotifyIcon(NIM_MODIFY, &tnd); 
			break;
		case WM_DESTROY:
			// If icon exists destroy it
			if(hIcon)	
			{
				Shell_NotifyIcon(NIM_DELETE, &tnd);
				DestroyMenu(hMenu);
				DestroyIcon(hIcon);
			}
			break;
		case WM_QUIT:
			// If icon exists destroy it
			if(hIcon)	
			{
				Shell_NotifyIcon(NIM_DELETE, &tnd);
				DestroyMenu(hMenu);
				DestroyIcon(hIcon);
			}
			break;

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

LPTSTR tmpFileName;	 

BOOL CALLBACK AboutProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	#define maxbuf 907
	TCHAR buffer[_MAX_PATH];
	HINSTANCE hInst=0;
	int ibuflen;
	TCHAR cDetails[maxbuf]="";

#ifdef USECLIPBOARD
	HGLOBAL      hGlobal ;
	PTSTR        pGlobal ;
	LPTSTR lpClassName = "";
//	LPTSTR lpWPClassName = "RichEdit20A";
	LPTSTR lpWPClassName = "Edit";
	HWND hWnd;
	HWND hChildWnd;
#else
	WIN32_FIND_DATA lpFindFileData;
	HANDLE hFile;
	DWORD lpNumberOfBytesWritten;
#endif

	int count=0;


	switch(uMsg)
	{
		case WM_COMMAND:
			switch(GET_WM_COMMAND_ID(wParam, lParam))
				{
					case IDOK:
#ifdef USECLIPBOARD
#else

						if(bFileCreated){ 
							HANDLE hFile;
							hFile = FindFirstFile(tmpFileName,  // pointer to name of file to search for 
								&lpFindFileData  // pointer to returned information 
								); 
 
							if(hFile){
								CloseHandle (hFile);
								if(DeleteFile(tmpFileName));
									bFileCreated = FALSE; 
							}
						}
#endif
						free(tmpFileName);
						EndDialog(hDlg, TRUE);
					break;
					
					case IDC_DETAILS:

						ibuflen = LoadString(ghThisInst, IDS_DETAILS, cDetails, maxbuf);
						
#ifdef USECLIPBOARD
						hGlobal = GlobalAlloc(
							GHND | GMEM_SHARE, 
							(ibuflen + 1) * sizeof (char));
						pGlobal = GlobalLock (hGlobal) ;
						lstrcpy (pGlobal, cDetails) ;
						GlobalUnlock (hGlobal) ;
						OpenClipboard(hDlg);
						EmptyClipboard();
						SetClipboardData (CF_TEXT, hGlobal) ;
						CloseClipboard();
						GlobalFree(hGlobal); // handle to the global memory object 

						// Open the file
						if(!(hInst = ShellExecute(
							hDlg,  // handle to parent window 
							TEXT("open"),  // pointer to string that specifies operation to perform 
							//"C:\\Program Files\\Accessories\\WORDPAD.EXE",  // pointer to filename or folder name string 
							TEXT("notepad.exe"),
							NULL,  // pointer to string that specifies executable-file parameters 
							buffer,  // pointer to string that specifies default directory 
							SW_SHOWDEFAULT  // whether file is shown when opened 
						)))
						{
							MessageBox(
								HWND_DESKTOP,
								TEXT("Unable to find NotePad"),
								TEXT("Printers"), MB_OK);
							return FALSE;
						}
						

						while((hWnd = FindWindow(NULL, TEXT("Untitled - Notepad")))==NULL)
							;
						/*while((hWnd = FindWindow(NULL, "Document - Wordpad"))==NULL)
							;*/
						
						hChildWnd = GetWindow(hWnd,  // handle of original window 
								GW_CHILD // relationship flag  
							); 

						while(_tcscmp(lpWPClassName, lpClassName) !=0)
						{

							GetClassName(hChildWnd,  // handle of window 
								lpClassName, // address of buffer for class name 
								125 // size of buffer, in characters 
							); 				
							if(_tcscmp(lpWPClassName, lpClassName) !=0)
								hChildWnd = GetNextWindow(hChildWnd,  // handle of original window 
									GW_HWNDNEXT // relationship flag  
								); 

						}

						SendMessage(hChildWnd,  // handle of destination window 
							WM_PASTE,  // message to send 
							0, // first message parameter 
							0  // second message parameter 
							);
#else
						if(bFileCreated)
							DeleteFile(tmpFileName);
						else
							 tmpFileName = malloc(260);
						
						/* Display the Readme */
						_getcwd( buffer, _MAX_PATH ); // Get Current Directory
						
						// Create the File Name
						_stprintf(tmpFileName, "%s\\%s%s", buffer, ReadMeFileName,ReadMeFileNameExt);
						//lpFileName = tmpFileName;
						
						while((
							hFile = CreateFile(tmpFileName, // pointer to name of the file 
								GENERIC_WRITE ,  // access (read-write) mode 
								FILE_SHARE_WRITE ,  // share mode 
								NULL,  // pointer to security attributes 
								CREATE_NEW,  // how to create 
								FILE_ATTRIBUTE_NORMAL,  // file attributes 
								NULL  // handle to file with attributes to copy 
							))==INVALID_HANDLE_VALUE)
						{
							_stprintf(tmpFileName, "%s\\%s%i%s", buffer, ReadMeFileName, count, ReadMeFileNameExt);
							count++;
						}

						WriteFile(hFile,  // handle to file to write to 
							 cDetails,  // pointer to data to write to file 
							 ibuflen, // number of bytes to write 
							 &lpNumberOfBytesWritten,  // pointer to number of bytes written 
							 NULL  // pointer to structure needed for overlapped I/O 
							); 

						CloseHandle (hFile);
					
						// Open the file
						hInst = ShellExecute(
							hDlg,  // handle to parent window 
							"open",  // pointer to string that specifies operation to perform 
							tmpFileName,  // pointer to filename or folder name string 
							NULL,  // pointer to string that specifies executable-file parameters 
							buffer,  // pointer to string that specifies default directory 
							SW_SHOWDEFAULT  // whether file is shown when opened 
						);
						bFileCreated = TRUE; 
#endif

					break;
				}
		break;
	}
	return FALSE;
	
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
	TCHAR DefaultPrinter[255];
	
    tnd.cbSize = sizeof(NOTIFYICONDATA); 
    tnd.hWnd = hwnd; 
    tnd.uID = uID; 
    tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
    tnd.uCallbackMessage = MYWM_NOTIFYICON; 
    tnd.hIcon = hIcon; 

	/* Get the name of the Default Printer */
	GetProfileString(TEXT("windows"), TEXT("device"), TEXT(",,,"), DefaultPrinter, sizeof(DefaultPrinter));
 	_stprintf(DefaultPrinter, "%s", _tcstok(DefaultPrinter, TEXT(",")));

	/* Display the default printer in the tooltip */
	if (DefaultPrinter)
		lstrcpyn(tnd.szTip, DefaultPrinter, sizeof(tnd.szTip));
	else if(lpszTip) 
        lstrcpyn(tnd.szTip, lpszTip, sizeof(tnd.szTip)); 
    else 
        tnd.szTip[0] = _T('\0'); 
	
    res = Shell_NotifyIcon(NIM_ADD, &tnd); 
	
    if (hIcon) 
        DestroyIcon(hIcon); 
	
    return res; 
} 

/*-----------------------------
HoverText based on code from 
Philip Jones (found via google)
used with permission 
-------------------------------*/
LRESULT CALLBACK HoverTextWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR  szText[95] = "";
	TCHAR  szMailTo[95] = "";
	TCHAR  szSubject[95];
	TCHAR  szWeb[95];
	TCHAR  szFTP[95];
	HDC         hdc ;
	PAINTSTRUCT ps ;
	RECT        rect ;
	static  HFONT hFont;
	HINSTANCE hInst;



	TRACKMOUSEEVENT tme;
	static BOOL  InWindow = FALSE;
	int i;

	switch (message)
	{
		case WM_CREATE:


			hFont = CreateFont (14, 0, 0, 0, FW_NORMAL, 0, 1, 0,
				   ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				   CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				   FF_SWISS, TEXT("MS Sans Serif"));

			return 0;

		case WM_DESTROY:
			  DeleteObject (hFont);
			  return 0;

		case WM_MOUSEMOVE:
			if (!InWindow)
			{
					InWindow = TRUE;
					InvalidateRect(hwnd, NULL, TRUE);
					tme.cbSize = sizeof(TRACKMOUSEEVENT);
					tme.dwFlags = TME_LEAVE;
					tme.hwndTrack = hwnd;
					TrackMouseEvent(&tme);
			}
			break;

		case WM_MOUSELEAVE:
			  InWindow = FALSE;
			  InvalidateRect(hwnd, NULL, TRUE);
			  break;

		case WM_PAINT :
			GetClientRect (hwnd, &rect) ;
			GetWindowText (hwnd, szText, sizeof (szText)) ;

			hdc = BeginPaint (hwnd, &ps) ;

			SetBkColor (hdc, GetSysColor (COLOR_BTNFACE)) ;

			if (InWindow)
			SetTextColor (hdc, RGB(255,0,0)) ;  // red, underlined
			else
			SetTextColor (hdc, RGB(0,0,255)) ;  // blue, underlined

			SelectObject(hdc, hFont);
			DrawText (hdc, szText, -1, &rect, DT_SINGLELINE | DT_LEFT | DT_VCENTER) ;

			EndPaint (hwnd, &ps) ;
			return 0 ;

		case WM_LBUTTONDOWN :
			GetWindowText(hwnd, szText, sizeof (szText));

			//see if link is web ("http://" or "www."), ftp (ftp://), email ("mailto:")
			i = _tcslen(szText);
			if (i)
			{
				
				if (_tcsstr(szText, TEXT("@")))   // email address
				{
					_tcscpy(szMailTo, TEXT("mailto:"));
					_tcscat(szMailTo, szText);
					_tcscpy(szSubject, TEXT("&Subject="));
					GetWindowText(GetParent(hwnd), &szSubject[9], sizeof (szText));
					_tcscat(szMailTo, szSubject);
					ShellExecute (NULL, NULL, _T(szMailTo), NULL, NULL, SW_SHOWNORMAL);
				}
				else if (_tcsstr(szText, TEXT("ftp."))) // ftp site
				{
					_tcscpy(szFTP,  TEXT("ftp://"));
					_tcscat(szFTP, szText);
					ShellExecute (NULL, NULL, _T(szFTP), NULL, NULL, SW_SHOWNORMAL);
				}
				else if (szText[0] == 'w')  // web site without http://
				{
					_tcscpy(szWeb,  TEXT("http://"));
					_tcscat(szWeb, szText);
					ShellExecute (NULL, NULL, _T(szWeb), NULL, NULL, SW_SHOWNORMAL);
				} 
				else       // web site with http://
					hInst = ShellExecute (hwnd, NULL, _T((szText)), NULL, NULL, SW_SHOWNORMAL);
		
			} 
		  return 0 ;

	} 

return DefWindowProc (hwnd, message, wParam, lParam) ;
}