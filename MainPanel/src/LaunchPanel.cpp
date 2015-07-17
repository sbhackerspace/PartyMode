//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the launch mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "LaunchPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
LaunchPanel::LaunchPanel(Ring& ring)
  : Panel(ring),
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
  getRandomizedSwitchStates(
    mRandomizedToggleStates,
    mSideStates,
    mLeftKeyState,
    mRightKeyState,
    mRedState);
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
void LaunchPanel::getRandomizedSwitchStates(
  boolean toggleStates[4][4],
  boolean sideStates[4],
  boolean& leftKeyState,
  boolean& rightKeyState,
  boolean& redState)
{
  for(int i = 0; i < mTotalNumberOfRows; i++)
  {
    for(int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      getSwitchState(toggleStates[i][j], mRandomizedTogglePins[i][j]);
    }
    getSwitchState(sideStates[i], mSideSwitches[i]);
  }
  getSwitchState(leftKeyState, mLeftKeyPin);
  getSwitchState(rightKeyState, mRightKeyPin);
  getSwitchState(redState, mRedButtonPin);
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
boolean LaunchPanel::incorrectToggleOrSwitchFlipped()
{
  boolean toggleStates[4][4];
  boolean sideStates[4];
  boolean leftKeyState, rightKeyState, redState;
  getRandomizedSwitchStates(
    toggleStates,
    sideStates,
    leftKeyState,
    rightKeyState,
    redState);
  for (int i = 0; i < mTotalNumberOfRows; ++i)
  {
    for (int j =0; j < mTotalNumberOfColumns; ++j)
    {
      if
        ((toggleStates[i][j] != mRandomizedToggleStates[i][j]) &&
        (!((i == mRow) && (j == mColumn))))
      {
        return true;
      }
    }
    if ((sideStates[i] != mSideStates[i]) && (i != mRow))
    {
      return true;
    }
  }
  if
    ((leftKeyState != mLeftKeyState) ||
     (rightKeyState != mRightKeyState) ||
     (redState != mRedState))
  {
    return true;
  }
  return false;
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
  getRandomizedSwitchStates(
    mRandomizedToggleStates,
    mSideStates,
    mLeftKeyState,
    mRightKeyState,
    mRedState);

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
  else if(incorrectToggleOrSwitchFlipped())
  {
    fail();
    mLaunchInitialized = false;
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
