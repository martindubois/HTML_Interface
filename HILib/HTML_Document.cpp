
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/HTML_Document.cpp

// CODE REVIEW 2020-05-15 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-15 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/HTML_Document.h>

// ===== HILib ==============================================================
#include "Utils.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

static const HI::XML_Document::Data ATTRIBUTES[HI::HTML_Document::ATTR_QTY] =
{
    { "ATTR_HREF" , "href"  },
    { "ATTR_STYLE", "style" },
};

static const HI::XML_Document::Data TAGS[HI::HTML_Document::TAG_QTY] =
{
    { "TAG_A"      , "a"             },
    { "TAG_BODY"   , "body"          },
    { "TAG_CODE"   , "code"          },
    { "TAG_DETAILS", "details"       },
    { "TAG_DOCTYPE", "!DOCTYPE html" },
    { "TAG_HEAD"   , "head"          },
    { "TAG_H1"     , "h1"            },
    { "TAG_H2"     , "h2"            },
    { "TAG_HR"     , "hr"            },
    { "TAG_HTML"   , "html"          },
    { "TAG_I"      , "i"             },
    { "TAG_P"      , "p"             },
    { "TAG_STYLE"  , "style"         },
    { "TAG_SUMMARY", "summary"       },
    { "TAG_TABLE"  , "table"         },
    { "TAG_TD"     , "td"            },
    { "TAG_TH"     , "th"            },
    { "TAG_TITLE"  , "title"         },
    { "TAG_TR"     , "tr"            },
};

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // TESTED HTML_Document.Attributes.Enumerate
    //        GenDoc.exe uses Attribute_GetFirst and Attribute_GetNext.

    // aOut [---;-W-]
    void HTML_Document::Attribute_GetFirst(Info * aOut)
    {
        assert(NULL != aOut);

        Info_Init(aOut, ATTRIBUTES[0]);
    }

    bool HTML_Document::Attribute_GetNext(Info * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndex++;

        if (ATTR_QTY <= aInOut->mIndex)
        {
            return false;
        }

        Info_Copy(aInOut, ATTRIBUTES[aInOut->mIndex]);

        return true;
    }

    // TESTED HTML_Document.Tags.Enumerate
    //        GenDoc.exe uses Tag_GetFirst and Tag_GetNext.

    // aOut [---;-W-]
    void HTML_Document::Tag_GetFirst(Info * aOut)
    {
        assert(NULL != aOut);

        Info_Init(aOut, TAGS[0]);
    }

    bool HTML_Document::Tag_GetNext(Info * aInOut)
    {
        assert(NULL != aInOut);

        aInOut->mIndex++;

        if (TAG_QTY <= aInOut->mIndex)
        {
            return false;
        }

        Info_Copy(aInOut, TAGS[aInOut->mIndex]);

        return true;
    }

    HTML_Document::HTML_Document() : XML_Document("html", ATTR_QTY, ATTRIBUTES, TAG_QTY, TAGS)
    {
    }

    void HTML_Document::Create(FolderId aFolder, const char * aName, const char * aTitle)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Create(aFolder, aName);

        Create(aTitle);
    }

    void HTML_Document::Create(const char * aFolder, const char * aName, const char * aTitle)
    {
        assert(NULL != aName);

        Create(aFolder, aName);

        Create(aTitle);
    }

    // ===== Document ======================================================

    HTML_Document::~HTML_Document()
    {
    }

    void HTML_Document::Create(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Document::Create(aFolder, aName);

        Create();
    }

    void HTML_Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        Document::Create(aFolder, aName);

        Create();
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void HTML_Document::Create()
    {
        Tag(TAG_DOCTYPE);

        Comment("Generated using the HTML_Interface library");

        Tag_Begin(TAG_HTML);
        NewLine();
        Tag_Begin(TAG_HEAD);
        NewLine();
    }

    void HTML_Document::Create(const char * aTitle)
    {
        assert(NULL != aTitle);

        Tag(TAG_TITLE, aTitle);
        Tag_End(true);
        NewLine();
        Tag_Begin(TAG_BODY);
        NewLine();
    }

}
