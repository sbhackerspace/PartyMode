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
    mMaxKeyTurnTime(250)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void KeyTurnPanel::initialize()
{
  clearStates();

  writeLeds();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void KeyTurnPanel::toggleKeyLights()
{
  if (millis() - mLastMoveTime > 100)
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
     (abs(mLeftTurnTime - mRightTurnTime) < mMaxKeyTurnTime))
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
void KeyTurnPanel::hasTimeExpired(const long& turnTime)
{
  if (millis() - turnTime > mMaxKeyTurnTime)
  {
    fail();
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean KeyTurnPanel::keyMode()
{
  if (haveKeysBeenSimultaneouslyTurned())
  {
    Serial.println("keys turned simulatenously!");
    return true;
  }

  if (!mLeftKeyState)
  {
    getKeyStateChange(mLeftKeyPin, mLeftKeyState, mLeftTurnTime);
  }
  else
  {
    hasTimeExpired(mLeftTurnTime);
  }

  if (!mRightKeyState)
  {
    getKeyStateChange(mRightKeyPin, mRightKeyState, mRightTurnTime);
  }
  else
  {
    hasTimeExpired(mRightTurnTime);
  }

  toggleKeyLights();
  return false;
}
