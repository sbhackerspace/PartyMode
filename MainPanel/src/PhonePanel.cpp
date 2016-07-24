//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the phone mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "PhonePanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
PhonePanel::PhonePanel(Ring& ring)
  : Panel(ring),
    mPhoneInitialized(false)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void PhonePanel::initializePhone()
{
  mPhoneInitialized = true;
  clearStates();
  writeLeds();
  mRing.clearRing();
  Serial.println('r');
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean PhonePanel::phoneMode()
{
  if (!mPhoneInitialized)
  {
    initializePhone();
  }

  while (Serial.available())
  {
    char inputChar = Serial.read();

    if (inputChar == 'f') //fail
    {
      fail();
    }
    else if (inputChar == 's') //success
    {
      return true;
    }
  }
  return false;
}
