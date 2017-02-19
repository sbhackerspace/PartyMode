//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a header for taint mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class TaintPanel : public Panel
{
  public:

	  TaintPanel(Ring& ring);

    void initialize(
      uint8_t Row0,
      uint8_t Row1,
      uint8_t Row2,
      uint8_t Row3,
      uint8_t Column);

    boolean taint();

  private:

    TaintPanel(const TaintPanel&);
    TaintPanel& operator = (const TaintPanel&);

    void getValue(int Row, int Column, uint8_t& Value);

    void countDown();

  private:

    long mCountdownTimer;
    uint8_t mRow0;
    uint8_t mRow1;
    uint8_t mRow2;
    uint8_t mRow3;
    uint8_t mColumn;
    uint32_t mColor;
    int mCountdownIndex;
};

