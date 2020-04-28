
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

        virtual void Close();

        virtual void Comment(const char * aText) = 0;

        virtual void Comment_Begin() = 0;

        virtual void Comment_End() = 0;

        virtual void Create(Document * aDocument);

        virtual void Create(FolderId aFolder, const char * aName);

        virtual void Create(const char * aFolder, const char * aName);

        virtual void Delete();

        virtual void DeleteOnDestruction();

    protected:

        Document(const char * aExtension);

    private:

        void Create(const char * aFileName);

        struct
        {
            unsigned mDeleteOnDestruction : 1;
            unsigned mDoNotClose          : 1;

            unsigned mReserved0 : 30;
        }
        mFlags;

        const char * mExtension;
        FILE       * mFile     ;
        std::string  mFileName ;
        std::string  mName     ;

    };

}
