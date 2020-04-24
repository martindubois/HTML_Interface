
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/Document.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================

#include <HI/Document.h>

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

static void GetFolderName(char * aOut, unsigned int aOutSize_byte, HI::FolderId aFolder);

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    Document::~Document()
    {
    }

    FILE * Document::GetFile()
    {
        assert(NULL != mFile);

        return mFile;
    }

    bool Document::IsClosed() const
    {
        return (NULL == mFile);
    }

    void Document::Close()
    {
        assert(NULL != mFile);

        FILE * lFile = mFile;

        mFile = NULL;

        if (!mFlags.mDoNotClose)
        {
            int lRet = fclose(lFile);
            if (0 != lRet)
            {
                throw std::exception("fclose(  ) failed", lRet);
            }
        }
    }

    void Document::Create(Document * aDocument)
    {
        assert(NULL != aDocument);

        assert(!mFlags.mDoNotClose);

        assert(NULL == mFile);

        mFile = aDocument->GetFile();
        assert(NULL != mFile);

        mFlags.mDoNotClose = true;
    }

    void Document::Create(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        assert(NULL == mFile);

        char lFolder  [1024];
        char lFullName[2048];
        int  lRet;

        switch (aFolder)
        {
        case FOLDER_APP_STATIC:
        case FOLDER_EXECUTABLE:
        case FOLDER_TEMP_APP  :
            GetFolderName(lFolder, sizeof(lFolder), aFolder);
            lRet = sprintf_s(lFullName, "%s\\%s.%s", lFolder, aName, mExtension);
            break;

        case FOLDER_CURRENT:
            lRet = sprintf_s(lFullName, "%s.%s", aName, mExtension);
            break;

        default: assert(false);
        }

        assert(0 < lRet);

        errno_t lErr = fopen_s(&mFile, lFullName, "wb");
        if (0 != lErr)
        {
            throw std::exception("fopen( , ,  ) failed", lErr);
        }

        assert(NULL != mFile);

        mName = aName;
    }

    void Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        // TODO
    }

    bool Document::Delete()
    {
        // TODO
        return false;
    }

    void Document::DeleteOnDestruction()
    {
        mFlags.mDeleteOnDestruction = true;
    }

    // Protected
    /////////////////////////////////////////////////////////////////////////

    Document::Document(const char * aExtension)
        : mExtension(aExtension)
        , mFile     (NULL      )
    {
        assert(NULL != aExtension);

        mFlags.mDeleteOnDestruction = false;
        mFlags.mDoNotClose          = false;
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// aOut [---;-W-]
void GetFolderName(char * aOut, unsigned int aOutSize_byte, HI::FolderId aFolder)
{
    assert(NULL != aOut         );
    assert(   0 <  aOutSize_byte);

    memset(aOut, 0, aOutSize_byte);

    switch (aFolder)
    {
    case HI::FOLDER_APP_STATIC:
        // TODO

    case HI::FOLDER_EXECUTABLE:
        // TODO

    case HI::FOLDER_TEMP_APP:
        // TODO

    default: assert(false);
    }
}
