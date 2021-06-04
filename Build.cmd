@echo off

rem Author    KMS - Martin Dubois, P.Eng.
rem Copyright (C) 2020-2021 KMS. All rights reserved.
rem License   https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
rem Product   HTML_Interface
rem File      Build.cmd
rem Usage     .\Build.cmd

echo Executing  Build.cmd  ...

rem ===== Initialisation ====================================================

set IMPORT_SCRIPT_FOLDER=Import\Scripts

set BUILD_BEGIN_CMD="%IMPORT_SCRIPT_FOLDER%\KmsBase_Build_Begin.cmd"
set BUILD_INSTALLER_CMD="%IMPORT_SCRIPT_FOLDER%\KmsBase_Build_Installer.cmd"

rem ===== Verification ======================================================

if not exist %BUILD_BEGIN_CMD% (
	echo FATAL ERROR  %BUILD_BEGIN_CMD%  does not exist
	echo Execute .\Import.cmd
	pause
	exit /B 10
)

if not exist %BUILD_INSTALLER_CMD% (
	echo FATAL ERROR  %BUILD_INSTALLER_CMD%  does not exist
	pause
	exit /B 20
)

rem ===== Execution =========================================================

call %BUILD_BEGIN_CMD% HTML_Interface
if ERRORLEVEL 1 (
	echo ERROR  call %BUILD_BEGIN_CMD% HRML_Interface  failed - %ERRORLEVEL%
	pause
	exit /B 30
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x86
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x86  failed - %ERRORLEVEL%
	pause
	exit /B 40
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 50
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x86
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x86  failed - %ERRORLEVEL%
	pause
	exit /B 60
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 70
)

call %TEST_CMD%
if ERRORLEVEL 1 (
    echo ERROR  call %TEST_CMD%  reported an error - %ERRORLEVEL%
	pause
	exit /B 80
)

%KMS_VERSION_EXE% Common\Version.h %EXPORT_CMD_TXT%
if ERRORLEVEL 1 (
	echo ERROR  %KMS_VERSION_EXE% Common\Version.h %EXPORT_CMD_TXT%  failed - %ERRORLEVEL%
	pause
	exit /B 90
)

call %BUILD_INSTALLER_CMD% %PRODUCT_ISS%
if ERRORLEVEL 1 (
	echo ERROR  call %BUILD_INSTALLER_CMD% %PRODUCT_ISS%  failed - %ERRORLEVEL%
	pause
	exit /B 100
)

%KMS_VERSION_EXE% -S %VERSION_H% %EXPORT_CMD%
if ERRORLEVEL 1 (
    echo ERROR  %KMS_VERSION_EXE% -S %VERSION_H% %EXPORT_CMD%  reported an error - %ERRORLEVEL%
	pause
	exit /B 110
)

rem ===== End ===============================================================

echo OK
