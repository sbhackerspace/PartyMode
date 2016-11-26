//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a header for test mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class TestPanel : public Panel
{
  public:

	  TestPanel(Ring& ring);

    void run();

  private:

    TestPanel(const TestPanel&);
    TestPanel& operator = (const TestPanel&);

};

