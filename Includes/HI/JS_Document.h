
// Product  HTML_Interface

/// \author KMS - Martin Dubois, P.Eng.
/// \file   Includes/JS_Document.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <HI/Document.h>

namespace HI
{

    /// \brief JS_Document
    class JS_Document : public Document
    {

    public:

        JS_Document();

        // ===== Document ===================================================

        virtual ~JS_Document();

        virtual void Comment      (const char * aComment);
        virtual void Comment_Begin();
        virtual void Comment_End  ();

    };

}
