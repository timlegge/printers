# Microsoft Developer Studio Generated NMAKE File, Based on Printers.dsp
!IF "$(CFG)" == ""
CFG=Printers - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Printers - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Printers - Win32 Release" && "$(CFG)" !=\
 "Printers - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Printers.mak" CFG="Printers - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Printers - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Printers - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Printers - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Printers.exe"

!ELSE 

ALL : "$(OUTDIR)\Printers.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AddMenuItems.obj"
	-@erase "$(INTDIR)\MenuItemClicked.obj"
	-@erase "$(INTDIR)\TrayIcon.obj"
	-@erase "$(INTDIR)\trayicon.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Printers.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\Printers.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\trayicon.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Printers.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib uuid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\Printers.pdb" /machine:I386 /out:"$(OUTDIR)\Printers.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AddMenuItems.obj" \
	"$(INTDIR)\MenuItemClicked.obj" \
	"$(INTDIR)\TrayIcon.obj" \
	"$(INTDIR)\trayicon.res"

"$(OUTDIR)\Printers.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Printers - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Printers.exe" "$(OUTDIR)\Printers.bsc"

!ELSE 

ALL : "$(OUTDIR)\Printers.exe" "$(OUTDIR)\Printers.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AddMenuItems.obj"
	-@erase "$(INTDIR)\AddMenuItems.sbr"
	-@erase "$(INTDIR)\MenuItemClicked.obj"
	-@erase "$(INTDIR)\MenuItemClicked.sbr"
	-@erase "$(INTDIR)\TrayIcon.obj"
	-@erase "$(INTDIR)\trayicon.res"
	-@erase "$(INTDIR)\TrayIcon.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Printers.bsc"
	-@erase "$(OUTDIR)\Printers.exe"
	-@erase "$(OUTDIR)\Printers.ilk"
	-@erase "$(OUTDIR)\Printers.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Printers.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\trayicon.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Printers.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AddMenuItems.sbr" \
	"$(INTDIR)\MenuItemClicked.sbr" \
	"$(INTDIR)\TrayIcon.sbr"

"$(OUTDIR)\Printers.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib uuid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\Printers.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\Printers.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AddMenuItems.obj" \
	"$(INTDIR)\MenuItemClicked.obj" \
	"$(INTDIR)\TrayIcon.obj" \
	"$(INTDIR)\trayicon.res"

"$(OUTDIR)\Printers.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Printers - Win32 Release" || "$(CFG)" ==\
 "Printers - Win32 Debug"
SOURCE=.\AddMenuItems.c
DEP_CPP_ADDME=\
	".\include\trayicon.h"\
	

!IF  "$(CFG)" == "Printers - Win32 Release"


"$(INTDIR)\AddMenuItems.obj" : $(SOURCE) $(DEP_CPP_ADDME) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Printers - Win32 Debug"


"$(INTDIR)\AddMenuItems.obj"	"$(INTDIR)\AddMenuItems.sbr" : $(SOURCE)\
 $(DEP_CPP_ADDME) "$(INTDIR)"


!ENDIF 

SOURCE=.\MenuItemClicked.c
DEP_CPP_MENUI=\
	".\include\trayicon.h"\
	

!IF  "$(CFG)" == "Printers - Win32 Release"


"$(INTDIR)\MenuItemClicked.obj" : $(SOURCE) $(DEP_CPP_MENUI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Printers - Win32 Debug"


"$(INTDIR)\MenuItemClicked.obj"	"$(INTDIR)\MenuItemClicked.sbr" : $(SOURCE)\
 $(DEP_CPP_MENUI) "$(INTDIR)"


!ENDIF 

SOURCE=.\TrayIcon.c
DEP_CPP_TRAYI=\
	".\include\trayicon.h"\
	

!IF  "$(CFG)" == "Printers - Win32 Release"


"$(INTDIR)\TrayIcon.obj" : $(SOURCE) $(DEP_CPP_TRAYI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Printers - Win32 Debug"


"$(INTDIR)\TrayIcon.obj"	"$(INTDIR)\TrayIcon.sbr" : $(SOURCE) $(DEP_CPP_TRAYI)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\trayicon.rc
DEP_RSC_TRAYIC=\
	".\Printers.ico"\
	

"$(INTDIR)\trayicon.res" : $(SOURCE) $(DEP_RSC_TRAYIC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

