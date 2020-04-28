@echo off

rem Author     KMS - Martin Dubois, P.Eng.
rem Copyright  (C) 2020 KMS. All rights reserved.
rem Product    HTML_Interface
rem File       Test.cmd
rem Usage      Test.cmd

echo Executing  Test.cmd  ...

rem ===== Initialisation ====================================================

rem ===== Verification ======================================================

rem ===== Execution =========================================================

Debug\HILib_Test.exe
if ERRORLEVEL 1 (
	echo ERROR  Debug\HILib_Test.exe  failed - %ERRORLEVEL%
	pause
	exit /B 5
)

Debug\GenDoc.exe
if ERRORLEVEL 1 (
	echo ERROR  Debug\GenDoc.exe  failed - %ERRORLEVEL%
	pause
	exit /B 10
)

x64\Debug\HILib_Test.exe
if ERRORLEVEL 1 (
	echo ERROR  x64\Debug\HILib_Test.exe  failed - %ERRORLEVEL%
	pause
	exit /B 15
)

x64\Debug\GenDoc.exe
if ERRORLEVEL 1 (
	echo ERROR  x64\Debug\GenDoc.exe  failed - %ERRORLEVEL%
	pause
	exit /B 20
)

Release\HILib_Test.exe
if ERRORLEVEL 1 (
	echo ERROR  Release\HILib_Test.exe  failed - %ERRORLEVEL%
	pause
	exit /B 25
)

Release\GenDoc.exe
if ERRORLEVEL 1 (
	echo ERROR  Release\GenDoc.exe  failed - %ERRORLEVEL%
	pause
	exit /B 30
)

x64\Release\HILib_Test.exe
if ERRORLEVEL 1 (
	echo ERROR  x64\Release\HILib_Test.exe  failed - %ERRORLEVEL%
	pause
	exit /B 35
)

x64\Release\GenDoc.exe
if ERRORLEVEL 1 (
	echo ERROR  x64\Release\GenDoc.exe  failed - %ERRORLEVEL%
	pause
	exit /B 40
)

rem ===== End ===============================================================

echo OK
