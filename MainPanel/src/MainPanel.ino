//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the control code for the large panel of the emergency party button
//
//  Authors: Mike Kapuscik, Dan Loman
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "Panel.h"
#include "Ring.h"

void setupSwitchLed(int Switch, int Led);

void getSideStates();
void getSwitchStates();
void readAndWriteRedButton();
void writeLeds();
void writeSideLeds();

void offMode();
void randomPartyMode();
void toggleFlipMode();
void writeLeds();
void serialSwitchStates();

Panel panel;
Ring colorRing;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setupSwitchLed(int Switch, int Led)
{
  pinMode(Switch, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, LOW);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      pinMode(panel.mToggleLeds[i][j], OUTPUT);
      pinMode(panel.mToggleMap[i][j], INPUT_PULLUP);
      digitalWrite(panel.mToggleLeds[i][j], LOW);
    }
    pinMode(panel.mSideLeds[i], OUTPUT);
    pinMode(panel.mSideSwitches[i], INPUT_PULLUP);
  }
  setupSwitchLed(panel.mKeySwitch, panel.mKeyLed);
  setupSwitchLed(panel.mRedSwitch, panel.mRedLed);
  panel.sirenOffset = analogRead(panel.knobPin);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean isInverted(int pinValue)
{
  boolean inverted = false;
  for (int i = 0; i < numInvertedSwitches; ++i)
  {
    if (pinValue == panel.mInvertedSwitches[i])
    {
      return true;
    }
  }
  return inverted;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void getSwitchState(boolean& switchState, int switchPin)
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
void getSwitchStates()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      getSwitchState(panel.mToggleStates[i][j], panel.mToggleMap[i][j]);
    }
    getSwitchState(panel.mSideStates[i], panel.mSideSwitches[i]);
  }
  getSwitchState(panel.mKeyState, panel.mKeySwitch);
  getSwitchState(panel.mRedState, panel.mRedSwitch);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void writeLeds()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      digitalWrite(panel.mToggleLeds[i][j], panel.mToggleStates[i][j]);
    }
    digitalWrite(panel.mSideLeds[i], panel.mSideStates[i]);
  }
  digitalWrite(panel.mKeyLed, panel.mKeyState);
  digitalWrite(panel.mRedLed, panel.mRedState);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void readAndWriteSiren()
{
  int knobValue = analogRead(panel.mKnobPin);
  knobValue = map(knobValue, panel.mSirenOffset, 1024, 0, 255);
  analogWrite(13, knobValue);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void offMode()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      digitalWrite(panel.mToggleLeds[i][j], LOW);
    }
    digitalWrite(panel.mSideLeds[i], LOW);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop()
{
  colorRing.showColors(50);
  getSwitchStates();
  writeLeds();
  readAndWriteSiren();
}
