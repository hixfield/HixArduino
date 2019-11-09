#ifndef HixPinDigitalOutput_h
#define HixPinDigitalOutput_h


#include "HixPinDigital.h"


class HixPinDigitalOutput : public HixPinDigital {

  public:

    HixPinDigitalOutput(int nPinNumber);
    bool begin();
    void high(void);
    void low(void);
    void digitalWrite(bool value);
    void blink(bool bOn, int nNumberOfBlinks, int nDelayOnMs, int nDelayOffMs);
    void blink(bool bOn, int nNumberOfBlinks, int nDelayMs);
    void toggle(void);
};


#endif
