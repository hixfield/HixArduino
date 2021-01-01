#ifndef HixRGBLed_h
#define HixRGBLed_h

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Ticker.h>

#include "HixColor.h"
#include "HixLED.h"
#include "HixLedAnimation.h"

class HixRGBLed : public Adafruit_NeoPixel {
   private:
    uint8_t m_nDefaultDimPercent;
    HixColor m_currentColor;
    //vars used in animation
    Ticker m_ticker;
    HixLedAnimation m_currentLedAnimation = HixLedAnimation::off;
    bool m_bBlinkCurrentlyOn;
    unsigned long m_nFadePercentage;
    bool m_bFadeDirection;
    //used for the animations
    void tickerISR(void);

   public:
    //constructor
    HixRGBLed(int nPinNumber, neoPixelType t, uint8_t nDefaultDimPercent);
    //put color value
    void setColor(HixColor color);
    void setColor(HixColor color, uint8_t nDimPercent);
    //make blink
    void setAnimate(HixLedAnimation ledMode);
};

#endif
