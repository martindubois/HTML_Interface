
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/Document.cpp

// CODE REVIEW 2020-06-21 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-21 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== Windows ============================================================
#include <Windows.h>

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
        if (mFlags.mDeleteOnDestruction)
        {
            Delete();
        }
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
                // NOT TESTED Document.Close.Error
                //            fclose(  ) fails.
                Utl_ThrowError("ERROR", __LINE__, "failed", lRet);
            }
        }
    }

    void Document::Comment(const char * aText)
    {
        assert(NULL != mFile);

        Comment_Begin();

            int lRet = fprintf(mFile, "%s", aText);
            if (0 > lRet)
            {
                // NOT TESTED Document.Comment.Error
                //            fprintf( , ,  ) fails.
                Utl_ThrowError("ERROR", __LINE__, "fprintf( , ,  )  failed", lRet);
            }

        Comment_End();
    }

    void Document::Comment_Begin()
    {
        assert(!mFlags.mInComment);

        mFlags.mInComment = true;
    }

    void Document::Comment_End()
    {
        assert(mFlags.mInComment);

        mFlags.mInComment = false;
    }

    // TESTED  Document.Create
    //         Create a document inside another document (GenDoc.exe)

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

    void Document::Create(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY >  aFolder);
        assert(NULL       != aName  );

        assert(NULL != mExtension);

        char lFileName[2048];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, mExtension);

        Create(lFileName);

        mName = aName;
    }

    // aFolder [--O;R--]
    void Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        assert(NULL != mExtension);

        char lFileName[2048];

        Utl_MakeFileName(lFileName, sizeof(lFileName), aFolder, aName, mExtension);

        Create(lFileName);

        mName = aName;
    }

    void Document::Delete()
    {
        if (!DeleteFile(mFileName.c_str()))
        {
            Utl_ThrowError("ERROR", __LINE__, "DeleteFile(  )  failed");
        }

        mFileName.clear();
    }

    void Document::DeleteOnDestruction()
    {
        mFlags.mDeleteOnDestruction = true;
    }

    void Document::NewLine()
    {
        assert(NULL != mFile);

        int lRet = fprintf(mFile, "\n");
        Utl_VerifyReturn(lRet);
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
        mFlags.mInComment           = false;
    }

    bool Document::InComment() const
    {
        return mFlags.mInComment;
    }

    void Document::Indent(unsigned int aLevel)
    {
        assert(NULL != mFile);

        for (unsigned int i = 0; i < aLevel; i++)
        {
            int lRet = fprintf(mFile, "    ");
            Utl_VerifyReturn(lRet);
        }
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void Document::Create(const char * aFileName)
    {
        assert(NULL != aFileName);

        assert(NULL == mFile);

        errno_t lErr = fopen_s(&mFile, aFileName, "wb");
        if (0 != lErr)
        {
            Utl_ThrowError("ERROR", __LINE__, "fopen( , ,  )  failed", lErr);
        }

        assert(NULL != mFile);

        mFileName = aFileName;
    }

}
