@echo off

rem Author     KMS - Martin Dubois, P.Eng.
rem Copyright  (C) 2020-2021 KMS. All rights reserved.
rem License    https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
rem Product    HTML_Interface
rem File       Export.cmd
rem Usage      .\Export.cmd {Ma.Mi.Bu} [Type]

echo  Executing  Export.cmd %1 %2  ...

rem ===== Initialisation ====================================================

set IMPORT_SCRIPT_FOLDER=Import\Scripts

set EXPORT_CMD="%IMPORT_SCRIPT_FOLDER%\KmsBase_Export.cmd"

rem ===== Execution =========================================================

call %EXPORT_CMD% HTML_Interface %1 %2
if ERRORLEVEL 1 (
    echo ERROR  call %EXPORT_CMD% EthCAN %1 %2  failed - %ERRORLEVEL%
	pause
	exit /B 10
)

rem ===== End ===============================================================

echo OK
