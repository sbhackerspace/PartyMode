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
    mLaunchPanel(ring),
    mDialPanel(ring),
    mKeyTurnPanel(ring),
    mPartyPanel(ring, 150),
    mMode(eOffMode)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ControlPanel::run()
{
  if (isPanelOn())
  {
    switch(mMode)
    {
      case eOffMode:
        mLaunchPanel.initializeLaunch();
        mMode = eLaunchMode;
        break;
      case eLaunchMode:
        if (mLaunchPanel.launchMode())
        {
          mDialPanel.initializeDialMode();
          mMode = eDialMode;
        }
        break;
      case eDialMode:
        if (mDialPanel.dialMode())
        {
          mMode = eKeyTurnMode;
          Serial.println("keymode");
        }
        break;
      case eKeyTurnMode:
        if (mKeyTurnPanel.keyMode())
        {
          mMode = ePartyMode;
        }
        break;
      case ePartyMode:
        mPartyPanel.partyMode();
        break;
    }
  }
  else
  {
    offMode();
  }
}
