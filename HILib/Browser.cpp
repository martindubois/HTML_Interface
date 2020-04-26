
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/Browser.cpp

// CODE REVIEW 2020-04-26 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-04-26 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>

// ===== C++ ================================================================
#include <exception>

// ===== Windows ============================================================
#include <Windows.h>

// ===== Includes ===========================================================
#include <HI/Browser.h>

// ===== HILib ==============================================================
#include "Utils.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define CHROME_EXE "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe"

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static bool Start_Chrome (const char * aFileName);
static bool Start_Process(const char * aExec, const char * aCommand);
static bool Start_Windows(const char * aFileName);

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    Browser::Browser()
    {
    }

    Browser::~Browser()
    {
    }

    // TODO Browser.Arguments
    //      Add arguments to
    //      - Select the default browser
    //      - Disable the broweser
    void Browser::ParseArguments(int aCount, const char ** aVector)
    {
        assert(   1 <= aCount );
        assert(NULL != aVector);
    }

    void Browser::Start(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        char lCommand [1024 + 128];
        char lFileName[1024 +  64];

        memset(&lCommand , 0, sizeof(lCommand ));

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, "html");

        if (!Start_Chrome(lFileName))
        {
            // NOT TESTED Browser.Chrome.Error
            //            Start the Windows default browser when starting
            //            Chrome fail.
            if (!Start_Windows(lFileName))
            {
                throw std::exception("ERROR  Cannot start browser");
            }
        }
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// aFileName [---;R--]
bool Start_Chrome(const char * aFileName)
{
    assert(NULL != aFileName);

    char lCommand[1024 + 128];

    int lRet = sprintf_s(lCommand, "\"" CHROME_EXE "\" --disable-background-mode --disable-plugins --start-maximized \"%s\"", aFileName);
    assert(0 < lRet);
    assert(sizeof(lCommand) > lRet);

    return Start_Process(CHROME_EXE, lCommand);
}

// aExec    [---;R--]
// aCommand [---;R--]
bool Start_Process(const char * aExec, const char * aCommand)
{
    assert(NULL != aExec   );
    assert(NULL != aCommand);

    PROCESS_INFORMATION lPI;
    STARTUPINFO         lSI;

    memset(&lPI, 0, sizeof(lPI));
    memset(&lSI, 0, sizeof(lSI));

    lSI.cb = sizeof(lSI);

    BOOL lRetB = CreateProcess(CHROME_EXE, const_cast<char *>(aCommand), NULL, NULL, FALSE, 0, NULL, NULL, &lSI, &lPI);
    if (lRetB)
    {
        lRetB = CloseHandle(lPI.hProcess);
        assert(lRetB);

        lRetB = CloseHandle(lPI.hThread);
        assert(lRetB);
    }

    return lRetB;
}

// NOT TESTED Browser.Windows
//            Start the windows default browser

// aFileName [---;R--]
bool Start_Windows(const char * aFileName)
{
    assert(NULL != aFileName);

    HINSTANCE lRet = ShellExecute(NULL, "open", aFileName, NULL, NULL, SW_SHOWDEFAULT);
    return (32 < reinterpret_cast<int64_t>(lRet));
}
