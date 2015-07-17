//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the key turn mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "KeyTurnPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
KeyTurnPanel::KeyTurnPanel(Ring& ring)
  : Panel(ring),
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
  if (millis() - mLastMoveTime > 1000)
  {
    mToggleState = !mToggleState;
    mLastMoveTime = millis();
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
    allStatesOn();
    writeLeds();
    delay(50);
    clearStates();
    writeLeds();
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
boolean KeyTurnPanel::keyMode()
{
  if (haveKeysBeenSimultaneouslyTurned())
  {
    return true;
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
  return false;
}
