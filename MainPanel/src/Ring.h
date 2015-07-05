//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Description:
//   Led ring wrapper class
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#pragma once

#define NUMPIXELS 24
#define RINGDATAPIN 16

#include <Adafruit_NeoPixel.h>
// Comment out this line for non-AVR boards (Arduino Due, etc.)
#include <avr/power.h>

class Ring{

  public:

    Ring();

    void showColors(uint8_t writeDelay);

  private:

    void incrementPins();
    void incrementPin(int& pin);

  private:

    int mRedPin, mGreenPin, mBluePin;

    unsigned long int mTimeSinceLastRingLedWrite;

    Adafruit_NeoPixel mStrip;
};

