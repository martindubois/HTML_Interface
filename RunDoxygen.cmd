@echo off

rem Author     KMS - Martin Dubois, P.Eng.
rem Copyright  (C) 2020 KMS. All rights reserved.
rem Product	   HTML_Interface
rem File       RunDoxygen.cmd

echo Executing  RunDoxygen.cmd  ...

rem ===== Initialisation ====================================================

set DOXYGEN="C:\Program Files\doxygen\bin\doxygen.exe"
set DOXYFILE_EN="DoxyFile_en.txt"

rem ===== Validation ========================================================

if not exist %DOXYGEN% (
    echo FATAL ERROR  %DOXYGEN%  does not exist
	echo Install doxygen
	pause
	exit /B 10
)

rem ===== Execution =========================================================

%DOXYGEN% %DOXYFILE_EN%
if ERRORLEVEL 1 (
    echo ERROR  %DOXYGEN%  reported an error - %ERRORLEVEL%
	pause
	exit /B 20
)

rem ===== End ===============================================================

echo OK!
