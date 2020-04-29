
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/HTML_Document.cpp

// CODE REVIEW 2020-04-29 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-04-29 KMS - Martin Dubois, P.Eng.

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

    HTML_Document::HTML_Document() : Document("html"), mInComment(false)
    {
    }

    // aName  [---;R--]
    // aTitle [---;R--]
    void HTML_Document::Create(FolderId aFolder, const char * aName, const char * aTitle)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Create(aFolder, aName);

        Create(aTitle);
    }

    // aFolder [---;R--]
    // aName   [---;R--]
    // aTitle  [---;R--]
    void HTML_Document::Create(const char * aFolder, const char * aName, const char * aTitle)
    {
        assert(NULL != aName);

        Create(aFolder, aName);

        Create(aTitle);
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

    void HTML_Document::Tag(HTML_Tag aTag)
    {
        assert(TAG_QTY > aTag);

        Tag_Internal(aTag);
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
                throw std::exception("ERROR  092  fprintf( , ,  )  failed");
            }

        Tag_End();
    }

    void HTML_Document::Tag_Begin(HTML_Tag aTag)
    {
        assert(TAG_QTY > aTag);

        const char * lName = Tag_Internal(aTag);

        mTags.push_back(lName);
    }

    void HTML_Document::Tag_End(bool aNewLine)
    {
        assert(!mTags.empty());

        if (aNewLine)
        {
            Document::NewLine();

            Indent(mTags.size() - 1);
        }

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
            Tag_End(true);
        }

        Document::Close();
    }

    void HTML_Document::Comment_Begin()
    {
        assert(!mInComment);

        NewLine();

        int lRet = fprintf(GetFile(), "<!--");
        Utl_VerifyReturn(lRet);

        mInComment = true;

        NewLine();
    }

    void HTML_Document::Comment_End()
    {
        assert(mInComment);

        mInComment = false;

        NewLine();

        int lRet = fprintf(GetFile(), "-->");
        Utl_VerifyReturn(lRet);

        NewLine();
    }

    // aName [---;R--]
    void HTML_Document::Create(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Document::Create(aFolder, aName);

        Create();
    }

    // aFolder [---;R--]
    // aName   [---;R--]
    void HTML_Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        Document::Create(aFolder, aName);

        Create();
    }

    void HTML_Document::NewLine()
    {
        Document::NewLine();

        Indent(mTags.size() + (mInComment ? 1 : 0));
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

    // aTitle [---;R--]
    void HTML_Document::Create(const char * aTitle)
    {
        assert(NULL != aTitle);

        Tag(TAG_TITLE, aTitle);
        Tag_End(true);
        NewLine();
        Tag_Begin(TAG_BODY);
        NewLine();
    }

    const char * HTML_Document::Tag_Internal(HTML_Tag aTag)
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

        return lTI.mName;
    }

}
