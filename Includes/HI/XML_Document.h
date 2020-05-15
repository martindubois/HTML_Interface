
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/XML_Document.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C++ ================================================================
#include <list>
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

        };

        /// \brief Info
        class Info
        {

        public:

            const char * mIdName;
            unsigned int mIndex ;
            const char * mName  ;

        };

        static void Info_Copy(Info * aOut, const Data & aIn);

        static void Info_Init(Info * aOut, const Data & aIn);

        /// \exception std::exception
        void Attribute_Set(unsigned int aAttribute, const char * aValue);

        /// \exception std::exception
        void Attribute_Set(const char * aAttribute, const char * aValue);

        /// \exception std::exception
        void Tag(unsigned int aTag);

        /// \exception std::exception
        void Tag(const char * aTag);

        /// \exception std::exception
        void Tag(unsigned int aTag, const char * aText);

        /// \exception std::exception
        void Tag(const char * aTag, const char * aText);

        /// \exception std::exception
        void Tag_Begin(unsigned int aTag);

        /// \exception std::exception
        void Tag_Begin(const char * aTag);

        /// \exception std::exception
        void Tag_End(bool aNewLine = false);

        /// \exception std::exception
        void Tag_NoAttribute(unsigned int aTag);

        /// \exception std::exception
        void Tag_NoAttribute(const char * aTag);

        // ===== Document ===================================================

        virtual ~XML_Document();

        virtual void Close();

        virtual void Comment_Begin();
        virtual void Comment_End  ();

        virtual void NewLine();

    protected:

        XML_Document(const char * aExtension, unsigned int aAttrQty, const Data * aAttrList, unsigned int aTagQty, const Data * aTagList);

    private:

        typedef std::list<std::string> StringList;

        StringList mAttributes;
        StringList mTags      ;

        unsigned int mAttrQty ;
        const Data * mAttrList;

        unsigned int mTagQty ;
        const Data * mTagList;

    };

}
