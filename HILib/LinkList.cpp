
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/LinkList.cpp

// CODE REVIEW 2020-05-27 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-05-27 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/Link.h>

#include <HI/LinkList.h>

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static double DetectConflict(const HI::Link * aA, const HI::Link * aB);

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

    double LinkList::GetLength(const Shape * aShape) const
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

    // Internal
    /////////////////////////////////////////////////////////////////////////

    double LinkList::GetWeight(const Shape * aShape) const
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

                for (InternalList::const_iterator lIt2 = mLinks.begin(); lIt2 != mLinks.end(); lIt2++)
                {
                    if (lIt != lIt2)
                    {
                        lResult_pixel += DetectConflict(lLink, *lIt2);
                    }
                }
            }
        }

        return lResult_pixel;
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

double DetectConflict(const HI::Link * aA, const HI::Link * aB)
{
    assert(NULL != aA);
    assert(NULL != aB);

    if (aA->IsOverlapping(aB))
    {
        return 1000;
    }

    if (aA->IsCrossing(aB))
    {
        return 100;
    }

    return 0;
}