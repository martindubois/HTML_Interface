
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/HI/Browser.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// ===== C++ ================================================================
#include <string>

// ===== Includes ===========================================================
#include <HI/Types.h>

namespace HI
{

    /// \brief Document
    class Document
    {

    public:

        virtual ~Document();

        FILE * GetFile();

        bool GetFileName(char * aOut, unsigned int aOutSize_byte) const;

        bool GetFolder(char * aOut, unsigned int aOutSize_byte) const;

        bool GetFullName(char * aOut, unsigned int aOutSize_byte) const;

        bool GetName(char * aOut, unsigned int aOutSize_byte) const;

        bool IsClosed() const;

        /// \exception std::exception
        virtual void Close();

        /// \exception std::exception
        virtual void Comment(const char * aText);

        /// \exception std::exception
        virtual void Comment_Begin();

        /// \exception std::exception
        virtual void Comment_End();

        virtual void Create(Document * aDocument);

        /// \exception std::exception
        virtual void Create(FolderId aFolder, const char * aName);

        /// \exception std::exception
        virtual void Create(const char * aFolder, const char * aName);

        /// \exception std::exception
        virtual void Delete();

        virtual void DeleteOnDestruction();

        /// \exception std::exception
        virtual void NewLine();

    protected:

        Document(const char * aExtension);

        bool InComment() const;

        void Indent(unsigned int aLevel);

    private:

        void Create(const char * aFileName);

        struct
        {
            unsigned mDeleteOnDestruction : 1;
            unsigned mDoNotClose          : 1;
            unsigned mInComment           : 1;

            unsigned mReserved0 : 29;
        }
        mFlags;

        const char * mExtension;
        FILE       * mFile     ;
        std::string  mFileName ;
        std::string  mName     ;

    };

}
