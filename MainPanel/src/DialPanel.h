//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the header for dial mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class DialPanel : public Panel
{
  public:

	  DialPanel(Ring& ring);

    boolean dialMode();

    void initializeDialMode();

  private:

    void writeRing();

    void incrementRingLeds(int changeInPosition);

    DialPanel(const DialPanel&);
    DialPanel& operator = (const DialPanel&);

  protected:

    boolean mDialModeInitialized;

  private:


    int mCurrentDistance;
    int mKnobFinalValue;

    int mRedNumber, mGreenNumber, mBlueNumber, mYellowNumber, mCyanNumber;

    int mLedIncrementDistance;
};
