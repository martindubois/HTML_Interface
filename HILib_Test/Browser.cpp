
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020-2021 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib_Test/Browser.h

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/Browser.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

static const char * ARG_0[] = { "HILib_Test.exe", "Browser.Prefered=None", "Useless" };

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Browser_Base)

    HI::Browser lB0;

    KMS_TEST_ASSERT(!lB0.IsOpen());

    lB0.ParseArguments(1, ARG_0);

    lB0.Open(HI::FOLDER_STATIC, "Tests/AutoClose");
    lB0.Close();

    lB0.SetPrefered(HI::Browser::CHROME);

    lB0.Open(HI::FOLDER_STATIC, "Tests/AutoClose");
    lB0.Close();

    lB0.SetAppMode(true);

    lB0.Open(HI::FOLDER_STATIC, "Tests/AutoClose");
    lB0.Close();

    lB0.SetKioskMode(true);

    lB0.Open(HI::FOLDER_STATIC, "Tests/AutoClose");
    lB0.Close();

    lB0.SetKioskMode(false);
    lB0.SetPrefered(HI::Browser::EDGE);

    lB0.Open(HI::FOLDER_STATIC, "Tests/AutoClose");
    lB0.Close();

    lB0.SetKioskMode(true);

    lB0.Open(HI::FOLDER_STATIC, "Tests/AutoClose");
    lB0.Close();

    lB0.SetPrefered(HI::Browser::DEFAULT_BROWSER);

    lB0.Open(HI::FOLDER_STATIC, "Tests/AutoClose");
    lB0.Close();

    lB0.ParseArguments(3, ARG_0);

    lB0.Open(HI::FOLDER_STATIC, "DoesNotExist");

    lB0.Start(HI::FOLDER_STATIC, "DoesNotExist");
    lB0.Start(NULL             , "DoesNotExist");

KMS_TEST_END

KMS_TEST_BEGIN(Browser_SetupA)

    HI::Browser lB0;

    lB0.Start(HI::FOLDER_CURRENT, "DoesNotExist");
    lB0.Start(NULL              , "DoesNotExist");

    lB0.SetPrefered(HI::Browser::EDGE);

    lB0.Start(HI::FOLDER_CURRENT, "DoesNotExist");

    lB0.SetPrefered(HI::Browser::DEFAULT_BROWSER);

    lB0.Start(HI::FOLDER_CURRENT, "DoesNotExist");

KMS_TEST_END
