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
    mInScrollMode(true),
    mLaunchInitialized(false),
    mLaunchSuccess(false),
    mRandomizedTogglePins({{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}),
    mRandomizedToggleLeds({{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}),
    mRow(0),
    mColumn(0),
    mCorrectToggleState(false),
    mCorrectSideState(false),
    mTimeout(20000),
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
  mLastMoveTime = millis();
  mLaunchInitialized = mInScrollMode = true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LaunchPanel::clearRandomizedToggles()
{
  for (int i = 0; i < mTotalNumberOfRows; ++i)
  {
    for (int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      mToggleStates[i][j] = isInverted(mRandomizedTogglePins[i][j]);
    }
  }
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
void LaunchPanel::turnOnOnlyCompletedLights()
{
  clearRandomizedToggles();
  for(int i = 0; i <= mTotalNumberOfRows; ++i)
  {
    for (int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      if (i * mTotalNumberOfRows + j < mProgressCounter)
      {
        mToggleStates[i][j] = !isInverted(mRandomizedTogglePins[i][j]);
      }
    }
  }
  writeLeds(mRandomizedToggleLeds);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LaunchPanel::flashCurrentLed()
{
  turnOnOnlyCompletedLights();
  digitalWrite(mSideLeds[mRow], !isInverted(mSideLeds[mRow]));
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
void LaunchPanel::flashRemainingLeds()
{
  turnOnOnlyCompletedLights();
  digitalWrite(
    mRandomizedToggleLeds[mScrollRow][mScrollColumn],
    !isInverted(mRandomizedTogglePins[mScrollRow][mScrollColumn]));

  if (millis() - mLastMoveTime > + random(600) + 50)
  {
    columnIncrement(mScrollColumn);
    if(mScrollColumn == 0)
    {
      rowIncrement(mScrollRow);
    }

    if (!mScrollRow && !mScrollColumn)
    {
      mInScrollMode = false;
    }

    mLastMoveTime = millis();
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LaunchPanel::incrementToggle()
{
  mProgressCounter++;

  columnIncrement(mColumn);
  if (mColumn == 0)
  {
    rowIncrement(mRow);
    if (!mRow && !mColumn)
    {
      mLaunchSuccess = true;
    }
  }

  digitalWrite(mSideLeds[mRow], !isInverted(mSideLeds[mRow]));

  mCorrectToggleState = getCorrectState(mRandomizedTogglePins[mRow][mColumn]);
  mCorrectSideState = getCorrectState(mSideSwitches[mRow]);

  mScrollRow = mRow;
  mScrollColumn = mColumn;
  mInScrollMode = true;
  mLastMoveTime = millis();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LaunchPanel::temporarySuccesMethod()
{
  clearStates();
  writeLeds();
  if (millis() - mLastFlashTime > 100)
  {
    mCurrentFlashState = !mCurrentFlashState;
    mLastFlashTime = millis();
  }
  if (mCurrentFlashState)
  {
    digitalWrite(mRedLed, HIGH);
  }
  else
  {
    digitalWrite(mRedLed, LOW);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean LaunchPanel::launchMode()
{
  if (!mLaunchInitialized)
  {
    initializeLaunch();
  }

  if (mLaunchSuccess)
  {
    temporarySuccesMethod();
    return true;
  }

  if (millis() - mLastMoveTime > mTimeout)
  {
    mLaunchInitialized = false;
    return false;
  }

  if (correctToggleAndSwitchFlipped())
  {
    incrementToggle();
  }

  if (mInScrollMode)
  {
    flashRemainingLeds();
  }
  else
  {
    flashCurrentLed();
  }
  return false;
}
