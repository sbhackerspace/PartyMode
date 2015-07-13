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

	  PartyModePanel(long ModeDuration);
	  PartyModePanel(
      long ModeDuration,
      int TotalNumberOfRows,
      int TotalNumberOfColumns);

    void partyMode();

  private:

    void rowRoll();
    void columnRoll();
    void snake();

    void clearStates();
    void goToNextMode();
    void rollingIncrement(int& Value);

    PartyModePanel(const PartyModePanel&);
    PartyModePanel& operator = (const PartyModePanel&);

  private:

    enum Mode
    {
      eRowRoll,
      eColumnRoll,
      eRowColumnRoll,
      eSnake
    };

  private:

    long mCurrentModeStartTime, mLastMoveTime, mModeDuration;

    Mode mCurrentMode;

    int mRow, mColumn;

};

