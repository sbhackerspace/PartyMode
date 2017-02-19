//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the test mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "TestPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
TestPanel::TestPanel(Ring& ring)
  : Panel(ring),
    mColor(0x0000FF),
    mTime(millis())
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TestPanel::run()
{
  getSwitchStates();
  writeLeds();

  for (int i = 0; i < mRing.getNumPixels(); ++i)
  {
    mRing.setPixelColor(i, mColor);
  }

  if (abs(millis() - mTime) > 800)
  {
    if (mColor == 0x0000FF)
    {
      mColor = 0x00FF00;
    }
    else if (mColor == 0x00FF00)
    {
      mColor = 0xFF0000;
    }
    else if (mColor == 0xFF0000)
    {
      mColor = 0x0000FF;
    }
    else
    {
      mColor = 0xFFFFFF;
    }
    mTime = millis();
  }
  mRing.show();

  Serial.println(mToggleStates[3][1]);
  digitalWrite(mToggleLeds[3][1], mToggleStates[3][1]);
}
