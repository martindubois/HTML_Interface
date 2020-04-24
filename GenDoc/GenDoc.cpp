
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       GenDoc/GenDoc.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/CSS_Colors.h>
#include <HI/CSS_Document.h>
#include <HI/HTML_Document.h>

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void GenerateCSS_Colors(const char * aName, const char * aTitle, HI::CSS_Colors::Order aOrder);

static void GenerateCSS_Properties();

static void GenerateHTML_Attributes();

static void GenerateHTML_Tags();

static void GenerateIndex();

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    try
    {
        GenerateCSS_Colors("CSS_ColorsByBlue" , "CSS Colors by BLUE Component" , HI::CSS_Colors::ORDER_BLUE );
        GenerateCSS_Colors("CSS_ColorsByGreen", "CSS Colors by GREEN Component", HI::CSS_Colors::ORDER_GREEN);
        GenerateCSS_Colors("CSS_ColorsByName" , "CSS Colors by Name"           , HI::CSS_Colors::ORDER_NAME );
        GenerateCSS_Colors("CSS_ColorsByRed"  , "CSS Colors by RED Component"  , HI::CSS_Colors::ORDER_RED  );
        GenerateCSS_Colors("CSS_ColorsByWhite", "CSS Colors by WHITE Component", HI::CSS_Colors::ORDER_WHITE);

        GenerateCSS_Properties();

        GenerateHTML_Attributes();

        GenerateHTML_Tags();

        GenerateIndex();
    }
    catch (std::exception eE)
    {
        fprintf(stderr, "EXCEPTION  %s\n", eE.what());
        return __LINE__;
    }
    catch (...)
    {
        fprintf(stderr, "UNEXPECTED EXCEPTION\n");
        return __LINE__;
    }

    return 0;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void GenerateCSS_Colors(const char * aName, const char * aTitle, HI::CSS_Colors::Order aOrder)
{
    assert(NULL != aName );
    assert(NULL != aTitle);

    HI::CSS_Document  lCSS;
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_CURRENT, aName, aTitle);

    lDoc.Tag_Begin(HI::TAG_STYLE);

        lCSS.Create(&lDoc);

            lCSS.Rule_Begin_Element("td");
                lCSS.Property_Set(HI::PROP_BORDER_STYLE, HI::CSS_Document::BORDER_STYLE_SOLID);
            lCSS.Rule_End();

        lCSS.Close();

    lDoc.Tag_End(HI::TAG_STYLE);

    lDoc.Tag(HI::TAG_H1, aTitle);

    lDoc.Tag_Begin(HI::TAG_TABLE);

        HI::CSS_ColorInfo lCI;

        HI::CSS_Colors::GetFirst(&lCI, aOrder);

        do
        {
            lDoc.Tag_Begin(HI::TAG_TR);
                char lStr[64];

                sprintf_s(lStr, "%d", lCI.mIndexBy);
                lDoc.Tag(HI::TAG_TD, lStr);

                lDoc.Tag(HI::TAG_TD, lCI.mIdName);
                lDoc.Tag(HI::TAG_TD, lCI.mName  );
                
                sprintf_s(lStr, "#%06x", lCI.mValue);
                lDoc.Tag(HI::TAG_TD, lStr);

                lDoc.Attribute_Set(HI::ATTR_STYLE, "color: #ff0000; text-align: right;");
                sprintf_s(lStr, "%d", lCI.GetRed());
                lDoc.Tag(HI::TAG_TD, lStr);

                lDoc.Attribute_Set(HI::ATTR_STYLE, "color: #00ff00; text-align: right;");
                sprintf_s(lStr, "%d", lCI.GetGreen());
                lDoc.Tag(HI::TAG_TD, lStr);

                lDoc.Attribute_Set(HI::ATTR_STYLE, "color: #0000ff; text-align: right;");
                sprintf_s(lStr, "%d", lCI.GetBlue());
                lDoc.Tag(HI::TAG_TD, lStr);

                sprintf_s(lStr, "background-color: %s; width: 40px;", lCI.mName);
                lDoc.Attribute_Set(HI::ATTR_STYLE, lStr);
                lDoc.Tag(HI::TAG_TD, "");

            lDoc.Tag_End(HI::TAG_TR);
        }
        while (HI::CSS_Colors::GetNext(&lCI));

    lDoc.Tag_End(HI::TAG_TABLE);

    lDoc.Close();
}

void GenerateCSS_Properties()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_CURRENT, "CSS_PropertiesByName", "CSS Properties by Name");

        lDoc.Tag(HI::TAG_H1, "CSS Properties by Name");

    lDoc.Close();
}

void GenerateHTML_Attributes()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_CURRENT, "HTML_AttributesByName", "HTML Attributes by Name");

        lDoc.Tag(HI::TAG_H1, "HTML Attributes by Name");

    lDoc.Close();
}

void GenerateHTML_Tags()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_CURRENT, "HTML_TagsByName", "HTML Tags by Name");

        lDoc.Tag(HI::TAG_H1, "HTML Tags by Name");

    lDoc.Close();
}

void GenerateIndex()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_CURRENT, "index", "HTML_Interface Documentation");

        lDoc.Tag(HI::TAG_H1, "HTML_Interface Documentation");

        lDoc.Tag(HI::TAG_H2, "CSS");

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByName.html");
            lDoc.Tag(HI::TAG_A, "Color by Name");
        lDoc.Tag_End(HI::TAG_P);

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByBlue.html");
            lDoc.Tag(HI::TAG_A, "Color by BLUE Component");
        lDoc.Tag_End(HI::TAG_P);

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByGreen.html");
            lDoc.Tag(HI::TAG_A, "Color by GREEN Component");
        lDoc.Tag_End(HI::TAG_P);

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByRed.html");
            lDoc.Tag(HI::TAG_A, "Color by RED Component");
        lDoc.Tag_End(HI::TAG_P);

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByWhite.html");
            lDoc.Tag(HI::TAG_A, "Color by WHITE Component");
        lDoc.Tag_End(HI::TAG_P);

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_PropertiesByName.html");
            lDoc.Tag(HI::TAG_A, "Properties by Name");
        lDoc.Tag_End(HI::TAG_P);

        lDoc.Tag(HI::TAG_H2, "HTML");

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "HTML_AttributesByName.html");
            lDoc.Tag(HI::TAG_A, "Attributes by Name");
        lDoc.Tag_End(HI::TAG_P);

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "HTML_TagsByName.html");
            lDoc.Tag(HI::TAG_A, "Tags by Name");
        lDoc.Tag_End(HI::TAG_P);

    lDoc.Close();
}
