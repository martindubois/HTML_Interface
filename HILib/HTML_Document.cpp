
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/HTML_Document.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================

#include <HI/HTML_Document.h>

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    HTML_Document::HTML_Document() : Document("html")
    {
    }

    void HTML_Document::Create(FolderId aFolder, const char * aName, const char * aTitle)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Create(aFolder, aName);

        Tag(TAG_TITLE, aTitle);
        Tag_End(TAG_HEAD);
        Tag_Begin(TAG_BODY);

        mEndBody = true;
    }

    void HTML_Document::Create(const char * aFolder, const char * aName, const char * aTitle)
    {
        assert(NULL != aName);

        Create(aFolder, aName);

        Tag(TAG_TITLE, aTitle);
        Tag_End(TAG_HEAD);
        Tag_Begin(TAG_BODY);

        mEndBody = true;
    }

    void HTML_Document::Attribute_Set(HTML_Attribute aAttr, const char * aValue)
    {
        assert(ATTR_QTY >  aAttr );
        assert(NULL     != aValue);

        HTML_AttributeInfo lAI;

        HTML_Attributes::FindByIndex(&lAI, aAttr);

        char lStr[128];

        sprintf_s(lStr, " %s=\"%s\"", lAI.mName, aValue);

        mAttributes.push_back(lStr);
    }

    void HTML_Document::Tag(HTML_Tag aTag, const char * aText)
    {
        Tag_Begin(aTag);

            int lRet = fprintf(GetFile(), "%s", aText);
            if (0 > lRet)
            {
                throw std::exception("fprintf( , ,  ) failed", lRet);
            }

        Tag_End(aTag);
    }

    void HTML_Document::Tag_Begin(HTML_Tag aTag)
    {
        assert(TAG_QTY > aTag);

        HTML_TagInfo lTI;

        HTML_Tags::FindByIndex(&lTI, aTag);

        int lRet = fprintf(GetFile(), "<%s", lTI.mName);
        if (0 >= lRet)
        {
            throw std::exception("fprintf( , ,  ) failed", lRet);
        }

        while (!mAttributes.empty())
        {
            fprintf(GetFile(), "%s", mAttributes.front().c_str());
            mAttributes.pop_front();
        }

        lRet = fprintf(GetFile(), ">");
        if (0 >= lRet)
        {
            throw std::exception("fprintf( , ,  ) failed", lRet);
        }
    }

    void HTML_Document::Tag_End(HTML_Tag aTag)
    {
        assert(TAG_QTY > aTag);

        HTML_TagInfo lTI;

        HTML_Tags::FindByIndex(&lTI, aTag);

        int lRet = fprintf(GetFile(), "</%s>", lTI.mName);
        if (0 > lRet)
        {
            throw std::exception("fprintf( , ,  ) failed", lRet);
        }
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
        if (mEndBody)
        {
            Tag_End(TAG_BODY);
        }

        Tag_End(TAG_HTML);

        Document::Close();
    }

    void HTML_Document::Comment(const char * aText)
    {
        // TODO
    }

    void HTML_Document::Comment_Begin()
    {
        // TODO
    }

    void HTML_Document::Comment_End()
    {
        // TODO
    }

    void HTML_Document::Create(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        Document::Create(aFolder, aName);

        Tag_Begin(TAG_HTML);
        Tag_Begin(TAG_HEAD);
    }

    void HTML_Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        Document::Create(aFolder, aName);

        Tag_Begin(TAG_HTML);
        Tag_Begin(TAG_HEAD);
    }

}
