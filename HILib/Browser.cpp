
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020-2021 KMS. All rights reserved.
// License    https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
// Product    HTML_Interface
// File       HILib/Browser.cpp

// CODE REVIEW 2021-06-19 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2021-06-19 KMS - Martin Dubois, P.Eng.

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

// Constants
/////////////////////////////////////////////////////////////////////////////

static const HI::Browser::BrowserType ORDER[HI::Browser::BROWSER_TYPE_QTY][HI::Browser::BROWSER_TYPE_QTY - 1] =
{
    { HI::Browser::CHROME, HI::Browser::EDGE  , HI::Browser::DEFAULT_BROWSER },
    { HI::Browser::EDGE  , HI::Browser::CHROME, HI::Browser::DEFAULT_BROWSER },

    { HI::Browser::DEFAULT_BROWSER, HI::Browser::EDGE, HI::Browser::CHROME },

    { HI::Browser::NO_BROWSER },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    Browser::Browser() : mAppMode(false), mKioskMode(false), mPrefered(CHROME), mState(STATE_INIT)
    {
    }

    // NOT TESTED  Browser.Detach
    //             Detach on delete

    Browser::~Browser()
    {
        switch (State_Get())
        {
        case STATE_OPEN: OS_Process_Close(mProcess); break;
        }
    }

    bool Browser::IsOpen()
    {
        return STATE_OPEN == State_Get();
    }

    void Browser::SetAppMode  (bool aIn) { mAppMode   = aIn; }
    void Browser::SetKioskMode(bool aIn) { mKioskMode = aIn; }

    void Browser::SetPrefered(BrowserType aIn)
    {
        assert(BROWSER_TYPE_QTY > aIn);

        assert(BROWSER_TYPE_QTY > mPrefered);

        mPrefered = aIn;
    }

    void Browser::Close()
    {
        switch (State_Get())
        {
        case STATE_OPEN:
            mState = STATE_INIT;

            OS_Process_Terminate(mProcess);
            break;
        }
    }

    // NOT TESTED  Browser.Detach

    void Browser::Detach()
    {
        switch (State_Get())
        {
        case STATE_OPEN:
            mState = STATE_INIT;

            OS_Process_Close(mProcess);
            break;
        }
    }

    void Browser::Open(FolderId aFolder, const char* aName)
    {
        assert(FOLDER_QTY > aFolder);
        assert(NULL != aName);

        char lFileName[1024];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, "html");

        Open(lFileName);
    }

    void Browser::Open(const Server* aServer, const char* aName)
    {
        assert(NULL != aServer);
        assert(NULL != aName);

        char lURL[1024];

        sprintf_s(lURL, "http://localhost:%u/%s.html", aServer->GetLocalPort(), aName);

        Open(lURL);
    }

    void Browser::ParseArguments(int aCount, const char** aVector)
    {
        assert(1 <= aCount);
        assert(NULL != aVector);

        for (int i = 1; i < aCount; i++)
        {
            assert(NULL != aVector[i]);

            ParseAssignation(aVector[i]);
        }
    }

    bool Browser::ParseAssignation(const char* aAssignation)
    {
        assert(NULL != aAssignation);

        if (0 == strcmp("Browser.AppMode=false"   , aAssignation)) { mAppMode = false; return true; }
        if (0 == strcmp("Browser.AppMode=true"    , aAssignation)) { mAppMode = true ; return true; }
        if (0 == strcmp("Browser.KioskMode=false" , aAssignation)) { mKioskMode = false; return true; }
        if (0 == strcmp("Browser.KioskMode=true"  , aAssignation)) { mKioskMode = true ; return true; }
        if (0 == strcmp("Browser.Prefered=Chrome" , aAssignation)) { mPrefered = CHROME         ; return true; }
        if (0 == strcmp("Browser.Prefered=Default", aAssignation)) { mPrefered = DEFAULT_BROWSER; return true; }
        if (0 == strcmp("Browser.Prefered=Edge"   , aAssignation)) { mPrefered = EDGE           ; return true; }
        if (0 == strcmp("Browser.Prefered=None"   , aAssignation)) { mPrefered = NO_BROWSER     ; return true; }

        return false;
    }

    void Browser::Start(FolderId aFolder, const char* aName)
    {
        assert(FOLDER_QTY > aFolder);
        assert(NULL != aName);

        char lFileName[1024 + 64];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, "html");

        Start(lFileName);
    }

    void Browser::Start(const char* aFolder, const char* aName)
    {
        assert(NULL != aName);

        char lFileName[1024 + 64];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, "html");

        Start(lFileName);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Browser::BuildCmd_Chrome(const char* aFileName, char* aOut, unsigned int aOutSize_byte)
    {
        assert(NULL != aFileName);
        assert(NULL != aOut);
        assert(0 < aOutSize_byte);

        const char* lCommon = "--disable-background-mode --disable-plugins --start-maximized";

        if (mKioskMode)
        {
            sprintf_s(aOut, aOutSize_byte, "\"%s\" %s --kiosk \"%s\"", OS_CHROME_EXE, lCommon, aFileName);
        }
        else if (mAppMode)
        {
            sprintf_s(aOut, aOutSize_byte, "\"%s\" %s --app=\"%s\" --new-window", OS_CHROME_EXE, lCommon, aFileName);
        }
        else
        {
            sprintf_s(aOut, aOutSize_byte, "\"%s\" %s \"%s\"", OS_CHROME_EXE, lCommon, aFileName);
        }
    }

    void Browser::BuildCmd_Edge(const char* aFileName, char* aOut, unsigned int aOutSize_byte)
    {
        assert(NULL != aFileName);
        assert(NULL != aOut);
        assert(0 < aOutSize_byte);

        if (mKioskMode)
        {
            sprintf_s(aOut, aOutSize_byte, "\"%s\" --kiosk \"%s\" --edge-kiosk-type=fullscreen --no-first-run", OS_EDGE_EXE, aFileName);
        }
        else
        {
            sprintf_s(aOut, aOutSize_byte, "\"%s\" \"%s\"", OS_EDGE_EXE, aFileName);
        }
    }

    // NOT TESTED  Browser.Open
    //             Open the second choice when opening the first choice
    //             fails.

    void Browser::Open(const char* aFileName)
    {
        assert(STATE_INIT == mState);

        assert(NULL != aFileName);

        for (unsigned int i = 0; i < NO_BROWSER; i++)
        {
            bool lRet;

            switch (ORDER[mPrefered][i])
            {
            case CHROME: lRet = Open_Chrome(aFileName); break;
            case EDGE  : lRet = Open_Edge  (aFileName); break;

            case DEFAULT_BROWSER: lRet = Open_Default(aFileName); break;

            case NO_BROWSER: return;
            }

            if (lRet)
            {
                mState = STATE_OPEN;
                return;
            }
        }

        Utl_ThrowError("ERROR", __LINE__, "Cannot open browser (NOT TESTED)");
    }

    bool Browser::Open_Chrome(const char* aFileName)
    {
        assert(NULL != aFileName);

        char lCommand[1024 + 128];

        BuildCmd_Chrome(aFileName, lCommand, sizeof(lCommand));

        return Open_Process(OS_CHROME_EXE, lCommand);
    }

    bool Browser::Open_Edge(const char* aFileName)
    {
        assert(NULL != aFileName);

        char lCommand[1024 + 128];

        BuildCmd_Edge(aFileName, lCommand, sizeof(lCommand));

        return Open_Process(OS_EDGE_EXE, lCommand);
    }

    bool Browser::Open_Process(const char* aExec, const char* aCommand)
    {
        assert(NULL != aExec);
        assert(NULL != aCommand);

        mProcess = OS_Process_Create(aExec, aCommand);

        return (NULL != mProcess);
    }

    bool Browser::Open_Default(const char* aFileName)
    {
        assert(NULL != aFileName);

        mProcess = OS_Open_Default(aFileName);

        return (NULL != mProcess);
    }

    void Browser::Start(const char* aFileName)
    {
        assert(NULL != aFileName);

        for (unsigned int i = 0; i < NO_BROWSER; i++)
        {
            bool lRet;

            switch (ORDER[mPrefered][i])
            {
            case CHROME: lRet = Start_Chrome(aFileName); break;
            case EDGE  : lRet = Start_Edge  (aFileName); break;

            case DEFAULT_BROWSER: lRet = OS_Start_Default(aFileName); break;

            case NO_BROWSER: return;
            }

            if (lRet)
            {
                return;
            }
        }

        Utl_ThrowError("ERROR", __LINE__, "Cannot start browser (NOT TESTED)");
    }

    bool Browser::Start_Chrome(const char* aFileName)
    {
        assert(NULL != aFileName);

        char lCommand[1024 + 128];

        BuildCmd_Chrome(aFileName, lCommand, sizeof(lCommand));

        return OS_Start_Process(OS_CHROME_EXE, lCommand);
    }

    bool Browser::Start_Edge(const char* aFileName)
    {
        assert(NULL != aFileName);

        char lCommand[1024 + 128];

        BuildCmd_Edge(aFileName, lCommand, sizeof(lCommand));

        return OS_Start_Process(OS_EDGE_EXE, lCommand);
    }

    Browser::State Browser::State_Get()
    {
        switch (mState)
        {
        case STATE_OPEN:
            if (!OS_Process_IsRunning(mProcess))
            {
                mState = STATE_INIT;
            }
            break;
        }

        return mState;
    }

}
