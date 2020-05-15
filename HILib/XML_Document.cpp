
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/XML_Document.cpp

// CODE REVIEW 2020-05-15 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-15 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/XML_Document.h>

// ===== HILib ==============================================================
#include "Utils.h"

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    // TESTED XML_Document.Enumerate
    //        GenDoc.exe enumerate HTML, and SVG, attributes and tags. So, it
    //        uses Info_Copy and Info_Init.

    void XML_Document::Info_Copy(Info * aOut, const Data & aData)
    {
        assert(NULL !=   aOut  );
        assert(NULL != (&aData));

        aOut->mIdName = aData.mIdName;
        aOut->mName   = aData.mName  ;
    }

    // aOut [---;-W-]
    void XML_Document::Info_Init(Info * aOut, const Data & aData)
    {
        assert(NULL !=   aOut  );
        assert(NULL != (&aData));

        memset(aOut, 0, sizeof(*aOut));

        Info_Copy(aOut, aData);
    }

    void XML_Document::Attribute_Set(unsigned int aAttr, const char * aValue)
    {
        assert(mAttrQty >  aAttr );
        assert(NULL     != aValue);

        XML_Document::Attribute_Set(mAttrList[aAttr].mName, aValue);
    }

    void XML_Document::Attribute_Set(const char * aAttr, const char * aValue)
    {
        assert(NULL != aAttr );
        assert(NULL != aValue);

        char lStr[256];

        int lRet = sprintf_s(lStr, " %s=\"%s\"", aAttr, aValue);
        Utl_VerifyReturn(lRet, sizeof(lStr));

        mAttributes.push_back(lStr);
    }

    void XML_Document::Tag(unsigned int aTag)
    {
        assert(mTagQty > aTag);

        XML_Document::Tag(mTagList[aTag].mName);
    }

    void XML_Document::Tag(const char * aTag)
    {
        assert(NULL != aTag);

        int lRet = fprintf(GetFile(), "<%s", aTag);
        Utl_VerifyReturn(lRet);

        while (!mAttributes.empty())
        {
            lRet = fprintf(GetFile(), "%s", mAttributes.front().c_str());
            mAttributes.pop_front();

            Utl_VerifyReturn(lRet);
        }

        lRet = fprintf(GetFile(), ">");
        Utl_VerifyReturn(lRet);
    }

    void XML_Document::Tag(unsigned int aTag, const char * aText)
    {
        assert(mTagQty >  aTag );
        assert(NULL    != aText);

        XML_Document::Tag(mTagList[aTag].mName, aText);
    }

    void XML_Document::Tag(const char * aTag, const char * aText)
    {
        assert(NULL != aTag );
        assert(NULL != aText);

        Tag_Begin(aTag);

            int lRet = fprintf(GetFile(), "%s", aText);
            if (0 > lRet)
            {
                // NOT TESTED XML_Document.Tag.Error
                //            fprintf( , ,  ) fails.
                throw std::exception("ERROR  120  fprintf( , ,  )  failed");
            }

        Tag_End();
    }

    void XML_Document::Tag_Begin(unsigned int aTag)
    {
        assert(mTagQty > aTag);

        XML_Document::Tag_Begin(mTagList[aTag].mName);
    }

    void XML_Document::Tag_Begin(const char * aTag)
    {
        assert(NULL != aTag);

        Tag(aTag);

        mTags.push_back(aTag);
    }

    void XML_Document::Tag_End(bool aNewLine)
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

    // NOT TESTED  XML_Document.Attribute
    //             Output tag without consuming queued attributes.

    void XML_Document::Tag_NoAttribute(unsigned int aTag)
    {
        assert(mTagQty > aTag);

        Tag_NoAttribute(mTagList[aTag].mName);
    }

    void XML_Document::Tag_NoAttribute(const char * aTag)
    {
        assert(NULL != aTag);

        int lRet = fprintf(GetFile(), "<%s", aTag);
        Utl_VerifyReturn(lRet);

        lRet = fprintf(GetFile(), ">");
        Utl_VerifyReturn(lRet);
    }

    // ===== Document =======================================================

    XML_Document::~XML_Document()
    {
        if (!IsClosed())
        {
            Close();
        }
    }

    void XML_Document::Close()
    {
        while (!mTags.empty())
        {
            Tag_End(true);
        }

        Document::Close();
    }

    void XML_Document::Comment_Begin()
    {
        NewLine();

        int lRet = fprintf(GetFile(), "<!--");
        Utl_VerifyReturn(lRet);

        Document::Comment_Begin();

        NewLine();
    }

    void XML_Document::Comment_End()
    {
        Document::Comment_End();

        NewLine();

        int lRet = fprintf(GetFile(), "-->");
        Utl_VerifyReturn(lRet);

        NewLine();
    }

    void XML_Document::NewLine()
    {
        Document::NewLine();

        Indent(mTags.size() + (InComment() ? 1 : 0));
    }

    // Protected
    /////////////////////////////////////////////////////////////////////////

    // aExtension [-K-;R--]
    XML_Document::XML_Document(const char * aExtension, unsigned int aAttrQty, const Data * aAttrList, unsigned int aTagQty, const Data * aTagList)
        : Document (aExtension)
        , mAttrQty (aAttrQty  ) 
        , mAttrList(aAttrList )
        , mTagQty  (aTagQty   )
        , mTagList (aTagList  )
    {
        assert(NULL != aExtension);
        assert(   0 <  aAttrQty  );
        assert(NULL != aAttrList );
        assert(   0 <  aTagQty   );
        assert(NULL != aTagList  );
    }

}
