//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the dial mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "DialPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
DialPanel::DialPanel(Ring& ring)
  : Panel(ring),
    mDialModeInitialized(false),
    mCurrentDistance(0),
    mKnobFinalValue(0),
    mRedNumber(0),
    mGreenNumber(0),
    mBlueNumber(0),
    mLedIncrementDistance(0)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DialPanel::initializeDialMode()
{
  mDialModeInitialized = true;
  mRing.clearRing();
  int currentPosition = analogRead(mKnobPin);

  if (currentPosition < 512)
  {
    mKnobFinalValue = 1018;
  }
  else
  {
    mKnobFinalValue = 1;
  }
  mCurrentDistance = abs(currentPosition - mKnobFinalValue);

  mLedIncrementDistance = (mCurrentDistance / (3 * mRing.getNumPixels()));
  mLedIncrementDistance *= .75;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DialPanel::incrementRingLeds(int changeInPosition)
{
  int numberToIncrement =  changeInPosition / mLedIncrementDistance;

  if (mRedNumber < mRing.getNumPixels())
  {
    mRedNumber += numberToIncrement;
  }
  else if (mBlueNumber < mRing.getNumPixels())
  {
    mBlueNumber += numberToIncrement;
  }
  else if (mGreenNumber < mRing.getNumPixels())
  {
    mGreenNumber += numberToIncrement;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DialPanel::writeRing()
{
  int numPixels = mRing.getNumPixels();
  uint32_t Color;
  for (int i = 0; i < numPixels; ++i)
  {
    if (i < mGreenNumber)
    {
      Color = mRing.getColor(0, 255, 0);
    }
    else if (i < mBlueNumber)
    {
      Color = mRing.getColor(0, 0, 255);
    }
    else if (i <= mRedNumber)
    {
      Color = mRing.getColor(255, 0, 0);
    }
    else
    {
      Color = mRing.getColor(0, 0, 0);
    }
    mRing.setPixelColor(i, Color);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean DialPanel::dialMode()
{
  if (!mDialModeInitialized)
  {
    initializeDialMode();
  }
  clearStates();
  writeLeds();

  int currentPosition = analogRead(mKnobPin);
  int newDistance = abs(mKnobFinalValue - currentPosition);
  int changeInDistance = abs(newDistance - mCurrentDistance);


  if(newDistance < mCurrentDistance && changeInDistance > mLedIncrementDistance)
  {
    incrementRingLeds(changeInDistance);
    mCurrentDistance = abs(currentPosition - mKnobFinalValue);
  }
  writeRing();


  Serial.println(currentPosition);
  Serial.println(mKnobFinalValue);
  if (abs(currentPosition - mKnobFinalValue) < 5)
  {
    mRing.clearRing();
    Serial.println("success");
    return true;
  }
  return false;
}
