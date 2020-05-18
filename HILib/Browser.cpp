
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/Browser.cpp

// CODE REVIEW 2020-05-18 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-18 KMS - Martin Dubois, P.Eng.

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
#include <HI/Server.h>

#include <HI/Browser.h>

// ===== HILib ==============================================================
#include "OS.h"
#include "Utils.h"

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static bool Start_Chrome(const char * aFileName);

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    Browser::Browser() : mPrefered(PREFERED_CHROME), mState(STATE_INIT)
    {
    }

    Browser::~Browser()
    {
        switch (mState)
        {
        // NOT TESTED  Browser.Detach
        //             Detach on delete
        case STATE_OPEN: OS_Process_Close(mProcess); break;
        }
    }

    void Browser::SetPrefered(Prefered aIn)
    {
        assert(PREFERED_QTY > aIn);

        assert(PREFERED_QTY > mPrefered);

        mPrefered = aIn;
    }

    void Browser::Close()
    {
        assert(STATE_OPEN == mState);

        mState = STATE_INIT;

        OS_Process_Terminate(mProcess);
    }

    // NOT TESTED  Browser.Detach

    void Browser::Detach()
    {
        assert(STATE_OPEN == mState);

        mState = STATE_INIT;

        OS_Process_Close(mProcess);
    }

    void Browser::Open(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        char lFileName[1024];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, "html");

        Open(lFileName);
    }

    void Browser::Open(const Server * aServer, const char * aName)
    {
        assert(NULL != aServer);
        assert(NULL != aName  );

        char lURL[1024];

        sprintf_s(lURL, "http://localhost:%u/%s.html", aServer->GetPort(), aName);

        Open(lURL);
    }

    void Browser::ParseArguments(int aCount, const char ** aVector)
    {
        assert(   1 <= aCount );
        assert(NULL != aVector);

        for (int i = 1; i < aCount; i++)
        {
            assert(NULL != aVector[i]);

            ParseAssignation(aVector[i]);
        }
    }

    bool Browser::ParseAssignation(const char * aAssignation)
    {
        assert(NULL != aAssignation);

        if (0 == strcmp("Browser.Prefered=Chrome" , aAssignation)) { mPrefered = PREFERED_CHROME ; return true; }
        if (0 == strcmp("Browser.Prefered=Default", aAssignation)) { mPrefered = PREFERED_DEFAULT; return true; }
        if (0 == strcmp("Browser.Prefered=None"   , aAssignation)) { mPrefered = PREFERED_NONE   ; return true; }

        return false;
    }

    void Browser::Start(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        char lFileName[1024 +  64];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, "html");

        Start(lFileName);
    }

    void Browser::Start(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        char lFileName[1024 + 64];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, "html");

        Start(lFileName);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    // NOT TESTED  Browser.Open
    //             Open the default OS browser.
    //             Open no browser.
    //             Open the second choice when opening the first choice
    //             fails.

    void Browser::Open(const char * aFileName)
    {
        assert(STATE_INIT == mState);

        assert(NULL != aFileName);

        bool lRet;

        switch (mPrefered)
        {
        case PREFERED_CHROME : lRet = Open_Chrome (aFileName); break;
        case PREFERED_DEFAULT: lRet = Open_Default(aFileName); break;

        case PREFERED_NONE: return;

        default: assert(false);
        }

        if (!lRet)
        {
            switch (mPrefered)
            {
            case PREFERED_CHROME : lRet = Open_Default(aFileName); break;
            case PREFERED_DEFAULT: lRet = Open_Chrome (aFileName); break;

            default: assert(false);
            }

            if (!lRet)
            {
                throw std::exception("ERROR  188  Cannot open browser");
            }
        }

        mState = STATE_OPEN;
    }

    bool Browser::Open_Chrome(const char * aFileName)
    {
        assert(NULL != aFileName);

        char lCommand[1024 + 128];

        int lRet = sprintf_s(lCommand, "\"%s\" --disable-background-mode --disable-plugins --start-maximized \"%s\"", OS_CHROME_EXE, aFileName);
        assert(0                < lRet);
        assert(sizeof(lCommand) > lRet);

        return Open_Process(OS_CHROME_EXE, lCommand);
    }

    bool Browser::Open_Process(const char * aExec, const char * aCommand)
    {
        assert(NULL != aExec   );
        assert(NULL != aCommand);

        mProcess = OS_Process_Create(aExec, aCommand);

        return (NULL != mProcess);
    }

    // NOT TESTED  Browser.Open
    //             Open the default OS browser.

    bool Browser::Open_Default(const char * aFileName)
    {
        assert(NULL != aFileName);

        mProcess = OS_Open_Default(aFileName);

        return (NULL != mProcess);
    }

    // TESTED  Browser.Start
    //         Start Chrome. (GenDoc.exe)

    // NOT TESTED  Browser.Start
    //             Start the default OS browser

    void Browser::Start(const char * aFileName)
    {
        assert(NULL != aFileName);

        bool lRet;

        switch (mPrefered)
        {
        case PREFERED_CHROME : lRet =    Start_Chrome (aFileName); break;
        case PREFERED_DEFAULT: lRet = OS_Start_Default(aFileName); break;

        case PREFERED_NONE: return;

        default: assert(false);
        }

        if (!lRet)
        {
            // NOT TESTED Browser.Chrome.Error
            //            Start the second choice when starting the first
            //            choice fails.

            switch (mPrefered)
            {
            case PREFERED_CHROME : lRet = OS_Start_Default(aFileName); break;
            case PREFERED_DEFAULT: lRet =    Start_Chrome (aFileName); break;

            default: assert(false);
            }

            if (!lRet)
            {
                throw std::exception("ERROR  268  Cannot start browser");
            }
        }
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

bool Start_Chrome(const char * aFileName)
{
    assert(NULL != aFileName);

    char lCommand[1024 + 128];

    int lRet = sprintf_s(lCommand, "\"%s\" --disable-background-mode --disable-plugins --start-maximized \"%s\"", OS_CHROME_EXE, aFileName);
    assert(0                < lRet);
    assert(sizeof(lCommand) > lRet);

    return OS_Start_Process(OS_CHROME_EXE, lCommand);
}
