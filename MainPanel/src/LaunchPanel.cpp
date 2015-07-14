//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the launch mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "LaunchPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
LaunchPanel::LaunchPanel()
  : Panel(),
    mLaunchInitialized(false),
    mLaunchSuccess(false),
    mRandomizedTogglePins({{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}),
    mRandomizedToggleLeds({{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}),
    mRow(0),
    mColumn(0),
    mCorrectToggleState(false),
    mCorrectSideState(false),
    mTimeout(10000),
    mLastFlashTime(0),
    mProgressCounter(0)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LaunchPanel::initializeLaunch()
{
  clearStates();
  writeLeds();
  mProgressCounter = mRow = mColumn = 0;
  int Temp, randomRow, randomColumn;
  memcpy(mRandomizedTogglePins, mToggleMap, sizeof(mToggleMap));
  memcpy(mRandomizedToggleLeds, mToggleLeds, sizeof(mToggleLeds));
  for (int i = 0; i < mTotalNumberOfRows; ++i)
  {
    for (int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      randomRow = random(i, mTotalNumberOfRows);
      randomColumn = random(j, mTotalNumberOfColumns);

      Temp = mRandomizedTogglePins[i][j];
      mRandomizedTogglePins[i][j] = mRandomizedTogglePins[randomRow][randomColumn];
      mRandomizedTogglePins[randomRow][randomColumn] = Temp;

      Temp = mRandomizedToggleLeds[i][j];
      mRandomizedToggleLeds[i][j] = mRandomizedToggleLeds[randomRow][randomColumn];
      mRandomizedToggleLeds[randomRow][randomColumn] = Temp;
    }
  }
  mCorrectToggleState = getCorrectState(mRandomizedTogglePins[0][0]);
  mCorrectSideState = getCorrectState(mSideSwitches[0]);
  digitalWrite(mSideLeds[mRow], !isInverted(mSideLeds[mRow]));
  mLastMoveTime = millis();
  mLaunchInitialized = true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean LaunchPanel::correctToggleAndSwitchFlipped()
{
  return ((mCorrectToggleState == digitalRead(mRandomizedTogglePins[mRow][mColumn])) &&
  (mCorrectSideState == digitalRead(mSideSwitches[mRow])));
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LaunchPanel::flashCurrentLed()
{
  if (millis() - mLastFlashTime > 100)
  {
    mCurrentFlashState = !mCurrentFlashState;
    mLastFlashTime = millis();
  }
  if (mCurrentFlashState)
  {
    digitalWrite(mRandomizedToggleLeds[mRow][mColumn], HIGH);
  }
  else
  {
    digitalWrite(mRandomizedToggleLeds[mRow][mColumn], LOW);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LaunchPanel::launchMode()
{
  if (!mLaunchInitialized)
  {
    initializeLaunch();
  }

  if (millis() - mLastMoveTime > mTimeout)
  {
    mLaunchInitialized = false;
    return;
  }

  if (correctToggleAndSwitchFlipped())
  {
    mProgressCounter++;
    digitalWrite(
      mRandomizedToggleLeds[mRow][mColumn],
      isInverted(mRandomizedTogglePins[mRow][mColumn]));
    columnIncrement(mColumn);
    if (mColumn == 0)
    {
      rowIncrement(mRow);
    }
    digitalWrite(mSideLeds[mRow], !isInverted(mSideLeds[mRow]));
    mCorrectToggleState = getCorrectState(mRandomizedTogglePins[mRow][mColumn]);
    mCorrectSideState = getCorrectState(mSideSwitches[mRow]);
    mLastMoveTime = millis();
  }
  flashCurrentLed();
}
