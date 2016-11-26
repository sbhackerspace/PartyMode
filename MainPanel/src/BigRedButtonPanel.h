//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a header for big red button mode panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class BigRedButtonPanel : public Panel
{
  public:

	  BigRedButtonPanel(Ring& ring);

    void initializeBigRedButton();

    bool  bigRedButtonMode();

  private:

    BigRedButtonPanel(const BigRedButtonPanel&);
    BigRedButtonPanel& operator = (const BigRedButtonPanel&);

};


