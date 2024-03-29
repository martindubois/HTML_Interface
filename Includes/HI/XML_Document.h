
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/XML_Document.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C++ ================================================================
#include <list>
#include <map>
#include <string>

// ===== Includes ===========================================================
#include <HI/Document.h>

namespace HI
{

    /// \brief XML_Document
    class XML_Document : public Document
    {

    public:

        /// \brief Data
        class Data
        {

        public:

            const char * mIdName;
            const char * mName  ;

            unsigned int mFlags;

        };

        enum
        {
            FLAG_TAG_MANDATORY_ATTR = 0x00000001,
            FLAG_TAG_NO_CLOSE       = 0x00000002,
            FLAG_TAG_NO_OPT_ATTR    = 0x00000004,
        };

        /// \brief Info
        class Info
        {

        public:

            const char * mIdName;
            unsigned int mIndex ;
            const char * mName  ;

        };

        typedef enum
        {
            UNIT_NONE   ,
            UNIT_PERCENT,
            UNIT_PIXEL  ,

            UNIT_QTY
        }
        Unit;

        /// \param aOut See Info
        /// \param aIn  See Data
        static void Info_Copy(Info * aOut, const Data & aIn);

        /// \param aOut See Info
        /// \param aIn  See Data
        static void Info_Init(Info * aOut, const Data & aIn);

        /// \param aAttribute The attribute index
        /// \param aValue     The attribute value
        /// \exception std::exception
        void Attribute_Set(unsigned int aAttribute, const char * aValue);

        /// \param aAttribute The attribute index
        /// \param aValue     The attribute value
        /// \exception std::exception
        void Attribute_Set(unsigned int aAttribute, unsigned int aValue);

        /// \param aAttribute The attribute index
        /// \param aValue     The attribute value
        /// \param aUnit      See HI::XML_Document::Unit
        /// \exception std::exception
        void Attribute_Set(unsigned int aAttribute, unsigned int aValue, Unit aUnit);

        /// \param aAttribute The attribute index
        /// \param aValue     The attribute value
        /// \param aUnit      Unit
        /// \exception std::exception
        void Attribute_Set(unsigned int aAttribute, unsigned int aValue, const char * aUnit);

        /// \param aAttribute The attribute name
        /// \param aValue     The attribute value
        /// \exception std::exception
        void Attribute_Set(const char * aAttribute, const char * aValue);

        /// \param aAttribute The attribute name
        /// \param aValue     The attribute value
        /// \exception std::exception
        void Attribute_Set(const char * aAttribute, unsigned int aValue);

        /// \param aAttribute The attribute name
        /// \param aValue     The attribute value
        /// \param aUnit      See HI::XML_Document::Unit
        /// \exception std::exception
        void Attribute_Set(const char * aAttribute, unsigned int aValue, Unit aUnit);

        /// \param aAttribute The attribute name
        /// \param aValue     The attribute value
        /// \param aUnit      Unit
        /// \exception std::exception
        void Attribute_Set(const char * aAttribute, unsigned int aValue, const char * aUnit);

        /// \param aTag The tag index
        /// \exception std::exception
        void Tag(unsigned int aTag);

        /// \param aTag   The tag name
        /// \param aFlags See FLAG_TAG_...
        /// \exception std::exception
        void Tag(const char * aTag, unsigned int aFlags = 0);

        /// \param aTag  The tag index
        /// \param aText The text to put into the tag
        /// \exception std::exception
        void Tag(unsigned int aTag, const char * aText);

        /// \param aTag  The tag name
        /// \param aText The text to put into the tag
        /// \exception std::exception
        void Tag(const char * aTag, const char * aText);

        /// \param aTag  The tag index
        /// \exception std::exception
        void Tag_Begin(unsigned int aTag);

        /// \param aTag   The tag name
        /// \param aFlags See FLAG_TAG_...
        /// \exception std::exception
        void Tag_Begin(const char * aTag, unsigned int aFlags = 0);

        /// \param aNewLine Set to true to move to a new line before closing the tag.
        /// \exception std::exception
        void Tag_End(bool aNewLine = false);

        /// \param aTag  The tag index
        /// \exception std::exception
        void Tag_NoAttribute(unsigned int aTag);

        /// \param aTag  The tag name
        /// \exception std::exception
        void Tag_NoAttribute(const char * aTag);

        // ===== Document ===================================================

        virtual ~XML_Document();

        virtual void Close();

        virtual void Comment_Begin();
        virtual void Comment_End  ();

        virtual void NewLine();

    protected:

        /// \param aExtension The file extension (without the dot)
        /// \param aAttrQty   The number of known attributes
        /// \param aAttrList  The information about the known attributes
        /// \param aTagQty    The number of known tags
        /// \param aTagList   The information about the known tags
        XML_Document(const char * aExtension, unsigned int aAttrQty, const Data * aAttrList, unsigned int aTagQty, const Data * aTagList);

        /// \param aTag  The tag index
        /// \param aAttr The attribute string that must always be used with the tag. This one must start with a space.
        void AddTagAttribute(unsigned int aTag, const char * aAttr);

    private:

        void PopAttribute ();
        void PopAttributes();
        void PopAttributes(unsigned int aFlags);

        void PushMandatoryAttributes(unsigned int aTag);

        void Write(const char * aText);

        typedef std::map<unsigned int, const char *> AttributeMap;
        typedef std::list<std::string> StringList;

        StringList mAttributes;
        StringList mTags      ;

        unsigned int mAttrQty ;
        const Data * mAttrList;

        AttributeMap mTagAttribute;
        unsigned int mTagQty ;
        const Data * mTagList;

    };

}
