# Microsoft Developer Studio Generated NMAKE File, Based on TrayIcon.dsp
!IF "$(CFG)" == ""
CFG=TrayIcon - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TrayIcon - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TrayIcon - Win32 Release" && "$(CFG)" !=\
 "TrayIcon - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TrayIcon.mak" CFG="TrayIcon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TrayIcon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TrayIcon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TrayIcon - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TrayIcon.exe"

!ELSE 

ALL : "$(OUTDIR)\TrayIcon.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AddMenuItems.obj"
	-@erase "$(INTDIR)\MenuItemClicked.obj"
	-@erase "$(INTDIR)\TrayIcon.obj"
	-@erase "$(INTDIR)\trayicon.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\TrayIcon.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\TrayIcon.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\trayicon.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TrayIcon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\TrayIcon.pdb" /machine:I386 /out:"$(OUTDIR)\TrayIcon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AddMenuItems.obj" \
	"$(INTDIR)\MenuItemClicked.obj" \
	"$(INTDIR)\TrayIcon.obj" \
	"$(INTDIR)\trayicon.res"

"$(OUTDIR)\TrayIcon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TrayIcon - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TrayIcon.exe"

!ELSE 

ALL : "$(OUTDIR)\TrayIcon.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AddMenuItems.obj"
	-@erase "$(INTDIR)\MenuItemClicked.obj"
	-@erase "$(INTDIR)\TrayIcon.obj"
	-@erase "$(INTDIR)\trayicon.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\TrayIcon.exe"
	-@erase "$(OUTDIR)\TrayIcon.ilk"
	-@erase "$(OUTDIR)\TrayIcon.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\TrayIcon.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\trayicon.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TrayIcon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\TrayIcon.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\TrayIcon.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AddMenuItems.obj" \
	"$(INTDIR)\MenuItemClicked.obj" \
	"$(INTDIR)\TrayIcon.obj" \
	"$(INTDIR)\trayicon.res"

"$(OUTDIR)\TrayIcon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(CFG)" == "TrayIcon - Win32 Release" || "$(CFG)" ==\
 "TrayIcon - Win32 Debug"
SOURCE=.\AddMenuItems.c
DEP_CPP_ADDME=\
	".\include\trayicon.h"\
	

"$(INTDIR)\AddMenuItems.obj" : $(SOURCE) $(DEP_CPP_ADDME) "$(INTDIR)"


SOURCE=.\MenuItemClicked.c
DEP_CPP_MENUI=\
	".\include\Resource.h"\
	

"$(INTDIR)\MenuItemClicked.obj" : $(SOURCE) $(DEP_CPP_MENUI) "$(INTDIR)"


SOURCE=.\TrayIcon.c

!IF  "$(CFG)" == "TrayIcon - Win32 Release"

DEP_CPP_TRAYI=\
	".\include\Resource.h"\
	".\include\trayicon.h"\
	

"$(INTDIR)\TrayIcon.obj" : $(SOURCE) $(DEP_CPP_TRAYI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TrayIcon - Win32 Debug"

DEP_CPP_TRAYI=\
	".\include\Resource.h"\
	".\include\trayicon.h"\
	

"$(INTDIR)\TrayIcon.obj" : $(SOURCE) $(DEP_CPP_TRAYI) "$(INTDIR)"


!ENDIF 

SOURCE=.\trayicon.rc
DEP_RSC_TRAYIC=\
	".\include\Resource.h"\
	".\TrayIcon.ico"\
	

"$(INTDIR)\trayicon.res" : $(SOURCE) $(DEP_RSC_TRAYIC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

