#ifndef HixPinPWM_h
#define HixPinPWM_h

#include "HixPin.h"

class HixPinPWM : HixPin {

	int m_nCurrentValue;

  public:

    //Only pin 9 and 10 are supported. And if you enable it on one of these pins the other pins PWM freq is also set to 25KHz
    //you can however mix 25KHz PWM in 9 or 10 with normal 500 Hz pwm on e.g. pin 3
    HixPinPWM(int nPinNumber);
    bool begin();
    void analogWriteRaw(int nValue);
    void analogWritePercent(float fPercent);
    int getRaw(void);
    float getPercent(void);
};

#endif
