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


#define MYWM_NOTIFYICON		(WM_APP+100)
#define MENU_OFFSET	3 // Offset the Exit, About. Separator Menu Items

#define ReadMeFileName	"Readme"   // Extension appended from below
#define ReadMeFileNameExt	".txt"	

#define cWin95 1
#define cWinNT 2
#define cWin98 3

//For those people who do not have the absolutely latest SDK header files
#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649)   // Taken from VC6 WINUSER.H
#endif // IDC_HAND
