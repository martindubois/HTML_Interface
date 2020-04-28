
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib_Test/Browser.h

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/Browser.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Browser_Base)

    HI::Browser lB0;

    lB0.Start(HI::FOLDER_CURRENT, "DoesNotExist");
    lB0.Start(NULL              , "DoesNotExist");

KMS_TEST_END
