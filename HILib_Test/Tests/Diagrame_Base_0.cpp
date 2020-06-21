
/*
    Generated using the HTML_Interface library
*/

// ===== C =====
#include <assert.h>

// ===== HTML_Interface =====
#include <HI/Diagram.h>
#include <HI/Link.h>

HI::Diagram * Diagrame_Base_0()
{
    HI::Diagram * lResult = new HI::Diagram();
    assert(NULL != lResult);

    HI::Shape * lShape00 = new HI::Shape("Box", "Golf - F", HI::Shape::TYPE_ELLIPSE);
    assert(NULL != lShape00);

    lShape00->SetAutoDelete();
    lShape00->SetFillColor ("white");
    lShape00->SetName      ("Golf - F");
    lShape00->SetTitle     ("");

    HI::Shape * lShape01 = new HI::Shape("Box", "Bravo - A - C", HI::Shape::TYPE_RECT);
    assert(NULL != lShape01);

    lShape01->SetAutoDelete();
    lShape01->SetFillColor ("LightGray");
    lShape01->SetName      ("Bravo - A - C");
    lShape01->SetTitle     ("Light Gray");

    HI::Shape * lShape02 = new HI::Shape("Box", "Charlie - A - B", HI::Shape::TYPE_RECT);
    assert(NULL != lShape02);

    lShape02->SetAutoDelete();
    lShape02->SetFillColor ("white");
    lShape02->SetName      ("Charlie - A - B");
    lShape02->SetTitle     ("");

    HI::Shape * lShape03 = new HI::Shape("Box", "Echo - D - F", HI::Shape::TYPE_RECT);
    assert(NULL != lShape03);

    lShape03->SetAutoDelete();
    lShape03->SetFillColor ("white");
    lShape03->SetName      ("Echo - D - F");
    lShape03->SetTitle     ("");

    HI::Shape * lShape04 = new HI::Shape("Box", "Alpha - B - C - D", HI::Shape::TYPE_RECT);
    assert(NULL != lShape04);

    lShape04->SetAutoDelete();
    lShape04->SetFillColor ("AliceBlue");
    lShape04->SetName      ("Alpha - B - C - D");
    lShape04->SetTitle     ("");

    HI::Shape * lShape05 = new HI::Shape("Box", "Delta - A - E - F", HI::Shape::TYPE_RECT);
    assert(NULL != lShape05);

    lShape05->SetAutoDelete();
    lShape05->SetFillColor ("white");
    lShape05->SetName      ("Delta - A - E - F");
    lShape05->SetTitle     ("");

    HI::Shape * lShape06 = new HI::Shape("Box", "Foxtrot - D - E - G", HI::Shape::TYPE_RECT);
    assert(NULL != lShape06);

    lShape06->SetAutoDelete();
    lShape06->SetFillColor ("white");
    lShape06->SetName      ("Foxtrot - D - E - G");
    lShape06->SetTitle     ("");

    HI::Link * lLink00 = new HI::Link(lShape04, lShape01);
    assert(NULL != lLink00);

    lLink00->SetAutoDelete  ();
    lLink00->SetColor       ("black");
    lLink00->SetDashArray   ("");
    lLink00->SetWeightFactor(1.000000);
    lLink00->SetWidth       (1);

    HI::Link * lLink01 = new HI::Link(lShape01, lShape02);
    assert(NULL != lLink01);

    lLink01->SetAutoDelete  ();
    lLink01->SetColor       ("black");
    lLink01->SetDashArray   ("");
    lLink01->SetWeightFactor(1.000000);
    lLink01->SetWidth       (1);

    HI::Link * lLink02 = new HI::Link(lShape02, lShape04);
    assert(NULL != lLink02);

    lLink02->SetAutoDelete  ();
    lLink02->SetColor       ("black");
    lLink02->SetDashArray   ("");
    lLink02->SetWeightFactor(1.000000);
    lLink02->SetWidth       (1);

    HI::Link * lLink03 = new HI::Link(lShape04, lShape05);
    assert(NULL != lLink03);

    lLink03->SetAutoDelete  ();
    lLink03->SetColor       ("Blue");
    lLink03->SetDashArray   ("");
    lLink03->SetWeightFactor(1.000000);
    lLink03->SetWidth       (1);

    HI::Link * lLink04 = new HI::Link(lShape05, lShape03);
    assert(NULL != lLink04);

    lLink04->SetAutoDelete  ();
    lLink04->SetColor       ("black");
    lLink04->SetDashArray   ("");
    lLink04->SetWeightFactor(1.000000);
    lLink04->SetWidth       (1);

    HI::Link * lLink05 = new HI::Link(lShape03, lShape06);
    assert(NULL != lLink05);

    lLink05->SetAutoDelete  ();
    lLink05->SetColor       ("black");
    lLink05->SetDashArray   ("");
    lLink05->SetWeightFactor(1.000000);
    lLink05->SetWidth       (1);

    HI::Link * lLink06 = new HI::Link(lShape06, lShape05);
    assert(NULL != lLink06);

    lLink06->SetAutoDelete  ();
    lLink06->SetColor       ("black");
    lLink06->SetDashArray   ("2,2");
    lLink06->SetWeightFactor(1.000000);
    lLink06->SetWidth       (1);

    HI::Link * lLink07 = new HI::Link(lShape06, lShape00);
    assert(NULL != lLink07);

    lLink07->SetAutoDelete  ();
    lLink07->SetColor       ("Red");
    lLink07->SetDashArray   ("");
    lLink07->SetWeightFactor(2.000000);
    lLink07->SetWidth       (3);

    return lResult;
}
