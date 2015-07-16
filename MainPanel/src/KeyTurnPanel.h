//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a header for key turn mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class KeyTurnPanel : public Panel
{
  public:

	  KeyTurnPanel();

    void keyMode();

  private:

    void toggleKeyLights();

    boolean haveKeysBeenSimultaneouslyTurned();

    boolean getKeyStateChange(int keyPin, boolean& keyState, long& turnTime);

    KeyTurnPanel(const KeyTurnPanel&);
    KeyTurnPanel& operator = (const KeyTurnPanel&);

  private:

    boolean mToggleState;
    long mLeftTurnTime, mRightTurnTime;
    int mMaxKeyTurnTime;
};

