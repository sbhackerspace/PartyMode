//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a class for party mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include <Arduino.h>

#define numInvertedSwitches 8

class Panel
{
  public:

	  Panel();

    void setupPanel();

    void offMode();
    void randomPartyMode();
    void toggleFlipMode();
    void testMode();

  private:

    void getSwitchStates();
    void writeLeds() const;
    void readAndWriteSiren() const;

    void setupSwitchLed(int Switch, int Led);

    void getSwitchState(boolean& switchState, int switchPin);
    boolean isInverted(int pinValue) const;

  private:

    static const int mKeyPin, mKeyLed;
    boolean mKeyState;

    static const int mRedButtonPin, mRedLed;
    boolean mRedState;

    static const int mKnobPin;

    static const int mToggleMap[4][4];
    static const int mToggleLeds[4][4];
    boolean mToggleStates[4][4];

    static const int mSideSwitches[4];
    static const int mSideLeds[4];
    boolean mSideStates[4];

    static const int mInvertedSwitches[numInvertedSwitches];
    const int mSirenOffset;
};

