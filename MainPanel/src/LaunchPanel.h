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

    boolean launchMode();

  private:

    void initializeLaunch();

    void clearRandomizedToggles();

    boolean correctToggleAndSwitchFlipped();
    boolean getCorrectState(int pin);

    void flashCurrentLed();
    void flashRemainingLeds();

    void turnOnOnlyCompletedLights();

    void incrementToggle();

    void temporarySuccesMethod();

    LaunchPanel(const LaunchPanel&);
    LaunchPanel& operator = (const LaunchPanel&);

  private:

    boolean mInScrollMode;
    boolean mLaunchInitialized;
    boolean mLaunchSuccess;
    int mRandomizedTogglePins[4][4];
    int mRandomizedToggleLeds[4][4];
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
boolean LaunchPanel::getCorrectState(int pin)
{
  return !digitalRead(pin);
}
