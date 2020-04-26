
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       GenDoc/GenDoc.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== KmsBase ============================================================
#include <KmsTool.h>

// ===== Includes ===========================================================
#include <HI/Browser.h>
#include <HI/CSS_Colors.h>
#include <HI/CSS_Document.h>
#include <HI/HTML_Document.h>

// ===== Common =============================================================
#include "../Common/Version.h"

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void ConfigBorders(HI::HTML_Document * aDoc);

static void GenerateCSS_Colors(const char * aName, const char * aTitle, HI::CSS_Colors::Order aOrder);

static void GenerateCSS_Properties();

static void GenerateHTML_Attributes();

static void GenerateHTML_Tags();

static void GenerateIndex();

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char ** aVector)
{
    KMS_TOOL_BANNER("HTML_Interface", "GenDoc", VERSION_STR, VERSION_TYPE);

    try
    {
        HI::Browser lBrowser;

        lBrowser.ParseArguments(aCount, aVector);

        GenerateCSS_Colors("CSS_ColorsByBlue" , "CSS Colors by BLUE Component" , HI::CSS_Colors::ORDER_BLUE );
        GenerateCSS_Colors("CSS_ColorsByGreen", "CSS Colors by GREEN Component", HI::CSS_Colors::ORDER_GREEN);
        GenerateCSS_Colors("CSS_ColorsByName" , "CSS Colors by Name"           , HI::CSS_Colors::ORDER_NAME );
        GenerateCSS_Colors("CSS_ColorsByRed"  , "CSS Colors by RED Component"  , HI::CSS_Colors::ORDER_RED  );
        GenerateCSS_Colors("CSS_ColorsByWhite", "CSS Colors by WHITE Component", HI::CSS_Colors::ORDER_WHITE);

        GenerateCSS_Properties();

        GenerateHTML_Attributes();

        GenerateHTML_Tags();

        GenerateIndex();

        lBrowser.Start(HI::FOLDER_TEMP, "index");
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

void ConfigBorders(HI::HTML_Document * aDoc)
{
    assert(NULL != aDoc);

    HI::CSS_Document  lCSS;

    aDoc->Tag_Begin(HI::TAG_STYLE);

        lCSS.Create(aDoc);

            lCSS.Rule_Begin_Element("td");
                lCSS.Property_Set(HI::PROP_BORDER_STYLE, HI::CSS_Document::BORDER_STYLE_SOLID);
            lCSS.Rule_End();

        lCSS.Close();

    aDoc->Tag_End();
}

void GenerateCSS_Colors(const char * aName, const char * aTitle, HI::CSS_Colors::Order aOrder)
{
    assert(NULL != aName );
    assert(NULL != aTitle);

    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_TEMP, aName, aTitle);

        ConfigBorders(&lDoc);

        lDoc.Tag(HI::TAG_H1, aTitle);

        lDoc.Tag_Begin(HI::TAG_TABLE);

            lDoc.Tag_Begin(HI::TAG_TR);
                lDoc.Tag(HI::TAG_TH, "Index"     );
                lDoc.Tag(HI::TAG_TH, "Enum value");
                lDoc.Tag(HI::TAG_TH, "Name"      );
                lDoc.Tag(HI::TAG_TH, "Value"     );
                lDoc.Tag(HI::TAG_TH, "Red"       );
                lDoc.Tag(HI::TAG_TH, "Green"     );
                lDoc.Tag(HI::TAG_TH, "Blue"      );
                lDoc.Tag(HI::TAG_TH, "Sample"    );
            lDoc.Tag_End();

            HI::CSS_ColorInfo lCI;

            HI::CSS_Colors::GetFirst(&lCI, aOrder);

            do
            {
                lDoc.Tag_Begin(HI::TAG_TR);

                    char lStr[64];

                    sprintf_s(lStr, "%d", lCI.mIndexBy);
                    lDoc.Tag(HI::TAG_TD, lStr);

                    lDoc.Tag_Begin(HI::TAG_TD);
                        lDoc.Tag(HI::TAG_CODE, lCI.mIdName);
                    lDoc.Tag_End();

                    lDoc.Tag_Begin(HI::TAG_TD);
                        lDoc.Tag(HI::TAG_CODE, lCI.mName);
                    lDoc.Tag_End();

                    lDoc.Tag_Begin(HI::TAG_TD);
                        sprintf_s(lStr, "#%06x", lCI.mValue);
                        lDoc.Tag(HI::TAG_CODE, lStr);
                    lDoc.Tag_End();

                    lDoc.Attribute_Set(HI::ATTR_STYLE, "color: #ff0000; text-align: right;");
                    sprintf_s(lStr, "%d", lCI.GetRed());
                    lDoc.Tag(HI::TAG_TD, lStr);

                    lDoc.Attribute_Set(HI::ATTR_STYLE, "color: #00ff00; text-align: right;");
                    sprintf_s(lStr, "%d", lCI.GetGreen());
                    lDoc.Tag(HI::TAG_TD, lStr);

                    lDoc.Attribute_Set(HI::ATTR_STYLE, "color: #0000ff; text-align: right;");
                    sprintf_s(lStr, "%d", lCI.GetBlue());
                    lDoc.Tag(HI::TAG_TD, lStr);

                    sprintf_s(lStr, "background-color: %s;", lCI.mName);
                    lDoc.Attribute_Set(HI::ATTR_STYLE, lStr);
                    lDoc.Tag(HI::TAG_TD, "");

                lDoc.Tag_End();
            }
            while (HI::CSS_Colors::GetNext(&lCI));

        lDoc.Tag_End();

    lDoc.Close();
}

void GenerateCSS_Properties()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_TEMP, "CSS_PropertiesByName", "CSS Properties by Name");

        ConfigBorders(&lDoc);

        lDoc.Tag(HI::TAG_H1, "CSS Properties by Name");

        lDoc.Tag_Begin(HI::TAG_TABLE);

            lDoc.Tag_Begin(HI::TAG_TR);
                lDoc.Tag(HI::TAG_TH, "Enum value");
                lDoc.Tag(HI::TAG_TH, "Property"  );
            lDoc.Tag_End();

            HI::CSS_PropertyInfo lPI;

            HI::CSS_Properties::GetFirst(&lPI);

            do
            {
                lDoc.Tag_Begin(HI::TAG_TR);
                    lDoc.Tag_Begin(HI::TAG_TD);
                        lDoc.Tag(HI::TAG_CODE, lPI.mIdName);
                    lDoc.Tag_End();
                    lDoc.Tag_Begin(HI::TAG_TD);
                        lDoc.Tag(HI::TAG_CODE, lPI.mName);
                    lDoc.Tag_End();
                lDoc.Tag_End();
            }
            while(HI::CSS_Properties::GetNext(&lPI));

        lDoc.Tag_End();

    lDoc.Close();
}

void GenerateHTML_Attributes()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_TEMP, "HTML_AttributesByName", "HTML Attributes by Name");

        ConfigBorders(&lDoc);

        lDoc.Tag(HI::TAG_H1, "HTML Attributes by Name");

        lDoc.Tag_Begin(HI::TAG_TABLE);

            lDoc.Tag_Begin(HI::TAG_TR);
                lDoc.Tag(HI::TAG_TH, "Enum value");
                lDoc.Tag(HI::TAG_TH, "Attribute" );
            lDoc.Tag_End();

            HI::HTML_AttributeInfo lAI;

            HI::HTML_Attributes::GetFirst(&lAI);

            do
            {
                lDoc.Tag_Begin(HI::TAG_TR);
                    lDoc.Tag_Begin(HI::TAG_TD);
                        lDoc.Tag(HI::TAG_CODE, lAI.mIdName);
                    lDoc.Tag_End();
                    lDoc.Tag_Begin(HI::TAG_TD);
                        lDoc.Tag(HI::TAG_CODE, lAI.mName);
                    lDoc.Tag_End();
                lDoc.Tag_End();
            }
            while(HI::HTML_Attributes::GetNext(&lAI));

        lDoc.Tag_End();

    lDoc.Close();
}

void GenerateHTML_Tags()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_TEMP, "HTML_TagsByName", "HTML Tags by Name");

        ConfigBorders(&lDoc);

        lDoc.Tag(HI::TAG_H1, "HTML Tags by Name");

        lDoc.Tag_Begin(HI::TAG_TABLE);

            lDoc.Tag_Begin(HI::TAG_TR);
                lDoc.Tag(HI::TAG_TH, "Enum value");
                lDoc.Tag(HI::TAG_TH, "Tag"  );
            lDoc.Tag_End();

            HI::HTML_TagInfo lTI;

            HI::HTML_Tags::GetFirst(&lTI);

            do
            {
                lDoc.Tag_Begin(HI::TAG_TR);
                    lDoc.Tag(HI::TAG_TD, lTI.mIdName);

                    char lStr[64];

                    sprintf_s(lStr, "&lt;%s&gt;", lTI.mName);
                    lDoc.Tag(HI::TAG_TD, lStr);
                lDoc.Tag_End();
            }
            while(HI::HTML_Tags::GetNext(&lTI));

        lDoc.Tag_End();

    lDoc.Close();
}

void GenerateIndex()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_TEMP, "index", "HTML_Interface Documentation");

        lDoc.Tag(HI::TAG_H1, "HTML_Interface Documentation");

        lDoc.Tag(HI::TAG_H2, "CSS");

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByName.html");
            lDoc.Tag(HI::TAG_A, "Color by Name");
        lDoc.Tag_End();

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByBlue.html");
            lDoc.Tag(HI::TAG_A, "Color by BLUE Component");
        lDoc.Tag_End();

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByGreen.html");
            lDoc.Tag(HI::TAG_A, "Color by GREEN Component");
        lDoc.Tag_End();

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByRed.html");
            lDoc.Tag(HI::TAG_A, "Color by RED Component");
        lDoc.Tag_End();

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_ColorsByWhite.html");
            lDoc.Tag(HI::TAG_A, "Color by WHITE Component");
        lDoc.Tag_End();

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "CSS_PropertiesByName.html");
            lDoc.Tag(HI::TAG_A, "Properties by Name");
        lDoc.Tag_End();

        lDoc.Tag(HI::TAG_H2, "HTML");

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "HTML_AttributesByName.html");
            lDoc.Tag(HI::TAG_A, "Attributes by Name");
        lDoc.Tag_End();

        lDoc.Tag_Begin(HI::TAG_P);
            lDoc.Attribute_Set(HI::ATTR_HREF, "HTML_TagsByName.html");
            lDoc.Tag(HI::TAG_A, "Tags by Name");
        lDoc.Tag_End();

    lDoc.Close();
}
