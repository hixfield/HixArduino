#ifndef HixPinAnalogInput_h
#define HixPinAnalogInput_h


#include "HixPin.h"


class HixPinAnalogInput : public HixPin {

  public:

    HixPinAnalogInput(int nPinNumber);
    bool begin();
    int analogRead();
};


#endif
