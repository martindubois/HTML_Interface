@echo off

rem Author    KMS - Martin Dubois, P.Eng.
rem Copyright (C) 2020 KMS. All rights reserved.
rem	Product   HTML_Interface
rem	File      Import.cmd
rem	Usage     .\Import.cmd

echo Executing  Import.cmd  ...

rem ===== Configuration =====================================================

set EXPORT_FOLDER=K:\Export

rem ===== Dependencies ======================================================

set KMS_BASE="%EXPORT_FOLDER%\KmsBase\3.0.30_Windows"

if not exist %EXPORT_FOLDER% set KMS_BASE="C:\Program Files\KmsBase"

rem ===== Constants =========================================================

set DST_FOLDER="%CD%\Import"

rem ===== Verification ======================================================

if not exist %KMS_BASE% (
	echo FATAL ERROR   %KMS_BASE%  does not exist
	pause
	exit /B 10
)

rem ===== Execution =========================================================

if not exist %DST_FOLDER%  mkdir %DST_FOLDER%

pushd  %KMS_BASE%
    call Import.cmd %DST_FOLDER%
popd

if ERRORLEVEL 1 (
	echo ERROR  call Import.cmd %DST_FOLDER%  reported an error - %ERRORLEVEL%
	pause
	exit /B 20
)

rem ===== Fin ===============================================================

echo OK
