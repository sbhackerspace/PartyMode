//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a class for test mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class TestPanel : public Panel
{
  public:

	  TestPanel();

    void testMode();

  private:

    TestPanel(const TestPanel&);
    TestPanel& operator = (const TestPanel&);

};
