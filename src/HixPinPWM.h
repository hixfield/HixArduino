#ifndef HixPinPWM_h
#define HixPinPWM_h

#include "HixPin.h"

class HixPinPWM : HixPin {

	int m_nCurrentValue;

  public:

    HixPinPWM(int nPinNumber);
    bool begin();
    void analogWriteRaw(int nValue);
    void analogWritePercent(float fPercent);
    int getRaw(void);
    float getPercent(void);
};

#endif
