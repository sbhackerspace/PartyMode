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

    void colorRing(uint8_t writeDelay);

    void initializeColorRing();

    int  getNumPixels() const;

    uint32_t getColor(uint8_t Red, uint8_t Green, uint8_t Blue) const;

    void setPixelColor(int index, uint32_t color);

    void setPixelColor(uint16_t index, uint8_t Red, uint8_t Green, uint8_t Blue);

    void show();

    void clearRing();

  private:

    void incrementPins();
    void incrementPin(int& pin);

  private:

    int mRedPin, mGreenPin, mBluePin;

    unsigned long int mTimeSinceLastRingLedWrite;

    Adafruit_NeoPixel mStrip;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline
int Ring::getNumPixels() const
{
  return mStrip.numPixels();
}

