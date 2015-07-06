#pragma once

#include <Arduino.h>

#define numInvertedSwitches 8

class Panel
{
  public:

	  Panel();

    static const int mKeySwitch, mKeyLed;
    boolean mKeyState;

    static const int mRedSwitch, mRedLed;
    boolean mRedState;

    static const int mKnobPin;

    static const int mToggleMap[4][4];
    static const int mToggleLeds[4][4];
    boolean mToggleStates[4][4];

    static const int mSideSwitches[4];
    static const int mSideLeds[4];
    boolean mSideStates[4];

    static const int mInvertedSwitches[numInvertedSwitches];
};

