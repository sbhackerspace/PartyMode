//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  This is the control code for the large panel of the emergency party button
//
//  Authors: Mike Kapuscik, Dan Loman
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "Panel.h"

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
      pinMode(panel.toggleLeds[i][j], OUTPUT);
      pinMode(panel.toggleMap[i][j], INPUT_PULLUP);
      digitalWrite(panel.toggleLeds[i][j], LOW);
    }
    pinMode(panel.sideLeds[i], OUTPUT);
    pinMode(panel.sideSwitches[i], INPUT_PULLUP);
  }
  setupSwitchLed(panel.keySwitch, panel.keyLed);
  setupSwitchLed(panel.redSwitch, panel.redLed);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean isInverted(int pinValue)
{
  boolean inverted = false;
  for (int i = 0; i < numInvertedSwitches; ++i)
  {
    if (pinValue == panel.invertedSwitches[i])
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
      getSwitchState(panel.toggleStates[i][j], panel.toggleMap[i][j]);
    }
    getSwitchState(panel.sideStates[i], panel.sideSwitches[i]);
  }
  getSwitchState(panel.keyState, panel.keySwitch);
  getSwitchState(panel.redState, panel.redSwitch);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void writeLeds()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      digitalWrite(panel.toggleLeds[i][j], panel.toggleStates[i][j]);
    }
    digitalWrite(panel.sideLeds[i], panel.sideStates[i]);
  }
  digitalWrite(panel.keyLed, panel.keyState);
  digitalWrite(panel.redLed, panel.redState);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void readAndWriteSiren()
{
  int knobValue = analogRead(panel.knobPin);
  knobValue = map(knobValue, 10, 1024, 0, 255);
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
      digitalWrite(panel.toggleLeds[i][j], LOW);
    }
    digitalWrite(panel.sideLeds[i], LOW);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop()
{
  getSwitchStates();
  writeLeds();
  readAndWriteSiren();
}
