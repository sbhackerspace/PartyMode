//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is a header for phone mode panels
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#pragma once

#include "Panel.h"

class PhonePanel : public Panel
{
  public:

	  PhonePanel(Ring& ring);

    void initializePhone();

    boolean phoneMode();

  private:

    PhonePanel(const PhonePanel&);
    PhonePanel& operator = (const PhonePanel&);

  private:

    boolean mPhoneInitialized;
};

