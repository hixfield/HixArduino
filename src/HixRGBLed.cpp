#include "HixRGBLed.h"

HixRGBLed::HixRGBLed(int nPinNumber, neoPixelType t, uint8_t nDefaultDimPercent) : Adafruit_NeoPixel(1, nPinNumber, t),
                                                                                   m_nDefaultDimPercent(nDefaultDimPercent) {
}

void HixRGBLed::setColor(HixColor color, uint8_t nDimPercent) {
    m_currentColor = color.getDimmedWithPercent(nDimPercent);
    setPixelColor(0, m_currentColor.getRGB());
    show();
}

void HixRGBLed::setColor(HixColor color) {
    setColor(color, m_nDefaultDimPercent);
}

void HixRGBLed::setColor(const char* szRGBString) {
    m_currentColor = parseColor(szRGBString);
    setPixelColor(0, m_currentColor.getRGB());
    show();
}

uint32_t HixRGBLed::parseColor(const char* szRGBString) {
    //must always have 6 characters
    if (strlen(szRGBString) != 6) return 0;
    //storin components
    const uint32_t hexBase = 16;
    uint32_t nR = hexCharToInt(szRGBString[5]) * hexBase + hexCharToInt(szRGBString[4]);
    uint32_t nG = hexCharToInt(szRGBString[3]) * hexBase + hexCharToInt(szRGBString[2]);
    uint32_t nB = hexCharToInt(szRGBString[1]) * hexBase + hexCharToInt(szRGBString[0]);
    //reassemble
    uint32_t nColor = (nR << 16) | (nG << 8) | nB;
    //return our calculated value
    return nColor;
}

uint32_t HixRGBLed::hexCharToInt(char c) {
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
        //no match return zero
        default:
            return 0;
    }
}

void HixRGBLed::setAnimate(HixLedAnimation ledAnimation) {
    //if no change nothing todo
    if (m_currentLedAnimation == ledAnimation) return;
    //set my mode
    m_currentLedAnimation = ledAnimation;
    //init to know state
    m_bBlinkCurrentlyOn = true;
    m_nFadePercentage = 0;
    m_bFadeDirection = true;
    //define period
    switch (m_currentLedAnimation) {
        case HixLedAnimation::off:
            m_ticker.detach();
            setPixelColor(0, 0);
            show();
            return;
        case HixLedAnimation::on:
            m_ticker.detach();
            setPixelColor(0, m_currentColor.getRGB());
            show();
            return;
        case HixLedAnimation::slowBlink:
            m_ticker.detach();
            m_ticker.attach_ms(HIXLEDANIMATION_PERIOD_SLOW_BLINK_MS, std::bind(&HixRGBLed::tickerISR, this));
            return;
        case HixLedAnimation::blink:
            m_ticker.detach();
            m_ticker.attach_ms(HIXLEDANIMATION_PERIOD_BLINK_MS, std::bind(&HixRGBLed::tickerISR, this));
            return;
        case HixLedAnimation::fastBlink:
            m_ticker.detach();
            m_ticker.attach_ms(HIXLEDANIMATION_PERIOD_FAST_BLINK_MS, std::bind(&HixRGBLed::tickerISR, this));
            return;
        case HixLedAnimation::fadeInOut:
            m_ticker.detach();
            m_ticker.attach_ms(HIXLEDANIMATION_PERIOD_FADEINOUT_MS / 100, std::bind(&HixRGBLed::tickerISR, this));
            return;
    }
}

void HixRGBLed::tickerISR(void) {
    switch (m_currentLedAnimation) {
        case HixLedAnimation::slowBlink:
        case HixLedAnimation::blink:
        case HixLedAnimation::fastBlink:
            setPixelColor(0, (m_bBlinkCurrentlyOn) ? m_currentColor.getRGB() : 0);
            show();
            m_bBlinkCurrentlyOn = !m_bBlinkCurrentlyOn;
            return;
        case HixLedAnimation::fadeInOut:
            //count up or down
            if (m_bFadeDirection)
                m_nFadePercentage++;
            else
                m_nFadePercentage--;
            //reverse direction if we hit a bounds
            if (m_nFadePercentage > 100) m_bFadeDirection = false;
            if (m_nFadePercentage == 0) m_bFadeDirection = true;
            //update the led
            setPixelColor(0, m_currentColor.getDimmedWithPercent(m_nFadePercentage));
            show();
            //todo
            break;
        default:
            break;
    }
}