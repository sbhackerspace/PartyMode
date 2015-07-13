//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for party mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "PartyModePanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
PartyModePanel::PartyModePanel(long ModeDuration)
  : Panel(),
    mCurrentModeStartTime(0),
    mLastMoveTime(0),
    mModeDuration(ModeDuration),
    mCurrentMode(eSnake),
    mRow(0),
    mColumn(0)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
PartyModePanel::PartyModePanel(
  long ModeDuration,
  int TotalNumberOfRows,
  int TotalNumberOfColumns)
  : Panel(TotalNumberOfRows, TotalNumberOfColumns),
    mCurrentModeStartTime(0),
    mLastMoveTime(0),
    mModeDuration(ModeDuration),
    mCurrentMode(eSnake),
    mRow(0),
    mColumn(0)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void PartyModePanel::goToNextMode()
{
  if (mCurrentMode == eRowRoll)
  {
    mCurrentMode = eColumnRoll;
  }
  else if (mCurrentMode == eColumnRoll)
  {
    mCurrentMode = eSnake;
  }
  else if (mCurrentMode == eSnake)
  {
    mCurrentMode = eRowRoll;
  }
  else
  {
    Serial.println("ERROR: Invalid party mode");
  }
  mRow = mColumn = 0;

  mCurrentModeStartTime = mLastMoveTime = millis();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void PartyModePanel::rollingIncrement(int& Index)
{
  Index++;
  if (Index > 3)
  {
    Index = 0;
  }
  mLastMoveTime = millis();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void PartyModePanel::rowRoll()
{
  if (millis() - mLastMoveTime > mModeDuration/40)
  {
    rollingIncrement(mRow);
  }
  for (int i = 0; i < mTotalNumberOfRows; ++i)
  {
    mToggleStates[mRow][i] = !isInverted(mToggleMap[mRow][i]);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void PartyModePanel::columnRoll()
{
  if (millis() - mLastMoveTime > mModeDuration/40)
  {
    rollingIncrement(mColumn);
  }
  for (int i = 0; i < mTotalNumberOfColumns; ++i)
  {
    mToggleStates[i][mColumn] = !isInverted(mToggleMap[i][mColumn]);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void PartyModePanel::snake()
{
  long currentTime = millis();
  if (currentTime - mLastMoveTime > mModeDuration/40)
  {
    rollingIncrement(mColumn);
    if (mColumn == 0)
    {
      rollingIncrement(mRow);
    }
  }
  mToggleStates[mRow][mColumn] = !isInverted(mToggleMap[mRow][mColumn]);
  if (mColumn == 0 && mRow == 0)
  {
    if (currentTime - mCurrentModeStartTime > 100)
    {
      mToggleStates[mTotalNumberOfRows-1][mTotalNumberOfColumns-1] =
        !isInverted(mToggleMap[mTotalNumberOfRows-1][mTotalNumberOfColumns-1]);
      mToggleStates[mTotalNumberOfRows-1][mTotalNumberOfColumns-2] =
        !isInverted(mToggleMap[mTotalNumberOfRows-1][mTotalNumberOfColumns-2]);
    }
  }
  else if (mColumn == 0)
  {
    mToggleStates[mRow - 1][mTotalNumberOfColumns - 1] =
      !isInverted(mToggleMap[mRow - 1][mTotalNumberOfColumns - 1]);
    mToggleStates[mRow - 1][mTotalNumberOfColumns - 2] =
      !isInverted(mToggleMap[mRow - 1][mTotalNumberOfColumns - 2]);
  }
  else if (mColumn == 1)
  {
    mToggleStates[mRow][0] = !isInverted(mToggleMap[mRow][0]);
    mToggleStates[mRow - 1][mTotalNumberOfColumns - 1] =
      !isInverted(mToggleStates[mRow - 1][mTotalNumberOfColumns - 1]);

  }
  else
  {
    mToggleStates[mRow][mColumn - 1] = !isInverted(mToggleMap[mRow][mColumn]);
    mToggleStates[mRow][mColumn - 2] = !isInverted(mToggleMap[mRow][mColumn]);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void PartyModePanel::clearStates()
{
  for (int i = 0; i < mTotalNumberOfRows; ++i)
  {
    for (int j = 0; j < mTotalNumberOfColumns; ++j)
    {
      mToggleStates[i][j] = isInverted(mToggleMap[i][j]);
    }
      mSideStates[i] = !isInverted(mSideSwitches[i]);
  }
  mRightKeyState = isInverted(mRightKeyPin);
  mLeftKeyState = isInverted(mLeftKeyPin);
  mRedState = isInverted(mRedButtonPin);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void PartyModePanel::partyMode()
{
  clearStates();
  if (mCurrentMode == eRowRoll)
  {
    rowRoll();
  }
  else if (mCurrentMode == eColumnRoll)
  {
    columnRoll();
  }
  else if (mCurrentMode == eSnake)
  {
    snake();
  }
  else if (mCurrentMode == eRowColumnRoll)
  {
    rowRoll();
    columnRoll();
  }
  else
  {
    Serial.println("ERROR: Invalid party mode");
  }

  writeLeds();

  if (millis() - mCurrentModeStartTime > mModeDuration)
  {
    goToNextMode();
  }
}
