
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/Document.cpp

// CODE REVIEW 2020-04-26 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-04-26 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/Document.h>

// ===== HILib ==============================================================
#include "Utils.h"

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
                // NOT TESTED Document.Error
                //            fclose fail
                throw std::exception("ERROR  fclose(  )  failed", lRet);
            }
        }
    }

    // aDocument [-K-;RW-]
    void Document::Create(Document * aDocument)
    {
        assert(NULL != aDocument);

        assert(!mFlags.mDoNotClose);

        assert(NULL == mFile);

        mFile = aDocument->GetFile();
        assert(NULL != mFile);

        mFlags.mDoNotClose = true;
    }

    // aName [---;R--]
    void Document::Create(FolderId aFolder, const char * aName)
    {
        assert(NULL != aName);

        assert(NULL == mFile);

        char lFileName[2048];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, mExtension);

        errno_t lErr = fopen_s(&mFile, lFileName, "wb");
        if (0 != lErr)
        {
            // NOT TESTED Document.Error
            //            fopen_s fail
            throw std::exception("ERROR  fopen( , ,  )  failed", lErr);
        }

        assert(NULL != mFile);

        mName = aName;
    }

    // TODO Document.Create

    // aFolder [---;R--]
    // aName   [---;R--]
    void Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);
    }

    // TODO Document.Delete

    bool Document::Delete()
    {
        return false;
    }

    // NOT TESTED Document.DeleteOnDestruction

    void Document::DeleteOnDestruction()
    {
        mFlags.mDeleteOnDestruction = true;
    }

    // Protected
    /////////////////////////////////////////////////////////////////////////

    // aExtension [-K-;RW-]
    Document::Document(const char * aExtension)
        : mExtension(aExtension)
        , mFile     (NULL      )
    {
        assert(NULL != aExtension);

        mFlags.mDeleteOnDestruction = false;
        mFlags.mDoNotClose          = false;
    }

}
