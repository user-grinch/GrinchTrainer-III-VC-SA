; Based on Seeman's CLEORedux Installer 
; https://github.com/cleolibrary/CLEO-Redux

#define AppName "Grinch Trainer"
#define AppVersion "1.0"
#define AppPublisher "Grinch_"
#define AppURL "https://github.com/user-grinch/GrinchTrainer-III-VC-SA"
#define OutputDir "."

#define GrinchTrainerLocalFolder="GrinchTrainerLocal"
#define UAL32="path\to\UAL32.zip"
#define D3D8to9Wrapper="path\to\d3d8.zip"
#define SilentPatchIII="path\to\SilentPatchIII.zip"
#define SilentPatchVC="path\to\SilentPatchVC.zip"
#define SilentPatchSA="path\to\SilentPatchSA.zip"
#define Redist="path\to\vc_redist.x86.exe"
#define DX9="path\to\dxwebsetup.exe"

[Setup]
AppId={{511AFCDA-FD5E-491C-A1B7-22BAC8F93711}}
AppName={#AppName}
AppVersion={#AppVersion}
AppVerName={#AppName} {#AppVersion} by {#AppPublisher}
AppPublisher={#AppPublisher}
AppPublisherURL={#AppURL}
AppCopyright=Copyright (c) 2019-2025, {#AppPublisher}
DefaultDirName=New folder
LicenseFile=../LICENSE
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
;PrivilegesRequiredOverridesAllowed=dialog
OutputDir={#OutputDir}
OutputBaseFilename=Installer
;SetupIconFile=cr4.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern
AppendDefaultDirName=false
DirExistsWarning=false
EnableDirDoesntExistWarning=true
UsePreviousAppDir=no
Uninstallable=false

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Types]
Name: "full"; Description: "Full"; Flags: iscustom

[Components]
Name: "program"; Description: "Grinch Trainer"; Types: full; Flags: fixed
Name: "plugins"; Description: "Prerequisites"; Types: full
Name: "plugins/d3d8to9"; Description: "d3d8to9 Wrapper - needed for III & VC"; Types: full; Flags: fixed
Name: "plugins/SilentPatch"; Description: "SilentPatch - needed for the mouse to work properly"; Types: full
Name: "plugins/asiloader"; Description: "Ultimate ASI Loader (by ThirteenAG)"; Types: full
Name: "plugins/redist"; Description: "Visual C++ Redistributable 2022 x86"; Types: full
Name: "plugins/dx9"; Description: "DirectX End-User Runtime Version 9.0"; Types: full

[Dirs]
Name: "{app}"; Permissions: users-modify
Name: "{app}\GrinchTrainerSA"; Check: IsSA; Permissions: users-modify
Name: "{app}\GrinchTrainerVC"; Check: IsVC; Permissions: users-modify
Name: "{app}\GrinchTrainerIII"; Check: IsIII; Permissions: users-modify

[Files]
Source: "{#GrinchTrainerLocalFolder}\GrinchTrainerSA.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: IsSA; AfterInstall: ExtractAll('{app}\GrinchTrainerSA.zip', '{app}'); Components: program;
Source: "{#GrinchTrainerLocalFolder}\GrinchTrainerVC.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: IsVC; AfterInstall: ExtractAll('{app}\GrinchTrainerVC.zip', '{app}'); Components: program;
Source: "{#GrinchTrainerLocalFolder}\GrinchTrainerIII.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: IsIII; AfterInstall: ExtractAll('{app}\GrinchTrainerIII.zip', '{app}'); Components: program;
Source: "{#UAL32}"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: WizardIsComponentSelected('plugins/asiloader'); AfterInstall: Extract('{app}\UAL32', 'dinput8.dll', '{app}'); Components: plugins/asiloader;
Source: "{#D3D8to9Wrapper}"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: WizardIsComponentSelected('plugins/d3d8to9'); AfterInstall: Extract('{app}\d3d8.zip', 'd3d8.dll', '{app}'); Components: plugins/d3d8to9;
Source: "{#SilentPatchIII}"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: IsSA; AfterInstall: ExtractAll('{app}\SilentPatchIII.zip', '{app}'); Components: plugins/SilentPatch;
Source: "{#SilentPatchVC}"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: IsVC; AfterInstall: ExtractAll('{app}\SilentPatchVC.zip', '{app}'); Components: plugins/SilentPatch;
Source: "{#SilentPatchSA}"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: IsSA; AfterInstall: ExtractAll('{app}\SilentPatchSA.zip', '{app}'); Components: plugins/SilentPatch;
Source: "{#Redist}"; DestDir: "{app}"; Flags: deleteafterinstall external; Components: plugins/redist;
Source: "{#DX9}"; DestDir: "{app}"; Flags: deleteafterinstall external; Components: plugins/dx9;

[Run]
Filename: "{#Redist}"; StatusMsg: "Installing Visual C++ Redistributable 2022 x86"; Check: WizardIsComponentSelected('plugins/redist'); Parameters: "/quiet"; Flags: waituntilterminated
Filename: "{#DX9}"; StatusMsg: "Installing DirectX End-User Runtime"; Check: WizardIsComponentSelected('plugins/dx9'); Flags: waituntilterminated

[InstallDelete]
Name: "{app}\Scripts\Globals.ini"; Type: files

[Code]
const
  SHCONTCH_NOPROGRESSBOX = 4;
  SHCONTCH_RESPONDYESTOALL = 16;

type
  eGameVer = (GTA_III, GTA_VC, GTA_SA, UNKNOWN);

var
  GameId: eGameVer;
  DownloadPage: TDownloadWizardPage;
  DefaultDirOnce: Boolean;

function IsSA(): Boolean;
begin
  Result := GameId = GTA_SA;
end;

function IsVC(): Boolean;
begin
  Result := GameId = GTA_VC;
end;

function IsIII(): Boolean;
begin
  Result := GameId = GTA_III;
end;

procedure unzipFile(Src, FileName, TargetFldr: PAnsiChar);
var
  Shell: variant;
  Item: variant;
  SrcFldr, DestFldr: variant;
begin
  if FileExists(Src) then 
  begin
    ForceDirectories(TargetFldr);

    Shell := CreateOleObject('Shell.Application');

    SrcFldr := Shell.NameSpace(string(Src));
    DestFldr := Shell.NameSpace(string(TargetFldr));
    Item := SrcFldr.ParseName(FileName);

    if not VarIsClear(Item) then
      DestFldr.CopyHere(Item, SHCONTCH_NOPROGRESSBOX or SHCONTCH_RESPONDYESTOALL);
 
  end;
end;

procedure unzipFolder(Src, TargetFldr: PAnsiChar);
var
  Shell: variant;
  SrcFldr, DestFldr: variant;
begin
  if FileExists(Src) then 
  begin
    ForceDirectories(TargetFldr);

    Shell := CreateOleObject('Shell.Application');

    SrcFldr := Shell.NameSpace(string(Src));
    DestFldr := Shell.NameSpace(string(TargetFldr));
    
    DestFldr.CopyHere(SrcFldr.Items, SHCONTCH_NOPROGRESSBOX or SHCONTCH_RESPONDYESTOALL);
 
  end;
end;

procedure Extract(Src, FileName, Target : String);
begin
  unzipFile(ExpandConstant(Src), ExpandConstant(FileName), ExpandConstant(target));
end;

procedure ExtractAll(Src, Target : String);
begin
  unzipFolder(ExpandConstant(Src), ExpandConstant(target));
end;

function GetSilentPatchName(): String;
begin
  if GameId = GTA_III then 
    Result := 'SilentPatchIII.asi'
  else if GameId = GTA_VC then 
    Result := 'SilentPatchVC.asi'
  else if GameId = GTA_SA then 
    Result := 'SilentPatchSA.asi';
end;

function IdentifyGame(Dir: String): eGameVer;
begin
  if FileExists(Dir + '\gta3.exe') then
  begin
    Result := GTA_III;
    Exit;
  end;
  if FileExists(Dir + '\gta-vc.exe') then
  begin
    Result := GTA_VC;
    Exit;
  end;
  if FileExists(Dir + '\gta_sa.exe') or FileExists(Dir + '\gta-sa.exe') or FileExists(Dir + '\GTA_SA.exe') then
  begin
    Result := GTA_SA;
    Exit;
  end;
  Result := UNKNOWN;
end;

procedure InitializeSetup();
begin
  GameId := IdentifyGame(ExpandConstant('{pf}\Rockstar Games\Grand Theft Auto III'));
  if GameId = UNKNOWN then
  begin
    DownloadPage := CreateInputOptionPage(wpSelectDir,
      'Game Version Selection',
      'Please select your game version',
      'Select the version of GTA that you are installing the trainer for:',
      False, True);
      
    DownloadPage.Add('GTA III');
    DownloadPage.Add('GTA VC');
    DownloadPage.Add('GTA SA');
    DownloadPage.OnChange := @OnDownloadPageChange;
  end;
end;

procedure OnDownloadPageChange(Sender: TObject);
begin
  if DownloadPage.SelectedValue = 'GTA III' then
    GameId := GTA_III
  else if DownloadPage.SelectedValue = 'GTA VC' then
    GameId := GTA_VC
  else if DownloadPage.SelectedValue = 'GTA SA' then
    GameId := GTA_SA;

  if GameId <> UNKNOWN then
    DownloadPage.Visible := False;
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssInstall then
  begin
    if GameId = UNKNOWN then
      MsgBox('Could not find a compatible game installation. Please check the selected game directory.', mbError, MB_OK);
    
    if IsSA then
    begin
      ExtractAll(ExpandConstant('{app}\GrinchTrainerSA.zip'), ExpandConstant('{app}'));
    end
    else if IsVC then
    begin
      ExtractAll(ExpandConstant('{app}\GrinchTrainerVC.zip'), ExpandConstant('{app}'));
    end
    else if IsIII then
    begin
      ExtractAll(ExpandConstant('{app}\GrinchTrainerIII.zip'), ExpandConstant('{app}'));
    end;
    
  end;
end;
