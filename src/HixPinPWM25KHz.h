#ifndef HixPinPWM25KHz_h
#define HixPinPWM25KHz_h

#include "HixPin.h"

class HixPinPWM25KHz : HixPin {

  public:

    HixPinPWM25KHz(int nPinNumber);
    bool begin();
    void analogWritePercent(float fPercent);
    float getPercent(void);
};

#endif
