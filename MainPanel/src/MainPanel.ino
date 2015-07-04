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

#include <Adafruit_NeoPixel.h>
#include <avr/power.h> // Comment out this line for non-AVR boards (Arduino Due, etc.)

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, 16, NEO_GRB + NEO_KHZ800);


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
  strip.begin();
  strip.show();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
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
  knobValue = map(knobValue, 0, 1024, 0, 255);
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
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  getSwitchStates();
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  writeLeds();
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  readAndWriteSiren();
}
