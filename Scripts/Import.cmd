@echo off

rem Author     KMS - Martin Dubois, P.Eng.
rem Copyright  (C) 2020 KMS. All rights reserved.
rem Product    HTML_Interface
rem File       Import.cmd
rem Usage      .\Import.cmd {Destination}

echo Executing  Import.cmd %1  ...

rem ===== Initialisation ====================================================

set KMS_COPY_EXE="KmsCopy.exe"

rem ===== Verification ======================================================

if not exist %1 (
    echo USER ERROR  %1 does not exixt
    pause
    exit /B 10
)

if not exist %KMS_COPY_EXE% (
    echo FATAL ERROR  %KMS_COPY_EXE%  does not exist
	echo Install KmsTools
    pause
    exit /B 20
)

rem ===== Execution =========================================================

%KMS_COPY_EXE% . %1 Import.txt
if ERRORLEVEL 1 (
    echo ERROR  %KMS_COPY_EXE% . %1 Import.txt  failed - %ERRORLEVEL
    pause
    exit /B 30
)

%KMS_COPY_EXE% . %1 Import.cmd.txt
if ERRORLEVEL 1 (
    echo ERROR  %KMS_COPY_EXE% . %1 Import.cmd.txt  failed - %ERRORLEVEL
    pause
    exit /B 40
)

rem ===== End ===============================================================

echo OK
