
// Product  HTML_Interface

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/CPP_Document.h
/// \brief     HI::CPP_Document

#pragma once

// ===== Includes ===========================================================
#include <HI/Document.h>

namespace HI
{

    /// \brief CPP_Document
    class CPP_Document : public Document
    {

    public:

        CPP_Document();

        // ===== Document ===================================================

        virtual ~CPP_Document();

        virtual void Close();

        virtual void Comment_Begin();
        virtual void Comment_End  ();

        virtual void Create(FolderId     aFolder, const char * aName);
        virtual void Create(const char * aFolder, const char * aName);

        virtual void NewLine();

    private:

        void Create(const char * aName);

    };

}
