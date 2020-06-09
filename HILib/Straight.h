
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Straight.h

#pragma once

class Straight
{

public:

    double GetB() const;
    double GetM() const;

    void Set(double aB, double aM);

    double Evaluate(double aX) const;

private:

    double mB;
    double mM;

};

// Public
/////////////////////////////////////////////////////////////////////////////

inline double Straight::GetB() const
{
    return mB;
}

inline double Straight::GetM() const
{
    return mM;
}

inline void Straight::Set(double aB, double aM)
{
    mB = aB;
    mM = aM;
}

inline double Straight::Evaluate(double aX) const
{
    return mM * aX + mB;
}
