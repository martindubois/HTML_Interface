
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/HTML_Document.cpp

// CODE REVIEW 2020-04-28 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-04-28 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/HTML_Document.h>

// ===== HILib ==============================================================
#include "Utils.h"

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    HTML_Document::HTML_Document() : Document("html")
    {
    }

    // TODO HTML_Document.Notices
    //      Add a notices indicating the file is generated using
    //      HTML_Interface.

    // aName  [---;R--]
    // aTitle [---;R--]
    void HTML_Document::Create(FolderId aFolder, const char * aName, const char * aTitle)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Create(aFolder, aName);

        Tag(TAG_TITLE, aTitle);
        Tag_End();
        Tag_Begin(TAG_BODY);

        mEndBody = true;
    }

    // aFolder [---;R--]
    // aName   [---;R--]
    // aTitle  [---;R--]
    void HTML_Document::Create(const char * aFolder, const char * aName, const char * aTitle)
    {
        assert(NULL != aName);

        Create(aFolder, aName);

        Tag(TAG_TITLE, aTitle);
        Tag_End();
        Tag_Begin(TAG_BODY);

        mEndBody = true;
    }

    // aValue [---;R--]
    void HTML_Document::Attribute_Set(HTML_Attribute aAttr, const char * aValue)
    {
        assert(ATTR_QTY >  aAttr );
        assert(NULL     != aValue);

        HTML_AttributeInfo lAI;

        HTML_Attributes::FindByIndex(&lAI, aAttr);

        char lStr[128];

        int lRet = sprintf_s(lStr, " %s=\"%s\"", lAI.mName, aValue);
        Utl_VerifyReturn(lRet, sizeof(lStr));

        mAttributes.push_back(lStr);
    }

    // aText [---;R--]
    void HTML_Document::Tag(HTML_Tag aTag, const char * aText)
    {
        Tag_Begin(aTag);

            int lRet = fprintf(GetFile(), "%s", aText);
            if (0 > lRet)
            {
                // NOT TESTED HTML_Document.Error
                //            fprintf fail
                throw std::exception("ERROR  fprintf( , ,  )  failed");
            }

        Tag_End();
    }

    void HTML_Document::Tag_Begin(HTML_Tag aTag)
    {
        assert(TAG_QTY > aTag);

        HTML_TagInfo lTI;

        HTML_Tags::FindByIndex(&lTI, aTag);

        int lRet = fprintf(GetFile(), "<%s", lTI.mName);
        Utl_VerifyReturn(lRet);

        while (!mAttributes.empty())
        {
            fprintf(GetFile(), "%s", mAttributes.front().c_str());
            mAttributes.pop_front();
        }

        lRet = fprintf(GetFile(), ">");
        Utl_VerifyReturn(lRet);

        mTags.push_back(lTI.mName);
    }

    void HTML_Document::Tag_End()
    {
        assert(!mTags.empty());

        int lRet = fprintf(GetFile(), "</%s>", mTags.back().c_str());
        Utl_VerifyReturn(lRet);

        mTags.pop_back();
    }

    // ===== Document ======================================================

    HTML_Document::~HTML_Document()
    {
        if (!IsClosed())
        {
            Close();
        }
    }

    void HTML_Document::Close()
    {
        while (!mTags.empty())
        {
            Tag_End();
        }

        Document::Close();
    }

    // TODO HTML_Document.Comment

    // aText [---;R--]
    void HTML_Document::Comment(const char * aText)
    {
    }

    void HTML_Document::Comment_Begin()
    {
    }

    void HTML_Document::Comment_End()
    {
    }

    // aName [---;R--]
    void HTML_Document::Create(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Document::Create(aFolder, aName);

        Tag_Begin(TAG_HTML);
        Tag_Begin(TAG_HEAD);
    }

    // aFolder [---;R--]
    // aName   [---;R--]
    void HTML_Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        Document::Create(aFolder, aName);

        Tag_Begin(TAG_HTML);
        Tag_Begin(TAG_HEAD);
    }

}
