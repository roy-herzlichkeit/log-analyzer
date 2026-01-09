; NSIS Installer Script for Log Analyzer CLI
; This is an optional custom NSIS script for additional installer features.
; CPack generates a default script, but this can be used for customizations.

!include "MUI2.nsh"
!include "EnvVarUpdate.nsh"

; Installer attributes
Name "Log Analyzer CLI"
OutFile "loganalyzer-installer.exe"
InstallDir "$PROGRAMFILES\LogAnalyzer"
InstallDirRegKey HKLM "Software\LogAnalyzer" "Install_Dir"
RequestExecutionLevel admin

; Modern UI settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\..\LICENSE.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; Language
!insertmacro MUI_LANGUAGE "English"

; Installer section
Section "Install"
    SetOutPath "$INSTDIR\bin"
    
    ; Copy the executable
    File "..\build\Release\loganalyzer.exe"
    
    ; Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"
    
    ; Registry entries for uninstall
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LogAnalyzer" "DisplayName" "Log Analyzer CLI"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LogAnalyzer" "UninstallString" '"$INSTDIR\Uninstall.exe"'
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LogAnalyzer" "InstallLocation" "$INSTDIR"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LogAnalyzer" "Publisher" "Your Name"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LogAnalyzer" "DisplayVersion" "1.0.0"
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LogAnalyzer" "NoModify" 1
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LogAnalyzer" "NoRepair" 1
    
    ; Add to PATH (requires EnvVarUpdate.nsh)
    ; ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR\bin"
    
SectionEnd

; Uninstaller section
Section "Uninstall"
    ; Remove from PATH
    ; ${un.EnvVarUpdate} $0 "PATH" "R" "HKLM" "$INSTDIR\bin"
    
    ; Remove files
    Delete "$INSTDIR\bin\loganalyzer.exe"
    Delete "$INSTDIR\Uninstall.exe"
    
    ; Remove directories
    RMDir "$INSTDIR\bin"
    RMDir "$INSTDIR"
    
    ; Remove registry keys
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LogAnalyzer"
    DeleteRegKey HKLM "Software\LogAnalyzer"
    
SectionEnd
