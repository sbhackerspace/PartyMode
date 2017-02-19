//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the test mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "ControlPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ControlPanel::ControlPanel(Ring& ring)
  : Panel(ring),
    mTogglePanel(ring),
    mDialPanel(ring),
    mPhonePanel(ring),
    mKeyTurnPanel(ring),
    mTaintPanel(ring),
    mBigRedButtonPanel(ring),
    mMode(eOffMode),
    mPartyModePanel(ring, 1000)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ControlPanel::PARTY()
{
  Serial.print("PARTY MODE ENABLED");
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ControlPanel::initialize()
{
  Serial.println("initializing control panel");
  mTogglePanel.initializeToggle();
  mMode = eTaintMode;
  mTaintPanel.initialize(1,2,3,4,5); //TEMP
  mFail = false;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ControlPanel::run()
{
  if (mFail)
  {
    mMode = eOffMode;
  }

  if (isPanelOn())
  {
    switch(mMode)
    {
      case eOffMode:
        initialize();
        break;

      case eToggleMode:
        if (mTogglePanel.toggleMode())
        {
          mDialPanel.initializeDialMode();
          mMode = eDialMode;
        }
        break;

      case eDialMode:
        if (mDialPanel.dialMode())
        {
          mMode = eTaintMode;
          mTaintPanel.initialize(1,2,3,4,5);
        }
        break;

      case ePhoneMode:
        if (mPhonePanel.phoneMode())
        {
          mMode = eTaintMode;
          mTaintPanel.initialize(1,2,3,4,5);
        }
        break;

      case eTaintMode:
        if (mTaintPanel.taint())
        {
          mMode = eKeyTurnMode;
          mKeyTurnPanel.initialize();
        }
        break;

      case eKeyTurnMode:
        if (mKeyTurnPanel.keyMode())
        {
          mMode = eBigRedButtonMode;
          mBigRedButtonPanel.initializeBigRedButton();
        }
        break;

      case eBigRedButtonMode:
        if (mBigRedButtonPanel.bigRedButtonMode())
        {
          mPartyModePanel.initialize();

          Serial.println("PARTY!");

          mMode = ePartyMode;
        }
        break;

      case ePartyMode:
        mPartyModePanel.party();
        break;
    }
  }
  else
  {
    offMode();
    mMode = eOffMode;
  }
}
