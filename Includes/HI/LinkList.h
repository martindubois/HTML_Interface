
// Product HTML_Interface

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/LinkList.h
/// \brief     HI::LinkList

#pragma once

// ===== C++ ================================================================
#include <list>

namespace HI
{

    class Link        ;
    class SVG_Document;
    class Shape       ;

    /// \brief HI::LinkList
    class LinkList
    {

    public:

        LinkList();

        ~LinkList();

        /// \param aLink The link to add
        void AddLink(Link * aLink);

        /// \param aFrom The Shape where the Link begins
        /// \param aTo   The Shape where the link ends
        void AddLink(const Shape * aFrom, const Shape * aTo);

        /// \param aShape The Shape of interrest
        /// \return The number of link connected to the shape
        unsigned int GetCount(const Shape * aShape);

        /// \return The total length in pixel
        double GetLength();

        /// \param aShape The Shape of interrest
        /// \return The total length of all link connected to the shape, in pixel.
        double GetLength(const Shape * aShape);

        /// \param aDoc The document to generate into
        /// \exception std::exception
        void Generate_SVG(HI::SVG_Document * aDoc) const;

    private:

        typedef std::list<Link *> InternalList;

        InternalList mLinks;

    };

}