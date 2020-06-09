
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// Product   HTML_Interface
// File      HILib/Math.h

// CODE REVIEW 2020-06-09 KMS - Martin Dubois, P.Eng.

#pragma once

// Functions
/////////////////////////////////////////////////////////////////////////////

extern bool Math_Range_Include_Excl(unsigned int aFrom, unsigned int aTo, double aValue);
extern bool Math_Range_Include_Incl(unsigned int aFrom, unsigned int aTo, double aValue);

extern bool Math_Ranges_Overlap_Excl(unsigned int aAFrom, unsigned int aATo, unsigned int aBFrom, unsigned int aBTo);
