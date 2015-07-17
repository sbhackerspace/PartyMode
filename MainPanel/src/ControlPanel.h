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
#include "KeyTurnPanel.h"
#include "PartyModePanel.h"

class ControlPanel : public Panel
{
  public:

	  ControlPanel(Ring& ring);

    void run();

  private:

    ControlPanel(const ControlPanel&);
    ControlPanel& operator = (const ControlPanel&);

  private:

    enum Mode
    {
      eOffMode,
      eLaunchMode,
      eDialMode,
      eKeyTurnMode,
      ePartyMode
    };

  private:

    LaunchPanel mLaunchPanel;
    DialPanel mDialPanel;
    KeyTurnPanel mKeyTurnPanel;
    PartyModePanel mPartyPanel;

    Mode mMode;
};

