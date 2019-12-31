#ifndef HixLED_h
#define HixLED_h

#include <HixPinDigitalOutput.h>
#include <Ticker.h>
#include <arduino.h>

enum class HixLedMode { off,
                        on,
                        slowBlink,
                        blink,
                        fastBlink,
                        fadeInOut };

class HixLED : public HixPinDigitalOutput {
  private:
    Ticker              m_ticker;
    const unsigned long m_delaySlowBlinkMs = 1000;
    const unsigned long m_delayBlinkMs     = 400;
    const unsigned long m_delayFastBlinkMs = 100;
    const unsigned long m_delayFadeInOutMs = 1500;
    HixLedMode          m_mode             = HixLedMode::off;
    const unsigned long m_nFadeSteps       = 100;
    unsigned long       m_nFadeCounter     = 0;
    bool                m_bFadeDirection   = true;
    const unsigned long m_nPWMStep         = PWMRANGE / m_nFadeSteps;

  public:
    HixLED(int nPinNumber);
    void digitalWrite(bool bValue);
    void blink(bool bOn, int nNumberOfBlinks, int nDelayMs);
    //async status funtions
    void on(void);
    void off(void);
    void slowBlink(void);
    void blink(void);
    void fastBlink(void);
    void fadeInOut(void);
    void tickerISR(void);
};

#endif
