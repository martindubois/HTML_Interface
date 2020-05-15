
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
#include <HI/SVG_Document.h>

// ===== Common =============================================================
#include "../Common/Version.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define EXT_HTML ".html"

#define HEADER_ENUM_VALUE "Enum value"

#define NAME_CSS_COLOR_BY_BLUE  "CSS_ColorByBlue"
#define NAME_CSS_COLOR_BY_GREEN "CSS_ColorByGreen"
#define NAME_CSS_COLOR_BY_NAME  "CSS_ColorByName"
#define NAME_CSS_COLOR_BY_RED   "CSS_ColorByRed"
#define NAME_CSS_COLOR_BY_WHITE "CSS_ColorByWhite"

#define NAME_CSS_PROPERTY_BY_NAME "CSS_PropertyByName"

#define NAME_HTML_ATTRIBUTE_BY_NANE "HTML_AttributeByName"
#define NAME_HTML_TAG_BY_NAME       "HTML_TagByName"

#define NAME_INDEX "index"

#define NAME_SVG_ATTRIBUTE_BY_NAME "SVG_AttributeByName"
#define NAME_SVG_TAG_BY_NAME       "SVG_TagByName"

#define PREFIX_CSS  "CSS "
#define PREFIX_HTML "HTML "
#define PREFIX_SVG  "SVG "

#define STYLE_RIGHT "text-align: right;"

#define TITLE_ATTRIBUTE_BY_NAME "Attributes by Name"

#define TITLE_COLOR_BY_BLUE  "Colors by BLUE Component"
#define TITLE_COLOR_BY_GREEN "Colors by GREEN Component"
#define TITLE_COLOR_BY_NAME  "Colors by Name"
#define TITLE_COLOR_BY_RED   "Colors by RED Component"
#define TITLE_COLOR_BY_WHITE "Colors by WHITE Component"

#define TITLE_INDEX "HTML_Interface Documentation"

#define TITLE_PROPERTY_BY_NAME "Properties by Name"

#define TITLE_TAG_BY_NAME "Tags by Name"

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void GenerateAttribute(HI::HTML_Document * aDoc, const HI::XML_Document::Info & aAI);

static void GenerateBegin_Attributes(HI::HTML_Document * aDoc, const char * aName, const char * aTitle);
static void GenerateBegin_Tags      (HI::HTML_Document * aDoc, const char * aName, const char * aTitle);

static void ConfigBorders(HI::HTML_Document * aDoc);

static void GenerateCode(HI::HTML_Document * aDoc, const char * aCode);

static void GenerateComponent(HI::HTML_Document * aDoc, const char * aStyle, unsigned int aValue);

static void GenerateCSS_Colors    (const char * aName, const char * aTitle, HI::CSS_Colors::Order aOrder);
static void GenerateCSS_Properties();

static void GenerateHTML_Attributes();
static void GenerateHTML_Tags      ();

static void GenerateIndex();

static void GenerateLink(HI::HTML_Document * aDoc, const char * aName, const char * aTitle);

static void GenerateSVG_Attributes();
static void GenerateSVG_Tags      ();

static void GenerateTag(HI::HTML_Document * aDoc, const HI::XML_Document::Info & aAI);

// Entry point
/////////////////////////////////////////////////////////////////////////////

// aVector [---;R--][---;R--]
int main(int aCount, const char ** aVector)
{
    KMS_TOOL_BANNER("HTML_Interface", "GenDoc", VERSION_STR, VERSION_TYPE);

    assert(   1 <= aCount );
    assert(NULL != aVector);

    try
    {
        HI::Browser lBrowser;

        lBrowser.ParseArguments(aCount, aVector);

        GenerateCSS_Colors(NAME_CSS_COLOR_BY_BLUE , PREFIX_CSS TITLE_COLOR_BY_BLUE , HI::CSS_Colors::ORDER_BLUE );
        GenerateCSS_Colors(NAME_CSS_COLOR_BY_GREEN, PREFIX_CSS TITLE_COLOR_BY_GREEN, HI::CSS_Colors::ORDER_GREEN);
        GenerateCSS_Colors(NAME_CSS_COLOR_BY_NAME , PREFIX_CSS TITLE_COLOR_BY_NAME , HI::CSS_Colors::ORDER_NAME );
        GenerateCSS_Colors(NAME_CSS_COLOR_BY_RED  , PREFIX_CSS TITLE_COLOR_BY_RED  , HI::CSS_Colors::ORDER_RED  );
        GenerateCSS_Colors(NAME_CSS_COLOR_BY_WHITE, PREFIX_CSS TITLE_COLOR_BY_WHITE, HI::CSS_Colors::ORDER_WHITE);

        GenerateCSS_Properties();

        GenerateHTML_Attributes();
        GenerateHTML_Tags      ();

        GenerateSVG_Attributes();
        GenerateSVG_Tags      ();

        GenerateIndex();

        lBrowser.Start(HI::FOLDER_TEMP, NAME_INDEX);
    }
    catch (std::exception eE)
    {
        fprintf(stderr, "ERROR  098  EXCEPTION  %s\n", eE.what());
        return __LINE__;
    }
    catch (...)
    {
        fprintf(stderr, "ERROR  103  UNEXPECTED EXCEPTION\n");
        return __LINE__;
    }

    return 0;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void GenerateAttribute(HI::HTML_Document * aDoc, const HI::XML_Document::Info & aAI)
{
    assert(NULL !=   aDoc);
    assert(NULL != (&aAI));

    aDoc->Tag_Begin(HI::HTML_Document::TAG_TR);
        GenerateCode(aDoc, aAI.mIdName);
        GenerateCode(aDoc, aAI.mName  );
    aDoc->Tag_End();
}

void GenerateBegin_Attributes(HI::HTML_Document * aDoc, const char * aName, const char * aTitle)
{
    assert(NULL != aDoc  );
    assert(NULL != aName );
    assert(NULL != aTitle);

    aDoc->Create(HI::FOLDER_TEMP, aName, aTitle);

        ConfigBorders(aDoc);

        aDoc->Tag(HI::HTML_Document::TAG_H1, aTitle);

        aDoc->Tag_Begin(HI::HTML_Document::TAG_TABLE);

            aDoc->Tag_Begin(HI::HTML_Document::TAG_TR);
                aDoc->Tag(HI::HTML_Document::TAG_TH, HEADER_ENUM_VALUE);
                aDoc->Tag(HI::HTML_Document::TAG_TH, "Attribute");
            aDoc->Tag_End();
}

void GenerateBegin_Tags(HI::HTML_Document * aDoc, const char * aName, const char * aTitle)
{
    assert(NULL != aDoc  );
    assert(NULL != aName );
    assert(NULL != aTitle);

    aDoc->Create(HI::FOLDER_TEMP, aName, aTitle);

        ConfigBorders(aDoc);

        aDoc->Tag(HI::HTML_Document::TAG_H1, aTitle);

        aDoc->Tag_Begin(HI::HTML_Document::TAG_TABLE);
            aDoc->Tag_Begin(HI::HTML_Document::TAG_TR);
                aDoc->Tag(HI::HTML_Document::TAG_TH, HEADER_ENUM_VALUE);
                aDoc->Tag(HI::HTML_Document::TAG_TH, "Tag");
            aDoc->Tag_End();
}

void ConfigBorders(HI::HTML_Document * aDoc)
{
    assert(NULL != aDoc);

    HI::CSS_Document  lCSS;

    aDoc->Tag_Begin(HI::HTML_Document::TAG_STYLE);

        lCSS.Create(aDoc);

            lCSS.Rule_Begin_Element("td");
                lCSS.Property_Set(HI::CSS_Document::PROP_BORDER_STYLE, HI::CSS_Document::BORDER_STYLE_SOLID);
            lCSS.Rule_End();

        lCSS.Close();

    aDoc->Tag_End();
}

void GenerateCode(HI::HTML_Document * aDoc, const char * aCode)
{
    assert(NULL != aDoc );
    assert(NULL != aCode);

    aDoc->Tag_Begin(HI::HTML_Document::TAG_TD);
        aDoc->Tag(HI::HTML_Document::TAG_CODE, aCode);
    aDoc->Tag_End();
}

void GenerateComponent(HI::HTML_Document * aDoc, const char * aStyle, unsigned int aValue)
{
    assert(NULL != aDoc  );
    assert(NULL != aStyle);
    assert( 255 >= aValue);

    aDoc->Attribute_Set(HI::HTML_Document::ATTR_STYLE, aStyle);

    char lStr[64];

    sprintf_s(lStr, "%d", aValue);
    aDoc->Tag(HI::HTML_Document::TAG_TD, lStr);
}

void GenerateCSS_Colors(const char * aName, const char * aTitle, HI::CSS_Colors::Order aOrder)
{
    assert(NULL != aName );
    assert(NULL != aTitle);

    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_TEMP, aName, aTitle);

        ConfigBorders(&lDoc);

        lDoc.Tag(HI::HTML_Document::TAG_H1, aTitle);

        lDoc.Tag_Begin(HI::HTML_Document::TAG_TABLE);

            lDoc.Tag_Begin(HI::HTML_Document::TAG_TR);
                lDoc.Tag(HI::HTML_Document::TAG_TH, "Index" );
                lDoc.Tag(HI::HTML_Document::TAG_TH, HEADER_ENUM_VALUE);
                lDoc.Tag(HI::HTML_Document::TAG_TH, "Name"  );
                lDoc.Tag(HI::HTML_Document::TAG_TH, "Value" );
                lDoc.Tag(HI::HTML_Document::TAG_TH, "Red"   );
                lDoc.Tag(HI::HTML_Document::TAG_TH, "Green" );
                lDoc.Tag(HI::HTML_Document::TAG_TH, "Blue"  );
                lDoc.Tag(HI::HTML_Document::TAG_TH, "Sample");
            lDoc.Tag_End();

            HI::CSS_ColorInfo lCI;

            HI::CSS_Colors::GetFirst(&lCI, aOrder);

            do
            {
                lDoc.Tag_Begin(HI::HTML_Document::TAG_TR);

                    char lStr[64];

                    sprintf_s(lStr, "%d", lCI.mIndexBy);
                    lDoc.Tag(HI::HTML_Document::TAG_TD, lStr);

                    GenerateCode(&lDoc, lCI.mIdName);
                    GenerateCode(&lDoc, lCI.mName  );

                    sprintf_s(lStr, "#%06x", lCI.mValue);
                    GenerateCode(&lDoc, lStr);

                    GenerateComponent(&lDoc, "color: #ff0000; " STYLE_RIGHT, lCI.GetRed  ());
                    GenerateComponent(&lDoc, "color: #00ff00; " STYLE_RIGHT, lCI.GetGreen());
                    GenerateComponent(&lDoc, "color: #0000ff; " STYLE_RIGHT, lCI.GetBlue ());

                    sprintf_s(lStr, "background-color: %s;", lCI.mName);
                    lDoc.Attribute_Set(HI::HTML_Document::ATTR_STYLE, lStr);
                    lDoc.Tag(HI::HTML_Document::TAG_TD, "");

                lDoc.Tag_End();
            }
            while (HI::CSS_Colors::GetNext(&lCI));

        lDoc.Tag_End();

    lDoc.Close();
}

void GenerateCSS_Properties()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_TEMP, NAME_CSS_PROPERTY_BY_NAME, PREFIX_CSS TITLE_PROPERTY_BY_NAME);

        ConfigBorders(&lDoc);

        lDoc.Tag(HI::HTML_Document::TAG_H1, PREFIX_CSS TITLE_PROPERTY_BY_NAME);

        lDoc.Tag_Begin(HI::HTML_Document::TAG_TABLE);

            lDoc.Tag_Begin(HI::HTML_Document::TAG_TR);
                lDoc.Tag(HI::HTML_Document::TAG_TH, HEADER_ENUM_VALUE);
                lDoc.Tag(HI::HTML_Document::TAG_TH, "Property");
            lDoc.Tag_End();

            HI::CSS_Document::Info lPI;

            HI::CSS_Document::Property_GetFirst(&lPI);

            do
            {
                lDoc.Tag_Begin(HI::HTML_Document::TAG_TR);
                    GenerateCode(&lDoc, lPI.mIdName);
                    GenerateCode(&lDoc, lPI.mName  );
                lDoc.Tag_End();
            }
            while(HI::CSS_Document::Property_GetNext(&lPI));

        lDoc.Tag_End();

    lDoc.Close();
}

void GenerateHTML_Attributes()
{
    HI::HTML_Document lDoc;

    GenerateBegin_Attributes(&lDoc, NAME_HTML_ATTRIBUTE_BY_NANE, PREFIX_HTML TITLE_ATTRIBUTE_BY_NAME);

        HI::XML_Document::Info lAI;

        HI::HTML_Document::Attribute_GetFirst(&lAI);

        do
        {
            GenerateAttribute(&lDoc, lAI);
        }
        while(HI::HTML_Document::Attribute_GetNext(&lAI));

    lDoc.Close();
}

void GenerateHTML_Tags()
{
    HI::HTML_Document lDoc;

    GenerateBegin_Tags(&lDoc, NAME_HTML_TAG_BY_NAME, PREFIX_HTML TITLE_TAG_BY_NAME);

        HI::XML_Document::Info lTI;

        HI::HTML_Document::Tag_GetFirst(&lTI);

        do
        {
            GenerateTag(&lDoc, lTI);
        }
        while(HI::HTML_Document::Tag_GetNext(&lTI));

    lDoc.Close();
}

void GenerateIndex()
{
    HI::HTML_Document lDoc;

    lDoc.Create(HI::FOLDER_TEMP, NAME_INDEX, TITLE_INDEX);

        lDoc.Tag(HI::HTML_Document::TAG_H1, TITLE_INDEX);

        lDoc.Tag(HI::HTML_Document::TAG_H2, "CSS");

        GenerateLink(&lDoc, NAME_CSS_COLOR_BY_NAME    EXT_HTML, TITLE_COLOR_BY_NAME   );
        GenerateLink(&lDoc, NAME_CSS_COLOR_BY_BLUE    EXT_HTML, TITLE_COLOR_BY_BLUE   );
        GenerateLink(&lDoc, NAME_CSS_COLOR_BY_GREEN   EXT_HTML, TITLE_COLOR_BY_GREEN  );
        GenerateLink(&lDoc, NAME_CSS_COLOR_BY_RED     EXT_HTML, TITLE_COLOR_BY_RED    );
        GenerateLink(&lDoc, NAME_CSS_COLOR_BY_WHITE   EXT_HTML, TITLE_COLOR_BY_WHITE  );
        GenerateLink(&lDoc, NAME_CSS_PROPERTY_BY_NAME EXT_HTML, TITLE_PROPERTY_BY_NAME);

        lDoc.Tag(HI::HTML_Document::TAG_H2, "HTML");

        GenerateLink(&lDoc, NAME_HTML_ATTRIBUTE_BY_NANE EXT_HTML, TITLE_ATTRIBUTE_BY_NAME);
        GenerateLink(&lDoc, NAME_HTML_TAG_BY_NAME       EXT_HTML, TITLE_TAG_BY_NAME      );

        lDoc.Tag(HI::HTML_Document::TAG_H2, "SVG");

        GenerateLink(&lDoc, NAME_SVG_ATTRIBUTE_BY_NAME EXT_HTML, TITLE_ATTRIBUTE_BY_NAME);
        GenerateLink(&lDoc, NAME_SVG_TAG_BY_NAME       EXT_HTML, TITLE_TAG_BY_NAME      );

    lDoc.Close();
}

void GenerateLink(HI::HTML_Document * aDoc, const char * aName, const char * aTitle)
{
    assert(NULL != aDoc  );
    assert(NULL != aName );
    assert(NULL != aTitle);

    aDoc->Tag_Begin(HI::HTML_Document::TAG_P);
        aDoc->Attribute_Set(HI::HTML_Document::ATTR_HREF, aName);
        aDoc->Tag(HI::HTML_Document::TAG_A, aTitle);
    aDoc->Tag_End();
}

void GenerateSVG_Attributes()
{
    HI::HTML_Document lDoc;

    GenerateBegin_Attributes(&lDoc, NAME_SVG_ATTRIBUTE_BY_NAME, PREFIX_SVG TITLE_ATTRIBUTE_BY_NAME);

        HI::XML_Document::Info lAI;

        HI::SVG_Document::Attribute_GetFirst(&lAI);

        do
        {
            GenerateAttribute(&lDoc, lAI);
        }
        while(HI::SVG_Document::Attribute_GetNext(&lAI));

    lDoc.Close();
}

void GenerateSVG_Tags()
{
    HI::HTML_Document lDoc;

    GenerateBegin_Tags(&lDoc, NAME_SVG_TAG_BY_NAME, PREFIX_SVG TITLE_TAG_BY_NAME);

        HI::XML_Document::Info lTI;

        HI::SVG_Document::Tag_GetFirst(&lTI);

        do
        {
            GenerateTag(&lDoc, lTI);
        }
        while(HI::SVG_Document::Tag_GetNext(&lTI));

    lDoc.Close();
}

void GenerateTag(HI::HTML_Document * aDoc, const HI::XML_Document::Info & aTI)
{
    assert(NULL !=   aDoc);
    assert(NULL != (&aTI));

    aDoc->Tag_Begin(HI::HTML_Document::TAG_TR);
        aDoc->Tag(HI::HTML_Document::TAG_TD, aTI.mIdName);

        char lStr[64];

        sprintf_s(lStr, "&lt;%s&gt;", aTI.mName);
        GenerateCode(aDoc, lStr);
    aDoc->Tag_End();
}
