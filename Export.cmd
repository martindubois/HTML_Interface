@echo off

rem Author     KMS - Martin Dubois, P.Eng.
rem Copyright  (C) 2020 KMS. All rights reserved.
rem Product    HTML_Interface
rem File       Export.cmd
rem Usage      .\Export.cmd {Ma.Mi.Bu} [Type]

echo  Executing  Export.cmd %1 %2  ...

rem ===== Initialisation ====================================================

if ""=="%2" (
    set DST="K:\Export\HTML_Interface\%1_Windows"
) else (
    set DST="K:\Export\HTML_Interface\%1_%2_Windows"
)

set EXPORT_TXT="Export.txt"

set EXPORT_CMD_TXT="Export.cmd.txt"

set KMS_COPY="C:\Software\KmsTools\KmsCopy.exe"

rem ===== Verification ======================================================

if ""=="%1" (
    echo USER ERROR  Invalid command line
    echo Usage : Export.cmd {Ma.Mi.Bu} [Internal|RC|Test]
    pause
    exit /B 10
)

if exist %DST% (
    echo USER ERROR  %DST%  already exist
    pause
    exit /B 20
)

if not exist %KMS_COPY% (
    echo FATAL ERROR  %KMS_COPY%  does not exist
    echo Install KmsTools
    pause
    exit /B 30
)

rem ===== Execution =========================================================

%KMS_COPY% . %DST% %EXPORT_TXT%
if ERRORLEVEL 1 (
    echo ERROR  %KMS_COPY% . %DST% %EXPORT_TXT%  failed - %ERRORLEVEL%
    pause
    exit /B 40
)

%KMS_COPY% . %DST% %EXPORT_CMD_TXT%
if ERRORLEVEL 1 (
    echo ERROR  %KMS_COPY% . %DST% %EXPORT_CMD_TXT%  failed - %ERRORLEVEL%
    pause
    exit /B 50
)

rem ===== End ===============================================================

echo OK
