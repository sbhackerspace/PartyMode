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

	  KeyTurnPanel(Ring& ring);

    boolean keyMode();

    void initialize();

  private:

    void toggleKeyLights();

    boolean haveKeysBeenSimultaneouslyTurned();

    boolean getKeyStateChange(int keyPin, boolean& keyState, long& turnTime);

    KeyTurnPanel(const KeyTurnPanel&);
    KeyTurnPanel& operator = (const KeyTurnPanel&);

    void hasTimeExpired(const long& turnTime);

  private:

    boolean mToggleState;
    long mLeftTurnTime, mRightTurnTime;
    int mMaxKeyTurnTime;
};

