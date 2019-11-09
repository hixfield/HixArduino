#ifndef HixPinDigital_h
#define HixPinDigital_h

#include "HixPin.h"

//*virtual* class for inherited HixPinInput and HixPinOutput

class HixPinDigital: public HixPin {

  public:
    HixPinDigital(int nPinNumber);
    bool digitalRead(void);
    bool isHigh(void);
    bool isLow(void);
};

#endif
