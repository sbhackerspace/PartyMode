//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a header for test mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"
#include "TogglePanel.h"
#include "DialPanel.h"
#include "PhonePanel.h"
#include "KeyTurnPanel.h"
#include "TaintPanel.h"
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

    void initialize();

  private:

    enum Mode
    {
      eOffMode,
      eToggleMode,
      eDialMode,
      ePhoneMode,
      eKeyTurnMode,
      eTaintMode,
      eBigRedButtonMode,
      ePartyMode
    };

  private:

    TogglePanel mTogglePanel;
    DialPanel mDialPanel;
    PhonePanel mPhonePanel;
    KeyTurnPanel mKeyTurnPanel;
    TaintPanel mTaintPanel;
    BigRedButtonPanel mBigRedButtonPanel;
    PartyModePanel mPartyModePanel;

    Mode mMode;
};

