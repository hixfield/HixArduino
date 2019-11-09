#ifndef HixPinDigital_h
#define HixPinDigital_h


#include "HixPin.h"


class HixPinDigital: public HixPin {

  public:
  	
    HixPinDigital(int nPinNumber);
    bool digitalRead(void);
    bool isHigh(void);
    bool isLow(void);
};


#endif
