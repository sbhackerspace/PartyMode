//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the header for the toggle mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class TogglePanel : public Panel
{
  public:

	  TogglePanel(Ring& ring);

    boolean toggleMode();

    void initializeToggle();

  private:

    void clearRandomizedToggles();

    boolean correctToggleAndSwitchFlipped();
    boolean incorrectToggleOrSwitchFlipped();

    void getRandomizedSwitchStates(
      boolean toggleStates[4][4],
      boolean sideStates[4],
      boolean& leftKeyState,
      boolean& rightKeyState,
      boolean& redState);

    boolean getCorrectState(int pin);

    void flashCurrentLed();
    void flashRemainingLeds();

    void turnOnOnlyCompletedLights();

    void incrementToggle();

    void temporarySuccesMethod();

    TogglePanel(const TogglePanel&);
    TogglePanel& operator = (const TogglePanel&);

  protected:

    boolean mToggleInitialized;

  private:

    boolean mInScrollMode;
    boolean mToggleSuccess;
    int mRandomizedTogglePins[4][4];
    int mRandomizedToggleLeds[4][4];
    boolean mRandomizedToggleStates[4][4];
    int mRow, mColumn;
    int mScrollRow, mScrollColumn;
    boolean mCorrectToggleState, mCorrectSideState;
    long mTimeout;

    long mLastFlashTime;
    boolean mCurrentFlashState;

    int mProgressCounter;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline
boolean TogglePanel::getCorrectState(int pin)
{
  return !digitalRead(pin);
}
