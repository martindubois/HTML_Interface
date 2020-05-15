
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib_Test/CSS_Document.h

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/CSS_Document.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(CSS_Document_Base)

    HI::CSS_Document lCD0;

    lCD0.DeleteOnDestruction();

    lCD0.Create(HI::FOLDER_TEMP, "Test");

        lCD0.Rule_Begin_Element("table");

            lCD0.Property_Set(HI::CSS_Document::PROP_BORDER_STYLE, HI::CSS_Document::BORDER_STYLE_DASHED);
            lCD0.Property_Set(HI::CSS_Document::PROP_PADDING, 10, HI::CSS_Document::UNIT_PX);

        lCD0.Rule_End();

    lCD0.Close();

    HI::CSS_Document lCD1;

    lCD1.Create(NULL, "Test");

        lCD1.Rule_Begin_Element("table");

            lCD1.Property_Set(HI::CSS_Document::PROP_BORDER_STYLE, HI::CSS_Document::BORDER_STYLE_DOTTED);

        lCD1.Rule_End();

    lCD1.Close();

    lCD1.Delete();

KMS_TEST_END
