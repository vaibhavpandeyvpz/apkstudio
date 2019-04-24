#define DeploymentDir GetEnv("DEPLOYMENT_DIR")

[Files]
Source: "{#DeploymentDir}\*"; DestDir: "{app}"; Flags: recursesubdirs

[Setup]
AppName=WA360
AppVersion=1.0
Compression=lzma2
DefaultDirName="{pf}\VPZ\APK Studio"
DefaultGroupName="VPZ\APK Studio"
SolidCompression=yes
UninstallDisplayIcon="{app}\ApkStudio.exe"

[Run]
Filename: "{app}\ApkStudio.exe"; Description: "Launch APK Studio"; Flags: nowait postinstall runasoriginaluser skipifsilent unchecked

[Icons]
Name: "{userdesktop}\APK Studio"; Filename: "{app}\ApkStudio.exe"
Name: "{group}\APK Studio"; Filename: "{app}\ApkStudio.exe"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"
