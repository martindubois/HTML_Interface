@echo off

rem Author     KMS - Martin Dubois, P.Eng.
rem Copyright  (C) 2020 KMS. All rights reserved.
rem Product    HTML_Interface
rem File       Build.cmd
rem Usage      Build.cmd

echo  Executing  Build.cmd  ...

rem ===== Initialisation ====================================================

set EXPORT_CMD="Export.cmd"
set KMS_VERSION="C:\Software\KmsTools\KmsVersion.exe"
set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe"
set OPTIONS="HTML_Interface.sln" /target:rebuild
set VERSION_H="Common/Version.h"

rem ===== Verification ======================================================

if not exist %KMS_VERSION% (
    echo FATAL ERROR  %KMS_VERSION%  does not exist
	echo Install KmsTools version 2.4.0 or higher
	pause
	exit /B 10
)

if not exist %MSBUILD% (
	echo FATAL ERROR  %MSBUILD%  does not exist
    echo Install Visual Studio 2017 Professional
	pause
	exit /B 20
)

rem ===== Execution =========================================================

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x86
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x86  failed - %ERRORLEVEL%
	pause
	exit /B 30
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 40
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x86
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x86  failed - %ERRORLEVEL%
	pause
	exit /B 50
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 60
)

call Test.cmd
if ERRORLEVEL 1 (
    echo ERROR  Test.cmd reported an error - %ERRORLEVEL%
	pause
	exit /B 70
)

%KMS_VERSION% -S %VERSION_H% %EXPORT_CMD%
if ERRORLEVEL 1 (
    echo ERROR  %KMS_VERSION% -S %VERSION_H% %EXPORT_CMD%  reported an error - %ERRORLEVEL%
	pause
	exit /B 80
)

rem ===== End ===============================================================

echo OK
