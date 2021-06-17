
/*
    Generated using the HTML_Interface library
*/

// ===== C =====
#include <assert.h>

// ===== HTML_Interface =====
#include <HI/Diagram.h>
#include <HI/Link.h>

HI::Diagram * Diagram_Base_0()
{
    HI::Diagram * lResult = new HI::Diagram();
    assert(NULL != lResult);
    lResult->SetBackgroundColor("AliceBlue");

    HI::Shape * lShape00 = lResult->mShapes.AddShape("Box", "Hotel - G", HI::Shape::TYPE_IMAGE);
    assert(NULL != lShape00);

    lShape00->SetImageURL   ("file://C:\\_VC\\HTML_Interface\\Static\\KMS.png");
    lShape00->SetSize       (80, 60);
    lShape00->SetNameOnImage();
    lShape00->SetTypeOnImage();

    HI::Shape * lShape01 = lResult->mShapes.AddShape("Box", "Bravo - A - C", HI::Shape::TYPE_RECT);
    assert(NULL != lShape01);

    lShape01->SetFillColor  ("LightGray");
    lShape01->SetSize       (104, 50);
    lShape01->SetStrokeWidth(4);
    lShape01->SetTitle      ("Light Gray!");

    HI::Shape * lShape02 = lResult->mShapes.AddShape("Box", "Charlie - A - B", HI::Shape::TYPE_RECT);
    assert(NULL != lShape02);

    lShape02->SetSize       (120, 50);

    HI::Shape * lShape03 = lResult->mShapes.AddShape("Box", "Echo - D - F", HI::Shape::TYPE_RECT);
    assert(NULL != lShape03);

    lShape03->SetSize       (96, 50);

    HI::Shape * lShape04 = lResult->mShapes.AddShape("Box", "Golf - F", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape04);


    HI::Shape * lShape05 = lResult->mShapes.AddShape("Box", "Alpha - B - C - D", HI::Shape::TYPE_RECT);
    assert(NULL != lShape05);

    lShape05->SetFillColor  ("AliceBlue");
    lShape05->SetSize       (136, 50);

    HI::Shape * lShape06 = lResult->mShapes.AddShape("Box", "Delta - A - E - F", HI::Shape::TYPE_RECT);
    assert(NULL != lShape06);

    lShape06->SetSize       (136, 50);

    HI::Shape * lShape07 = lResult->mShapes.AddShape("Box", "Foxtrot - D - E - G", HI::Shape::TYPE_RECT);
    assert(NULL != lShape07);

    lShape07->SetSize       (152, 50);

    HI::Link * lLink00 = lResult->mLinks.AddLink(lShape05, lShape01);
    assert(NULL != lLink00);

    lLink00->SetColor       ("black");

    HI::Link * lLink01 = lResult->mLinks.AddLink(lShape01, lShape02);
    assert(NULL != lLink01);

    lLink01->SetColor       ("black");

    HI::Link * lLink02 = lResult->mLinks.AddLink(lShape02, lShape05);
    assert(NULL != lLink02);

    lLink02->SetColor       ("black");

    HI::Link * lLink03 = lResult->mLinks.AddLink(lShape05, lShape06);
    assert(NULL != lLink03);

    lLink03->SetColor       ("Blue");

    HI::Link * lLink04 = lResult->mLinks.AddLink(lShape06, lShape03);
    assert(NULL != lLink04);

    lLink04->SetColor       ("black");

    HI::Link * lLink05 = lResult->mLinks.AddLink(lShape03, lShape07);
    assert(NULL != lLink05);

    lLink05->SetColor       ("black");

    HI::Link * lLink06 = lResult->mLinks.AddLink(lShape07, lShape06);
    assert(NULL != lLink06);

    lLink06->SetColor       ("black");
    lLink06->SetDashArray   ("2,2");

    HI::Link * lLink07 = lResult->mLinks.AddLink(lShape07, lShape04);
    assert(NULL != lLink07);

    lLink07->SetColor       ("Red");
    lLink07->SetWeightFactor(2.000000);
    lLink07->SetWidth       (3);

    HI::Link * lLink08 = lResult->mLinks.AddLink(lShape04, lShape00);
    assert(NULL != lLink08);

    lLink08->SetColor       ("black");

    return lResult;
}
