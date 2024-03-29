
// Product HTML_Interface
// License https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/LinkList.h
/// \brief     HI::LinkList

#pragma once

// ===== C++ ================================================================
#include <list>

namespace HI
{

    class CPP_Document;
    class Link        ;
    class SVG_Document;
    class Shape       ;
    class ShapeList   ;

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
        /// \return This method returns a pointer to the new Link instance.
        Link * AddLink(const Shape * aFrom, const Shape * aTo);

        /// \param aA
        /// \param aB
        /// \return This method returns a pointer to a Link instance.
        const Link * Find(const Shape * aA, const Shape * aB) const;

        /// \param aShape The Shape of interrest
        /// \return The number of link connected to the shape
        unsigned int GetCount(const Shape * aShape) const;

        /// \return The total length in pixel
        double GetLength() const;

        /// \param aShape The Shape of interrest
        /// \return The total length of all link connected to the shape, in pixel.
        double GetLength(const Shape * aShape) const;

        /// \param aIndex Index of the link to retrieve
        /// \return This method return a pointer to a Link instance or NULL if aIndex is not valid.
        Link * GetLink(unsigned int aIndex);

        /// \param aDoc    The document to generate into
        /// \param aShapes
        /// \exception std::exception
        void Generate_CPP(HI::CPP_Document * aDoc, const ShapeList & aShapes) const;

        /// \param aDoc The document to generate into
        /// \exception std::exception
        void Generate_SVG(HI::SVG_Document * aDoc) const;

    // Internal

        double GetWeight(const Shape * aShape) const;

        void LinkCounts_Update() const;

    private:

        double GetWeight(const Shape * aShape, const Link * aLink) const;

        typedef std::list<Link *> InternalList;

        InternalList mLinks;

    };

}
