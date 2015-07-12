#include "Panel.h"
#include "PanelPinValues.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Panel::Panel(void)
  : mLeftKeyState(false),
    mRightKeyState(false),
    mRedState(false),
    mToggleStates({
      {false, false, false, false},
      {false, false, false, false},
      {false, false, false, false},
      {false, false, false, false}}),
    mSideStates({false, false, false, false}),
    mSirenOffset(analogRead(mKnobPin))
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::setupSwitchLed(int Switch, int Led)
{
  pinMode(Switch, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, LOW);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::setupPanel()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
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
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::writeLeds(void) const
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      digitalWrite(mToggleLeds[i][j], mToggleStates[i][j]);
    }
    digitalWrite(mSideLeds[i], mSideStates[i]);
  }
  digitalWrite(mLeftKeyLed, mLeftKeyState);
  digitalWrite(mRightKeyLed, mRightKeyState);
  digitalWrite(mRedLed, mRedState);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::readAndWriteSiren() const
{
  int knobValue = analogRead(mKnobPin);
  knobValue = map(knobValue, mSirenOffset, 1024, 0, 255);
  analogWrite(13, knobValue);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::offMode()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      digitalWrite(mToggleLeds[i][j], LOW);
    }
    digitalWrite(mSideLeds[i], LOW);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Panel::testMode()
{
  getSwitchStates();
  writeLeds();
  readAndWriteSiren();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean Panel::isInverted(int pinValue) const
{
  boolean inverted = false;
  for (int i = 0; i < numInvertedSwitches; ++i)
  {
    if (pinValue == mInvertedSwitches[i])
    {
      return true;
    }
  }
  return inverted;
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
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      getSwitchState(mToggleStates[i][j], mToggleMap[i][j]);
    }
    getSwitchState(mSideStates[i], mSideSwitches[i]);
  }
  getSwitchState(mLeftKeyState, mLeftKeyPin);
  getSwitchState(mRightKeyState, mRightKeyPin);
  Serial.println(mRightKeyState);
  getSwitchState(mRedState, mRedButtonPin);
}

