//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a header for Big red button mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#include "BigRedButtonPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
BigRedButtonPanel::BigRedButtonPanel(Ring& ring)
  : Panel(ring),
    mRedFlash(true)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void BigRedButtonPanel::initializeBigRedButton()
{
  clearStates();

  writeLeds();

  delay(1000);

  mLastMoveTime = millis();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool BigRedButtonPanel::bigRedButtonMode()
{
  getSwitchState(mRedState, mRedButtonPin);

  if (mRedState)
  {
    return true;
  }

  if (abs(millis() - mLastMoveTime) > 400)
  {
    digitalWrite(mRedLed, mRedFlash);

    mRedFlash = !mRedFlash;

    mLastMoveTime = millis();
  }

  return false;
}
