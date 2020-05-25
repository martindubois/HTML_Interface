
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib_Test/Diagram.cpp

// ===== Import/Includes ====================================================
#include <KmsTest.h>

// ===== Includes ===========================================================
#include <HI/Diagram.h>
#include <HI/Shape.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Diagram_Base)

    HI::Diagram lD0;

    lD0.mShapes.AddShape("Box", "A");
    lD0.mShapes.AddShape("Box", "B");
    lD0.mShapes.AddShape("Box", "C");
    lD0.mShapes.AddShape("Box", "D");
    lD0.mShapes.AddShape("Box", "E");
    lD0.mShapes.AddShape("Box", "F");

    lD0.mLinks.AddLink(lD0.mShapes.GetShape(0), lD0.mShapes.GetShape(1));
    lD0.mLinks.AddLink(lD0.mShapes.GetShape(1), lD0.mShapes.GetShape(2));
    lD0.mLinks.AddLink(lD0.mShapes.GetShape(2), lD0.mShapes.GetShape(0));

    lD0.mLinks.AddLink(lD0.mShapes.GetShape(0), lD0.mShapes.GetShape(3));

    lD0.mLinks.AddLink(lD0.mShapes.GetShape(3), lD0.mShapes.GetShape(4));
    lD0.mLinks.AddLink(lD0.mShapes.GetShape(4), lD0.mShapes.GetShape(5));
    lD0.mLinks.AddLink(lD0.mShapes.GetShape(5), lD0.mShapes.GetShape(3));

    KMS_TEST_COMPARE(0, strcmp("A", lD0.mShapes.GetShape(0)->GetName()));

    KMS_TEST_ASSERT(NULL == lD0.mShapes.GetShape(6));

    lD0.Generate_HTML(HI::FOLDER_CURRENT, "Diagram_Base_0", "Diagram - Base - 0");

KMS_TEST_END