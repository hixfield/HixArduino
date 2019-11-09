#ifndef HixPinDigitalInput_h
#define HixPinDigitalInput_h


#include "HixPinDigital.h"


class HixPinDigitalInput : public HixPinDigital {

  public:

    HixPinDigitalInput(int nPinNumber);
    void begin();
    void attachInterrupt( void (isr)(void), int mode);
};


#endif
