
// Author     KMS - Martin Dubois, P.Eng.
// Copyright  (C) 2020 KMS. All rights reserved.
// Product    HTML_Interface
// File       HILib/CPP_Document.cpp

// CODE REVIEW 2020-06-21 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-21 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/CPP_Document.h>

// ===== HILib ==============================================================
#include "Utils.h"

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    CPP_Document::CPP_Document() : Document("cpp")
    {
    }

    // ===== Document =======================================================

    CPP_Document::~CPP_Document()
    {
    }

    void CPP_Document::Close()
    {
        FILE * lFile = GetFile();
        assert(NULL != lFile);

        fprintf(lFile, EOL);
        fprintf(lFile, "    return lResult;" EOL);
        fprintf(lFile, "}" EOL);

        Document::Close();
    }

    void CPP_Document::Comment_Begin()
    {
        NewLine();

        int lRet = fprintf(GetFile(), "/*");
        Utl_VerifyReturn(lRet);

        Document::Comment_Begin();

        NewLine();
    }

    void CPP_Document::Comment_End()
    {
        Document::Comment_End();

        NewLine();

        int lRet = fprintf(GetFile(), "*/");
        Utl_VerifyReturn(lRet);

        NewLine();
    }

    void CPP_Document::Create(FolderId aFolder, const char * aName)
    {
        assert(FOLDER_QTY > aFolder);
        assert(NULL != aName);

        Document::Create(aFolder, aName);

        Create(aName);
    }

    void CPP_Document::Create(const char * aFolder, const char * aName)
    {
        assert(NULL != aName);

        Document::Create(aFolder, aName);

        Create(aName);
    }

    void CPP_Document::NewLine()
    {
        Document::NewLine();

        Indent(InComment() ? 1 : 0);
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    void CPP_Document::Create(const char * aName)
    {
        Comment("Generated using the HTML_Interface library");

        FILE * lFile = GetFile();
        assert(NULL != lFile);

        fprintf(lFile, EOL);
        fprintf(lFile, "// ===== C ====="    EOL);
        fprintf(lFile, "#include <assert.h>" EOL);
        fprintf(lFile, EOL);
        fprintf(lFile, "// ===== HTML_Interface =====" EOL);
        fprintf(lFile, "#include <HI/Diagram.h>"       EOL);
        fprintf(lFile, "#include <HI/Link.h>"          EOL);
        fprintf(lFile, EOL);
        fprintf(lFile, "HI::Diagram * %s()"                             EOL, aName);
        fprintf(lFile, "{"                                              EOL);
        fprintf(lFile, "    HI::Diagram * lResult = new HI::Diagram();" EOL);
        fprintf(lFile, "    assert(NULL != lResult);"                   EOL);
    }

}
