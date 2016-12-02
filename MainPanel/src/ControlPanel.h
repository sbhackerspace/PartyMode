//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a header for test mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"
#include "LaunchPanel.h"
#include "DialPanel.h"
#include "PhonePanel.h"
#include "KeyTurnPanel.h"
#include "BigRedButtonPanel.h"
#include "PartyModePanel.h"

class ControlPanel : public Panel
{
  public:

	  ControlPanel(Ring& ring);

    void run();

  private:

    void PARTY();

    ControlPanel(const ControlPanel&);
    ControlPanel& operator = (const ControlPanel&);

  private:

    enum Mode
    {
      eOffMode,
      eLaunchMode,
      eDialMode,
      ePhoneMode,
      eKeyTurnMode,
      eBigRedButtonMode,
      ePartyMode
    };

  private:

    LaunchPanel mLaunchPanel;
    DialPanel mDialPanel;
    PhonePanel mPhonePanel;
    KeyTurnPanel mKeyTurnPanel;
    BigRedButtonPanel mBigRedButtonPanel;
    PartyModePanel mPartyModePanel;

    Mode mMode;
};

