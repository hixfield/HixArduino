#ifndef HixLED_h
#define HixLED_h

#include <HixLedAnimation.h>
#include <HixPinDigitalOutput.h>
#include <Ticker.h>
#include <arduino.h>

class HixLED : public HixPinDigitalOutput {
   private:
    Ticker m_ticker;
    HixLedAnimation m_currentLedAnimation = HixLedAnimation::off;
    unsigned long m_nFadePercentage = 0;
    bool m_bFadeDirection = true;

   public:
    HixLED(int nPinNumber);
    void digitalWrite(bool bValue);
    void blink(bool bOn, int nNumberOfBlinks, int nDelayMs);
    //make animation
    void setAnimate(HixLedAnimation ledMode);
    //individual functions
    void on(void);
    void off(void);
    void slowBlink(void);
    void blink(void);
    void fastBlink(void);
    void fadeInOut(void);
    void tickerISR(void);
};

#endif
