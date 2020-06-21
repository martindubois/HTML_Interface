
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/XML_Document.cpp

// CODE REVIEW 2020-06-21 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-21 KMS - Martin Dubois, P.Eng.

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

    void XML_Document::Attribute_Set(unsigned int aAttr, unsigned int aValue)
    {
        assert(mAttrQty > aAttr);

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

    void XML_Document::Attribute_Set(const char * aAttr, unsigned int aValue)
    {
        assert(NULL != aAttr);

        char lValue[16];

        int lRet = sprintf_s(lValue, "%u", aValue);
        Utl_VerifyReturn(lRet, sizeof(lValue));

        XML_Document::Attribute_Set(aAttr, lValue);
    }

    void XML_Document::Tag(unsigned int aTag)
    {
        assert(mTagQty > aTag);

        const Data & lTI = mTagList[aTag];

        if (0 != (FLAG_TAG_MANDATORY_ATTR & lTI.mFlags))
        {
            PushMandatoryAttributes(aTag);
        }

        XML_Document::Tag(lTI.mName, lTI.mFlags);
    }

    void XML_Document::Tag(const char * aTag, unsigned int aFlags)
    {
        assert(NULL != aTag);

        int lRet = fprintf(GetFile(), "<%s", aTag);
        Utl_VerifyReturn(lRet);

        PopAttributes(aFlags);

        Write((0 == (FLAG_TAG_NO_CLOSE & aFlags)) ? " />" : ">");
    }

    // NOT TESTED XML_Document.Tag
    //            Tag with mandatory attribute and text in it.

    void XML_Document::Tag(unsigned int aTag, const char * aText)
    {
        assert(mTagQty >  aTag );
        assert(NULL    != aText);

        const Data & lTI = mTagList[aTag];

        if (0 != (FLAG_TAG_MANDATORY_ATTR & lTI.mFlags))
        {
            PushMandatoryAttributes(aTag);
        }

        XML_Document::Tag(lTI.mName, aText);
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
                Utl_ThrowError("ERROR", __LINE__, "fprintf( , ,  )  failed");
            }

        Tag_End();
    }

    void XML_Document::Tag_Begin(unsigned int aTag)
    {
        assert(mTagQty > aTag);

        const Data & lTI = mTagList[aTag];

        if (0 != (FLAG_TAG_MANDATORY_ATTR & lTI.mFlags))
        {
            PushMandatoryAttributes(aTag);
        }

        XML_Document::Tag_Begin(lTI.mName);
    }

    void XML_Document::Tag_Begin(const char * aTag, unsigned int aFlags)
    {
        assert(NULL != aTag);

        int lRet = fprintf(GetFile(), "<%s", aTag);
        Utl_VerifyReturn(lRet);

        PopAttributes(aFlags);

        Write(">");

        mTags.push_back(aTag);
    }

    void XML_Document::Tag_End(bool aNewLine)
    {
        assert(!mTags.empty());

        if (aNewLine)
        {
            Document::NewLine();

            Indent(static_cast<unsigned int>(mTags.size()) - 1);
        }

        int lRet = fprintf(GetFile(), "</%s>", mTags.back().c_str());
        Utl_VerifyReturn(lRet);

        mTags.pop_back();
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

        Write("<!--");

        Document::Comment_Begin();

        NewLine();
    }

    void XML_Document::Comment_End()
    {
        Document::Comment_End();

        NewLine();

        Write("-->");

        NewLine();
    }

    void XML_Document::NewLine()
    {
        Document::NewLine();

        Indent(static_cast<unsigned int>(mTags.size()) + (InComment() ? 1 : 0));
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

    // aAttr [-K-;R--]
    void XML_Document::AddTagAttribute(unsigned int aTag, const char * aAttr)
    {
        assert(NULL != aAttr);

        mTagAttribute.insert(AttributeMap::value_type(aTag, aAttr));
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void XML_Document::PopAttribute()
    {
        int lRet = fprintf(GetFile(), "%s", mAttributes.front().c_str());
        mAttributes.pop_front();

        Utl_VerifyReturn(lRet);
    }

    void XML_Document::PopAttributes()
    {
        while (!mAttributes.empty())
        {
            PopAttribute();
        }
    }

    void XML_Document::PopAttributes(unsigned int aFlags)
    {
        if (0 == (FLAG_TAG_NO_OPT_ATTR & aFlags))
        {
            PopAttributes();
        }
        else
        {
            if (0 != (FLAG_TAG_MANDATORY_ATTR & aFlags))
            {
                PopAttribute();
            }
        }
    }

    void XML_Document::PushMandatoryAttributes(unsigned int aTag)
    {
        AttributeMap::const_iterator lAttr = mTagAttribute.find(aTag);
        assert(mTagAttribute.end() != lAttr);

        mAttributes.push_front(lAttr->second);
    }

    void XML_Document::Write(const char * aText)
    {
        assert(NULL != aText);

        int lRet = fprintf(GetFile(), aText);
        Utl_VerifyReturn(lRet);
    }

}
