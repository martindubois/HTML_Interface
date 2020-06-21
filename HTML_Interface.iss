
; Author    KMS - Martin Dubois, P.Eng.
; Copyright (C) 2020 KMS. All rights reserved.
; License   http://www.apache.org/licenses/LICENSE-2.0
; Product   HTML_Interface
; File      HTML_Interface.iss

[Setup]
AllowNetworkDrive=no
AllowUNCPath=no
AppCopyright=Copyright (C) 2020 KMS.
AppName=HTML_Interface
AppPublisher=KMS
AppPublisherURL=http://www.kms-quebec.com
AppSupportURL=http://www.kms-quebec.com
AppVersion=0.0.23
ArchitecturesAllowed=x64 x86
ArchitecturesInstallIn64BitMode=x64
DefaultDirName={pf}\HTML_Interface
LicenseFile=License.txt
MinVersion=10.0
OutputBaseFilename=HTML-Interface_0.0.23
OutputDir=Installer

[Files]
Source: "_DocUser\HTML_Interface.ReadMe.txt"            ; DestDir: "{app}"; Flags: isreadme
Source: "Debug\GenDoc.exe"                              ; DestDir: "{app}\Binairies\Debug_32"
Source: "Debug\HILib.lib"                               ; DestDir: "{app}\Libraries\Debug_32"
Source: "Debug\HILib.pdb"                               ; DestDir: "{app}\Libraries\Debug_32"
Source: "DoxyFile_en.txt"                               ; DestDir: "{app}"
Source: "HILib\_DocUser\HTML_Interface.HILib.ReadMe.txt"; DestDir: "{app}"
Source: "Import\Binaries\Release_32\KmsCopy.exe"        ; DestDir: "{app}"
Source: "Import\KmsBase.ReadMe.txt"                     ; DestDir: "{app}"
Source: "Includes\HI\Browser.h"                         ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\CSS_Colors.h"                      ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\CSS_Document.h"                    ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\Diagram.h"                         ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\Document.h"                        ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\HTML_Document.h"                   ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\JS_Document.h"                     ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\Line.h"                            ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\Link.h"                            ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\LinkList.h"                        ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\Point.h"                           ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\Server.h"                          ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\Shape.h"                           ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\ShapeList.h"                       ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\SVG_Document.h"                    ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\Types.h"                           ; DestDir: "{app}\Includes\HI"
Source: "Includes\HI\XML_Document.h"                    ; DestDir: "{app}\Includes\HI"
Source: "Release\GenDoc.exe"                            ; DestDir: "{app}"
Source: "Release\GenDoc.exe"                            ; DestDir: "{app}\Binaries\Release_32"
Source: "Release\HILib.lib"                             ; DestDir: "{app}\Libraries\Release_32"
Source: "RunDoxygen.cmd"                                ; DestDir: "{app}"
Source: "Scripts\Import.cmd"                            ; DestDir: "{app}"
Source: "Scripts\Import.cmd.txt"                        ; DestDir: "{app}"
Source: "Scripts\Import.txt"                            ; DestDir: "{app}"
Source: "Static\ErrorNotFound.html"                     ; DestDir: "{app}\Static"
Source: "Static\favicon.ico"                            ; DestDir: "{app}\Static"
Source: "x64\Debug\GenDoc.exe"                          ; DestDir: "{app}\Binaries\Debug_64"
Source: "x64\Debug\HILib.lib"                           ; DestDir: "{app}\Libraries\Debug_64"
Source: "x64\Debug\HILib.pdb"                           ; DestDir: "{app}\Libraries\Debug_64"
Source: "x64\Release\GenDoc.exe"                        ; DestDir: "{app}\Binaries\Release_64"
Source: "x64\Release\HILib.lib"                         ; DestDir: "{app}\Libraries\Release_64"
