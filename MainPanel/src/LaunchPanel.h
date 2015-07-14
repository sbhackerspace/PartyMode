//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the header for the launch mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class LaunchPanel : public Panel
{
  public:

	  LaunchPanel();

    void launchMode();

  private:

    void initializeLaunch();

    boolean correctToggleAndSwitchFlipped();
    boolean getCorrectState(int pin);

    void flashCurrentLed();

    LaunchPanel(const LaunchPanel&);
    LaunchPanel& operator = (const LaunchPanel&);

  private:

    boolean mLaunchInitialized;
    boolean mLaunchSuccess;
    int mRandomizedTogglePins[4][4];
    int mRandomizedToggleLeds[4][4];
    int mRow, mColumn;
    boolean mCorrectToggleState, mCorrectSideState;
    long mTimeout;

    long mLastFlashTime;
    boolean mCurrentFlashState;

    int mProgressCounter;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline
boolean LaunchPanel::getCorrectState(int pin)
{
  return !digitalRead(pin);
}
