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
  clearStates();
  writeLeds();
  mRing.clearRing();

  Serial.println('s');
  digitalWrite(mPhoneRingerPin, HIGH);
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

    if (inputChar == 'a')
    {
      return true;
    }
    else if (inputChar == 'o')
    {
      digitalWrite(mPhoneRingerPin, LOW);
    }
  }
  if (millis() - mLastMoveTime > 5000)
  {
    digitalWrite(mPhoneRingerPin, LOW);
    fail();
  }
  return false;
}
