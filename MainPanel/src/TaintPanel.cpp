//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the class for the key turn mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "TaintPanel.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
TaintPanel::TaintPanel(Ring& ring)
  : Panel(ring),
    mCountdownTimer(0),
    mRow0(0),
    mRow1(0),
    mRow2(0),
    mRow3(0),
    mColumn(1),
    mColor(0x0000FF),
    mCountdownIndex(0)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TaintPanel::initialize(
  uint8_t Row0,
  uint8_t Row1,
  uint8_t Row2,
  uint8_t Row3,
  uint8_t Column)
{
  mCountdownTimer = millis();
  mRow0 = Row0;
  mRow1 = Row1;
  mRow2 = Row2;
  mRow3 = Row3;
  mColumn = Column;
  mCountdownIndex = 0;
  mRing.clearRing();
  mColor = 0x0000FF;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
static void setValue(bool Condition, int Index, uint8_t& Value)
{
  if (Condition)
  {
    bitSet(Value, Index);
  }
  else
  {
    bitClear(Value, Index);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TaintPanel::getValue(int Row, int Column, uint8_t& Value)
{
  setValue(mToggleStates[Row][Column], Column, Value);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TaintPanel::countDown()
{
  if (abs(millis() - mCountdownTimer) > 400)
  {
    if (mCountdownIndex < mRing.getNumPixels())
    {
      mRing.setPixelColor(mCountdownIndex++, mColor);
    }
    else
    {
      mCountdownIndex = 0;

      if(mColor == 0x0000FF)
      {
        mColor = 0x00FF00;
      }
      else if (mColor == 0x00FF00)
      {
        mColor = 0xFF0000;
      }
      else
      {
        mRing.clearRing();
        fail();
      }
    }
    mCountdownTimer = millis();

  }
  mRing.show();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean TaintPanel::taint()
{
  countDown();

  getSwitchStates();

  writeLeds();

  if (mRedState)
  {
    uint8_t Row0 = 0;
    uint8_t Row1 = 0;
    uint8_t Row2 = 0;
    uint8_t Row3 = 0;
    uint8_t Column = 0;

    for(int i = 0; i < mTotalNumberOfColumns; i++)
    {
      getValue(0, i, Row0);
      getValue(1, i, Row1);
      getValue(2, i, Row2);
      getValue(3, i, Row3);
      setValue(mSideStates[i], i, Column);
    }

    if (Row0 == mRow0 && Row1 == mRow1 && Row2 == mRow2 && Row3 == mRow3, Column == mColumn)
    {
      Serial.println("woot");
      mRing.clearRing();
      return true;
    }
    else
    {
      Serial.println("taintfail");
      mRing.clearRing();
      fail();
    }
  }

  return false;
}
