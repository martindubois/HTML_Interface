@echo off

rem Author    KMS - Martin Dubois, P.Eng.
rem Copyright (C) 2020 KMS. All rights reserved.
rem Product   HTML_Interface
rem File      Build.cmd
rem Usage     .\Build.cmd

echo Executing  Build.cmd  ...

rem ===== Initialisation ====================================================

set EXPORT_CMD="Export.cmd"
set INNO_COMPIL32="C:\Program Files (x86)\Inno Setup 5\Compil32.exe"
set KMS_VERSION="Import\Binaries\Release_32\KmsVersion.exe"
set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe"
set PRODUCT="HTML_Interface"
set OPTIONS="%PRODUCT%.sln" /target:rebuild
set VERSION_H="Common/Version.h"
set TEST_CMD="Test.cmd"

rem ===== Verification ======================================================

if not exist %INNO_COMPIL32% (
	echo FATAL ERROR  %INNO_COMPIL32%  does not exist
	echo Install Inno 5.6.1
	pause
	exit /B 10
)

if not exist %KMS_VERSION% (
    echo FATAL ERROR  %KMS_VERSION%  does not exist
	echo Install KmsTools version 2.4.0 or higher
	pause
	exit /B 20
)

if not exist %MSBUILD% (
	echo FATAL ERROR  %MSBUILD%  does not exist
    echo Install Visual Studio 2017 Professional
	pause
	exit /B 30
)

rem ===== Execution =========================================================

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

%KMS_VERSION% Common\Version.h Export.cmd.txt %PRODUCT%.iss
if ERRORLEVEL 1 (
	echo ERROR  %KMS_VERSION% Common\Version.h Export.cmd.txt %PRODUCT%.iss  failed - %ERRORLEVEL%
	pause
	exit /B 90
)

%INNO_COMPIL32% /cc %PRODUCT%.iss
if ERRORLEVEL 1 (
	echo ERROR  %INNO_COMPIL32% /cc %PRODUCT%.iss  failed - %ERRORLEVEL%
	pause
	exit /B 100
)

%KMS_VERSION% -S %VERSION_H% %EXPORT_CMD%
if ERRORLEVEL 1 (
    echo ERROR  %KMS_VERSION% -S %VERSION_H% %EXPORT_CMD%  reported an error - %ERRORLEVEL%
	pause
	exit /B 110
)

rem ===== End ===============================================================

echo OK
