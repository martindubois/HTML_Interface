
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

        /// \return The length of the link in pixel
        double GetLength() const;

        /// \aShape The shape of interreset
        /// \retval false Not connected
        /// \retval true  Connected
        bool IsConnectedTo(const Shape * aShape);

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
