
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib_Test/HTML_Document.h

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/HTML_Document.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(HTML_Document_Base)

    HI::HTML_Document lHD0;

    lHD0.Create(NULL, "Test");

    lHD0.Tag(HI::TAG_HR);

    try
    {
        lHD0.Delete();

        KMS_TEST_ASSERT(false);
    }
    catch (std::exception)
    {
    }

    lHD0.Close();

    lHD0.Delete();

    HI::HTML_Document lHD1;

    lHD1.DeleteOnDestruction();

    lHD1.Create(NULL, "Test", "Test");

    HI::HTML_Document lHD2;

    try
    {
        lHD2.Create(NULL, "Test");

        KMS_TEST_ASSERT(false);
    }
    catch (std::exception)
    {
    }

KMS_TEST_END
