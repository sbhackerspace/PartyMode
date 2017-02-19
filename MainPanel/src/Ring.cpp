//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Description:
//   Led ring wrapper class
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#include "Ring.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Ring::Ring()
  : mRedPin(0),
    mGreenPin(8),
    mBluePin(16),
    mTimeSinceLastRingLedWrite(0),
    mStrip(24, 16, NEO_GRB + NEO_KHZ800)
{
  mStrip.begin();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Ring::initializeColorRing()
{
  mRedPin = 0;
  mGreenPin = 8;
  mBluePin = 16;
  mTimeSinceLastRingLedWrite = millis();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Ring::incrementPin(int& pin)
{
  pin++;
  if (pin >= mStrip.numPixels())
  {
    pin = 0;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Ring::incrementPins()
{
  incrementPin(mRedPin);
  incrementPin(mGreenPin);
  incrementPin(mBluePin);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Ring::clearRing()
{
  uint32_t color = mStrip.Color(0, 0, 0);
  for (int i = 0; i < mStrip.numPixels(); ++i)
  {
    mStrip.setPixelColor(i, color);
  }
  mStrip.show();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Ring::colorRing(uint8_t wait)
{
  uint32_t Color;
  unsigned long currentTime;
  for (int i = 0; i < mStrip.numPixels(); ++i)
  {
    if (i == mRedPin)
    {
      Color = mStrip.Color(255, 0, 0);
    }
    else if (i == mGreenPin)
    {
      Color = mStrip.Color(0, 255, 0);
    }
    else if (i == mBluePin)
    {
      Color = mStrip.Color(0, 0, 255);
    }
    else
    {
      Color = mStrip.Color(0, 0, 0);
    }
    mStrip.setPixelColor(i, Color);
    mStrip.show();
    currentTime = millis();
    if (currentTime - mTimeSinceLastRingLedWrite > wait)
    {
      incrementPins();
      mTimeSinceLastRingLedWrite = millis();
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
uint32_t Ring::getColor(uint8_t Red, uint8_t Green, uint8_t Blue) const
{
  return mStrip.Color(Red, Green, Blue);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Ring::setPixelColor(int index, uint32_t color)
{
  mStrip.setPixelColor(index, color);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Ring::setPixelColor(
  uint16_t index,
  uint8_t Red,
  uint8_t Green,
  uint8_t Blue)
{
  mStrip.setPixelColor(index, Red, Green, Blue);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Ring::show()
{
  mStrip.show();
}
