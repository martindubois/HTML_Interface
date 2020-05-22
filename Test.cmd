@echo off

rem Author     KMS - Martin Dubois, P.Eng.
rem Copyright  (C) 2020 KMS. All rights reserved.
rem Product    HTML_Interface
rem File       Test.cmd
rem Usage      Test.cmd

echo Executing  Test.cmd  ...

rem ===== Initialisation ====================================================

set GEN_DOC_ARG="Browser.Prefered=None"

set GEN_DOC_EXE=GenDoc.exe

set HI_LIB_TEST_EXE=HILib_Test.exe

rem ===== Verification ======================================================

rem ===== Execution =========================================================

set CONFIG=Debug

%CONFIG%\%HI_LIB_TEST_EXE%
if ERRORLEVEL 1 (
	echo ERROR  %CONFIG%\%HI_LIB_TEST_EXE%  failed - %ERRORLEVEL%
	pause
	exit /B 5
)

%CONFIG%\%GEN_DOC_EXE% %GEN_DOC_ARG%
if ERRORLEVEL 1 (
	echo ERROR  %CONFIG%\%GEN_DOC_EXE%  failed - %ERRORLEVEL%
	pause
	exit /B 10
)

set CONFIG=x64\Debug

%CONFIG%\%HI_LIB_TEST_EXE%
if ERRORLEVEL 1 (
	echo ERROR  %CONFIG%\%HI_LIB_TEST_EXE%  failed - %ERRORLEVEL%
	pause
	exit /B 15
)

%CONFIG%\%GEN_DOC_EXE% %GEN_DOC_ARG%
if ERRORLEVEL 1 (
	echo ERROR  %CONFIG%\%GEN_DOC_EXE%  failed - %ERRORLEVEL%
	pause
	exit /B 20
)

set CONFIG=Release

%CONFIG%\%HI_LIB_TEST_EXE%
if ERRORLEVEL 1 (
	echo ERROR  %CONFIG%\%HI_LIB_TEST_EXE%  failed - %ERRORLEVEL%
	pause
	exit /B 25
)

%CONFIG%\%GEN_DOC_EXE% %GEN_DOC_ARG%
if ERRORLEVEL 1 (
	echo ERROR  %CONFIG%\%GEN_DOC_EXE%  failed - %ERRORLEVEL%
	pause
	exit /B 30
)

set CONFIG=x64\Release

%CONFIG%\%HI_LIB_TEST_EXE%
if ERRORLEVEL 1 (
	echo ERROR  %CONFIG%\%HI_LIB_TEST_EXE%  failed - %ERRORLEVEL%
	pause
	exit /B 35
)

%CONFIG%\%GEN_DOC_EXE% %GEN_DOC_ARG%
if ERRORLEVEL 1 (
	echo ERROR  %CONFIG%\%GEN_DOC_EXE%  failed - %ERRORLEVEL%
	pause
	exit /B 40
)

rem ===== End ===============================================================

echo OK
