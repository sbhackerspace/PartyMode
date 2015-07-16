//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the key turn mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "KeyTurnPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
KeyTurnPanel::KeyTurnPanel()
  : Panel(),
    mToggleState(true),
    mLeftTurnTime(0),
    mRightTurnTime(0),
    mMaxKeyTurnTime(150)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void KeyTurnPanel::toggleKeyLights()
{
  if (millis() - mLastMoveTime > 100)
  {
    mToggleState = !mToggleState;
  }
  digitalWrite(mLeftKeyLed, mToggleState);
  digitalWrite(mRightKeyLed, mToggleState);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean KeyTurnPanel::haveKeysBeenSimultaneouslyTurned()
{
  if
    (mLeftKeyState &&
     mRightKeyState &&
     (abs(mLeftTurnTime - mRightTurnTime) > mMaxKeyTurnTime))
  {
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean KeyTurnPanel::getKeyStateChange(
  int keyPin,
  boolean& keyState,
  long& turnTime)
{
  if (!keyState)
  {
    getSwitchState(keyState, keyPin);
    if (keyState)
    {
      turnTime = millis();
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void KeyTurnPanel::keyMode()
{
  if (haveKeysBeenSimultaneouslyTurned())
  {
    fail(); //TODO make a success mode
  }

  if (!mLeftKeyState)
  {
    getKeyStateChange(mLeftKeyPin, mLeftKeyState, mLeftTurnTime);
  }
  if (!mRightKeyState)
  {
    getKeyStateChange(mRightKeyPin, mRightKeyState, mRightTurnTime);
  }
  toggleKeyLights();
}
