; offlineshop.nsi
!include "MUI2.nsh"

; -------------------------------
; Start
!define /file VERSION "version.txt"
!define /file ARCH "arch.txt"
!define company "AbyleDotOrg"
!define icon "offlineshop.ico"
!define MUI_PRODUCT "offlineshop"
!define MUI_FILE "offlineshop"
!define MUI_VERSION ${VERSION}
!define MUI_BRANDINGTEXT "offlineshop"

CRCCheck On

; The name of the installer
Name "offlineshop"

; The file to write
OutFile "offlineshop-${VERSION}-core-${ARCH}-installer.exe"

!define MUI_ICON "offlineshop.ico"
!define MUI_UNICON "offlineshop.ico"

; The default installation directory
InstallDir $PROGRAMFILES\offlineshop

!insertmacro MUI_LANGUAGE "English"
;--------------------------------


; Pages
Page directory
Page components
Page instfiles


!include "Sections.nsh"


Function .onInit

Execwait '"$SYSDIR\taskkill.exe" /F /IM offlineshop.exe /T'


FunctionEnd



; The stuff to install
Section "offlineshop" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR



  ; Put file there
   File /r /x *.txt /x *.bat *.*

        ;create desktop shortcut
        CreateShortCut "$DESKTOP\${MUI_PRODUCT}.lnk" "$INSTDIR\${MUI_FILE}.exe" ""


         WriteUninstaller "$INSTDIR\Uninstall.exe"

         ;write uninstall information to the registry
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" "DisplayName" "${MUI_PRODUCT} (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" "UninstallString" "$INSTDIR\Uninstall.exe"

SectionEnd ; end the section





;--------------------------------
;Uninstaller Section
Section "Uninstall"

;Delete Files
  RMDir /r "$INSTDIR\*.*"

;Remove the installation directory
  RMDir "$INSTDIR"

;Delete Start Menu Shortcuts
  Delete "$DESKTOP\offlineshop.lnk"


;Delete Uninstaller And Unistall Registry Entries
  DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\${MUI_PRODUCT}"
  DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}"

SectionEnd
