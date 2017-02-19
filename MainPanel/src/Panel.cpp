#include "Panel.h"
#include "PanelPinValues.h"

bool Panel::mFail = false;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Panel::Panel(Ring& ring)
  : mTotalNumberOfRows(4),
    mTotalNumberOfColumns(4),
    mRing(ring),
    mLeftKeyState(false),
    mRightKeyState(false),
    mRedState(false),
    mToggleStates({
      {false, false, false, false},
      {false, false, false, false},
      {false, false, false, false},
      {false, false, false, false}}),
    mSideStates({false, false, false, false}),
    mLastMoveTime(0)
{
  clearStates();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::setupSwitchLed(int Switch, int Led)
{
  pinMode(Switch, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
  randomSeed(analogRead(0));
  clearStates();
  writeLeds();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::setupPanel()
{
  for(int i = 0; i < mTotalNumberOfRows; i++)
  {
    for(int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      pinMode(mToggleLeds[i][j], OUTPUT);
      pinMode(mToggleMap[i][j], INPUT_PULLUP);
      digitalWrite(mToggleLeds[i][j], LOW);
    }
    pinMode(mSideLeds[i], OUTPUT);
    pinMode(mSideSwitches[i], INPUT_PULLUP);
  }
  setupSwitchLed(mLeftKeyPin, mLeftKeyLed);
  setupSwitchLed(mRightKeyPin, mRightKeyLed);
  setupSwitchLed(mRedButtonPin, mRedLed);

  pinMode(mMainPowerSwitch, INPUT);
  digitalWrite(mMainPowerSwitch, HIGH);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::writeLeds() const
{
  for(int i = 0; i < mTotalNumberOfRows; i++)
  {
    for(int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      digitalWrite(mToggleLeds[i][j], mToggleStates[i][j]);
    }
    digitalWrite(mSideLeds[i], mSideStates[i]);
  }
  digitalWrite(mLeftKeyLed, mLeftKeyState);
  digitalWrite(mRightKeyLed, mRightKeyState);
  digitalWrite(mRedLed, mRedState);
  analogWrite(mSirenPin, mSirenValue);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::writeLeds(int ledMap[4][4]) const
{
  for(int i = 0; i < mTotalNumberOfRows; i++)
  {
    for(int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      digitalWrite(ledMap[i][j], mToggleStates[i][j]);
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::readAndWriteSiren() const
{
  int knobValue = analogRead(mKnobPin);
  knobValue = map(knobValue, 0, 1024, 0, 255);
  analogWrite(mSirenPin, knobValue);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean Panel::isInverted(int pinValue) const
{
  for (int i = 0; i < numInvertedSwitches; ++i)
  {
    if (pinValue == mInvertedSwitches[i])
    {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::getSwitchState(boolean& switchState, int switchPin)
{
  if(isInverted(switchPin))
  {
    switchState = !digitalRead(switchPin);
  }
  else
  {
    switchState = digitalRead(switchPin);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::getSwitchStates()
{
  for(int i = 0; i < mTotalNumberOfRows; i++)
  {
    for(int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      getSwitchState(mToggleStates[i][j], mToggleMap[i][j]);
    }
    getSwitchState(mSideStates[i], mSideSwitches[i]);
  }
  getSwitchState(mLeftKeyState, mLeftKeyPin);
  getSwitchState(mRightKeyState, mRightKeyPin);
  getSwitchState(mRedState, mRedButtonPin);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::clearStates()
{
  for (int i = 0; i < mTotalNumberOfRows; ++i)
  {
    for (int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      mToggleStates[i][j] = isInverted(mToggleStates[i][j]);
    }
    mSideStates[i] = !isInverted(mSideSwitches[i]);
  }
  mRightKeyState = !isInverted(mRightKeyPin);
  mLeftKeyState = !isInverted(mLeftKeyPin);
  mRedState = !isInverted(mRedButtonPin);
  mSirenValue = 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::allStatesOn()
{
  for (int i = 0; i < mTotalNumberOfRows; ++i)
  {
    for (int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      mToggleStates[i][j] = !isInverted(mToggleMap[i][j]);
    }
      mSideStates[i] = isInverted(mSideSwitches[i]);
  }
  mRightKeyState = isInverted(mRightKeyPin);
  mLeftKeyState = isInverted(mLeftKeyPin);
  mRedState = isInverted(mRedButtonPin);
  mSirenValue = 255;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean Panel::isPanelOn()
{
  return !digitalRead(mMainPowerSwitch);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::offMode()
{
  clearStates();
  writeLeds();
  mRing.clearRing();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::fail()
{
  clearStates();
  writeLeds();
  Serial.println("fail");
  mFail = true;
  for (int i = 0; i <100; ++i)
  {
    analogWrite(mSirenPin, i);
    analogWrite(mRedLed, i);
    delay(6);
  }
  for (int i = 100; i >= 0; --i)
  {
    analogWrite(mSirenPin, i);
    analogWrite(mRedLed, i);
    delay(6);
  }
  Serial.println(mFail ? "panel true" : "panel false");
}

