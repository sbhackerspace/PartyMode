//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the header for dial mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

#include "Ring.h"

class DialPanel : public Panel
{
  public:

	  DialPanel(Ring& ring);

    void dialMode();

  private:

    void initializeDialMode();

    void writeRing();

    void incrementRingLeds(int changeInPosition);

    DialPanel(const DialPanel&);
    DialPanel& operator = (const DialPanel&);

  private:

    Ring& mRing;

    boolean mDialModeInitialized;

    int mCurrentDistance;
    int mKnobFinalValue;

    int mRedNumber, mGreenNumber, mBlueNumber, mYellowNumber, mCyanNumber;

    int mLedIncrementDistance;
};
