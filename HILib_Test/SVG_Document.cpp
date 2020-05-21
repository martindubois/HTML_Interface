
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib_Test/SVG_Document.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/SVG_Document.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(SVG_Document_Base)

    HI::SVG_Document lSD0;

    lSD0.Attribute_Set(HI::SVG_Document::ATTR_HEIGHT,  768);
    lSD0.Attribute_Set(HI::SVG_Document::ATTR_WIDTH , 1024);

    lSD0.Create(HI::FOLDER_CURRENT, "SVG_Document_Base_0");

    lSD0.DeleteOnDestruction();

KMS_TEST_END
