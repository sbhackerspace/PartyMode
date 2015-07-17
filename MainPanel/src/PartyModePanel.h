//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the header for party mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class PartyModePanel : public Panel
{
  public:

	  PartyModePanel(Ring& ring, long ModeDuration);

    void partyMode();

  private:

    void rowRoll();
    void columnRoll();
    void snake();

    void goToNextMode();

    PartyModePanel(const PartyModePanel&);
    PartyModePanel& operator = (const PartyModePanel&);

  private:

    enum PartyMode
    {
      eRowRoll,
      eColumnRoll,
      eRowColumnRoll,
      eSnake
    };

  private:

    long mCurrentModeStartTime, mLastMoveTime, mModeDuration;

    PartyMode mCurrentMode;

    int mRow, mColumn;

};

