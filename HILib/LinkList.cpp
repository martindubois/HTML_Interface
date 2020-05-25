
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/LinkList.cpp

// CODE REVIEW 2020-05-24 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-24 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/Link.h>

#include <HI/LinkList.h>

namespace HI
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    LinkList::LinkList()
    {
    }

    LinkList::~LinkList()
    {
        for (InternalList::iterator lIt = mLinks.begin(); lIt != mLinks.end(); lIt++)
        {
            Link * lLink = (*lIt);
            assert(NULL != lLink);

            if (lLink->GetAutoDelete())
            {
                delete lLink;
            }
        }
    }

    // aFrom [-K-;R--]
    // aTo   [-K-;R--]
    void LinkList::AddLink(const Shape * aFrom, const Shape * aTo)
    {
        assert(NULL != aFrom);
        assert(NULL != aTo  );

        Link * lLink = new Link(aFrom, aTo);
        assert(NULL != lLink);

        lLink->SetAutoDelete();

        mLinks.push_back(lLink);
    }

    // aShape [---;---]
    double LinkList::GetLength(const Shape * aShape)
    {
        assert(NULL != aShape);

        double lResult_pixel = 0;

        for (InternalList::const_iterator lIt = mLinks.begin(); lIt != mLinks.end(); lIt++)
        {
            Link * lLink = *lIt;
            assert(NULL != lLink);

            if (lLink->IsConnectedTo(aShape))
            {
                lResult_pixel += lLink->GetLength();
            }
        }

        return lResult_pixel;
    }

    void LinkList::Generate_SVG(SVG_Document * aDoc) const
    {
        assert(NULL != aDoc);

        for (InternalList::const_iterator lIt = mLinks.begin(); lIt != mLinks.end(); lIt++)
        {
            assert(NULL != (*lIt));

            (*lIt)->Generate_SVG(aDoc);
        }
    }

}
