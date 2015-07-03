//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  This is the control code for the large panel of the emergency party button
//
//  Authors: Mike Kapuscik, Dan Loman
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "Panel.h"

int keySwitch = 6;
int keyLed = 14;
boolean keyState = false;

int redSwitch = 15;
int redLed = 12;
boolean redState = false;

int knobPin = A9;

int toggleLeds[4][4] = {{ 3,  9,  4,  8},
                    {37, 28, 38, 33},
                    {36, 39, 32, 30},
                    {26, 40, 35, 24}};

int toggleMap[4][4] = {{42, 50, 44, 45},
                       {21, 47, 49, 48},
                       {43, 17, 20, 51},
                       {19, 52, 46, 53}};

int sideSwitches[4] = {11, 2, 10, 5};
int sideLeds[4] = {34, 22, 41, 7};
boolean sideStates[4];

#define numInvertedSwitches 7
int invertedSwitches[numInvertedSwitches] = {42, 50, 44, 45, 11, 2, 10};

boolean toggleStates[4][4];

void setupSwitchLed(int Switch, int Led);

void getSideStates();
void getSwitchStates();
void readAnalog();
void writeLeds();
void writeSideLeds();

void offMode();
void randomPartyMode();
void toggleFlipMode();
void writeLeds();
void serialSwitchStates();

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
      pinMode(toggleLeds[i][j], OUTPUT);
      pinMode(toggleMap[i][j], INPUT_PULLUP);
      digitalWrite(toggleLeds[i][j], LOW);
      toggleStates[i][j] = digitalRead(toggleMap[i][j]);
    }
    sideStates[i] = digitalRead(sideSwitches[i]);
  }
  setupSwitchLed(keySwitch, keyLed);
  setupSwitchLed(redSwitch, redLed);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean isInverted(int pinValue)
{
  boolean inverted = false;
  for (int i = 0; i < numInvertedSwitches; ++i)
  {
    if (pinValue == invertedSwitches[i])
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
      getSwitchState(toggleStates[i][j], toggleMap[i][j]);
    }
    getSwitchState(sideStates[i], sideSwitches[i]);
  }
  getSwitchState(keyState, keySwitch);
  getSwitchState(redState, redSwitch);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void writeLeds()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; ++j)
    {
      digitalWrite(toggleLeds[i][j], toggleStates[i][j]);
    }
    digitalWrite(sideLeds[i], sideStates[i]);
  }
  digitalWrite(keyLed, keyState);
  digitalWrite(redLed, redState);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void readAnalog()
{
  int knobValue = analogRead(knobPin);
  knobValue = map(knobValue, 0, 1024, 0, 255);
  Serial.print("knobValue = ");
  Serial.println(knobValue);
  Serial.println();
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
      digitalWrite(toggleLeds[i][j], LOW);
    }
    digitalWrite(sideLeds[i], LOW);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop()
{
  getSwitchStates();
  writeLeds();
  readAnalog();
}
