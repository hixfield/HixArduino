#ifndef HixPinDigitalInput_h
#define HixPinDigitalInput_h

#include "HixPinDigital.h"

class HixPinDigitalInput : public HixPinDigital
{

public:
  HixPinDigitalInput(int nPinNumber);
  bool begin();
  bool begin(int mode);
  void attachInterrupt(void(isr)(void), int mode);
};

#endif
