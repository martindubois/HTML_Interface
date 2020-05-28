
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

        double lResult = 0;

        for (InternalList::const_iterator lIt = mLinks.begin(); lIt != mLinks.end(); lIt++)
        {
            Link * lLink = *lIt;
            assert(NULL != lLink);

            if (lLink->IsConnectedTo(aShape))
            {
                const Shape * lOtherShape = lLink->GetOtherShape(aShape);

                lResult += lLink->GetLength();

                for (InternalList::const_iterator lIt2 = mLinks.begin(); lIt2 != mLinks.end(); lIt2++)
                {
                    Link * lLink2 = *lIt2;
                    if (lLink != lLink2)
                    {
                        if (lLink->IsOverlapping(lLink2))
                        {
                            lResult += 1000;
                        }

                        if (!lLink2->IsConnectedTo(aShape) && !lLink2->IsConnectedTo(lOtherShape) && lLink->IsCrossing(lLink2))
                        {
                            lResult += 100;
                        }
                    }
                }
            }
        }

        return lResult;
    }

}
