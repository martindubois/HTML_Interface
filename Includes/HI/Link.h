
// Product HTML_Interface

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2020 KMS. All rights reserved.
/// \file      Includes/HI/Link.h
/// \brief     HI::Link

#pragma once

namespace HI
{

    class SVG_Document;
    class Shape       ;

    /// \brief HI::Link
    class Link
    {

    public:

        Link();

        /// \param aFrom The Shape where the link begins
        /// \param aTo   The Shape where the link ends
        Link(const Shape * aFrom, const Shape * aTo);

        ~Link();

        /// \retval false Do not delete
        /// \retval true  Delete when no longer needed
        bool GetAutoDelete() const;

        /// \return This method returns a pointer to the shape at the start of the link.
        const Shape * GetFrom() const;

        /// \return The length of the link in pixel
        double GetLength() const;

        /// \return See HI::Line
        Line GetLine() const;

        /// \param aShape One of the two connected shapes
        /// \return This method returns the pointer to the other connected shape.
        const Shape * GetOtherShape(const Shape * aShape) const;

        /// \return This method returns a pointer to the shape at the end of the link.
        const Shape * GetTo() const;

        /// \param aShape The shape of interreset
        /// \retval false Not connected
        /// \retval true  Connected
        bool IsConnectedTo(const Shape * aShape) const;

        void SetAutoDelete();

        /// \param aFrom The Shape where the link begins
        void SetFrom(const Shape * aFrom);

        /// \param aTo The Shape where the link ends
        void SetTo(const Shape * aTo);

        /// \param aDoc The document to generate into
        /// \exception std::exception
        void Generate_SVG(HI::SVG_Document * aDoc) const;

    private:

        void Init();

        struct
        {
            unsigned mAutoDelete : 1;

            unsigned mReserved0 : 31;
        }
        mFlags;

        const Shape * mFrom;
        const Shape * mTo  ;

    };

}
