; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=Printers
AppVerName=Printers 1.1
AppPublisher=Timothy Legge
AppPublisherURL=http://printers.sourceforge.net/
AppSupportURL=http://printers.sourceforge.net/
AppUpdatesURL=http://printers.sourceforge.net/
DefaultDirName={pf}\Printers
DefaultGroupName=Printers
AllowNoIcons=yes
AlwaysCreateUninstallIcon=yes
LicenseFile=C:\Printers\Printers1.0\gpl.txt
; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Files]
Source: "C:\Printers\Printers1.0\Release\Printers.exe"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "C:\Printers\Printers1.0\gpl.txt"; DestDir: "{app}"; CopyMode: alwaysoverwrite

[INI]
Filename: "{app}\Printers.url"; Section: "InternetShortcut"; Key: "URL"; String: "http://printers.sourceforge.net/"

[Registry]
Root: HKCU; Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; Flags: uninsdeletevalue; ValueType: string; ValueName: "Printers"; ValueData: "{app}\Printers.exe"

[Icons]
Name: "{group}\Printers"; Filename: "{app}\Printers.exe"
Name: "{group}\Printers on the Web"; Filename: "{app}\Printers.url"

[Run]
Filename: "{app}\Printers.exe"; Description: "Launch Printers"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files; Name: "{app}\Printers.url"

