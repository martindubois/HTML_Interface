
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/LinkList.cpp

// CODE REVIEW 2020-06-21 KMS - Martin Dubois, P.Eng.

// TEST COVERAGE 2020-06-21 KMS - Martin Dubois, P.Eng.

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <HI/Line.h>
#include <HI/Link.h>
#include <HI/Shape.h>

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
    Link * LinkList::AddLink(const Shape * aFrom, const Shape * aTo)
    {
        assert(NULL != aFrom);
        assert(NULL != aTo  );

        Link * lResult = new Link(aFrom, aTo);
        assert(NULL != lResult);

        lResult->SetAutoDelete();

        mLinks.push_back(lResult);

        return lResult;
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

    Link * LinkList::GetLink(unsigned int aIndex)
    {
        InternalList::iterator lIt = mLinks.begin();

        for (unsigned int i = 0; i < aIndex; i++)
        {
            lIt++;
        }

        if (mLinks.end() == lIt)
        {
            return NULL;
        }

        assert(NULL != *lIt);

        return *lIt;
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
                lResult += GetWeight(aShape, lLink);
            }
        }

        return lResult;
    }

    void LinkList::LinkCounts_Update() const
    {
        for (InternalList::const_iterator lIt = mLinks.begin(); lIt != mLinks.end(); lIt++)
        {
            Link * lLink = *lIt;
            assert(NULL != lLink);

            lLink->GetFrom()->LinkCount_Inc();
            lLink->GetTo  ()->LinkCount_Inc();
        }
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    double LinkList::GetWeight(const Shape * aShape, const Link * aLink) const
    {
        assert(NULL != aShape);
        assert(NULL != aLink );

        const Shape * lOtherShape = aLink->GetOtherShape(aShape);

        double lResult = aLink->GetWeight();

        for (InternalList::const_iterator lIt2 = mLinks.begin(); lIt2 != mLinks.end(); lIt2++)
        {
            Link * lLink2 = *lIt2;
            assert(NULL != lLink2);

            if (aLink != lLink2)
            {
                Line lLine = aLink->GetLine();

                if (lLine.IsOverlapping(lLink2->GetLine()))
                {
                    lResult += 1000;
                }

                if (!lLink2->IsConnectedTo(aShape) && !lLink2->IsConnectedTo(lOtherShape))
                {
                    if (lLine.IsCrossing(lLink2->GetLine()))
                    {
                        lResult += 100;
                    }

                    if ((lLink2->GetFrom()->IsCrossing(lLine)) || (lLink2->GetTo()->IsCrossing(lLine)))
                    {
                        lResult += 1000;
                    }
                }
            }
        }

        return lResult;
    }

}
