//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a base class for party mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include <Arduino.h>

#include "Ring.h"

#define numInvertedSwitches 10

class Panel
{
  public:

    void setupPanel();

    boolean isPanelOn();

    void offMode();

  protected:

	  Panel(Ring& ring);

    void getSwitchStates();
    void writeLeds() const;
    void writeLeds(int ledMap[4][4]) const;
    void readAndWriteSiren() const;

    void setupSwitchLed(int Switch, int Led);

    void getSwitchState(boolean& switchState, int switchPin);
    boolean isInverted(int pinValue) const;

    void rowIncrement(int& Value);
    void columnIncrement(int& Value);

    void clearStates();

    void fail();

    //private and unimplimented to prevent accidental copying
    Panel(const Panel&);
    Panel& operator = (const Panel&);

  protected:

    const int mTotalNumberOfRows, mTotalNumberOfColumns;
    Ring& mRing;
    static const int mLeftKeyPin, mLeftKeyLed, mRightKeyPin, mRightKeyLed;

    static const int mSirenPin;
    int mSirenValue;

    static const int mMainPowerSwitch;
    boolean mLeftKeyState, mRightKeyState;

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

    long mLastMoveTime;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline
void Panel::rowIncrement(int& Index)
{
  Index++;
  if (Index >= mTotalNumberOfRows)
  {
    Index = 0;
  }
  mLastMoveTime = millis();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline
void Panel::columnIncrement(int& Index)
{
  Index++;
  if (Index >= mTotalNumberOfColumns)
  {
    Index = 0;
  }
  mLastMoveTime = millis();
}
