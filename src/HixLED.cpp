#include "HixLED.h"

HixLED::HixLED(int nPinNumber) : HixPinDigitalOutput(nPinNumber) {
}

void HixLED::digitalWrite(bool bValue) {
    if (bValue)
        on();
    else
        off();
};

void HixLED::setAnimate(HixLedAnimation ledAnimation) {
    //if no change nothing todo
    if (m_currentLedAnimation == ledAnimation) return;
    //set my mode
    m_currentLedAnimation = ledAnimation;
    //init to know state
    m_nFadePercentage = 0;
    m_bFadeDirection = true;
    //define period
    switch (m_currentLedAnimation) {
        case HixLedAnimation::off:
            off();
            return;
        case HixLedAnimation::on:
            on();
            return;
        case HixLedAnimation::slowBlink:
            slowBlink();
            return;
        case HixLedAnimation::blink:
            blink();
            return;
        case HixLedAnimation::fastBlink:
            fastBlink();
            return;
        case HixLedAnimation::fadeInOut:
            fadeInOut();
            return;
    }
}

void HixLED::on(void) {
    if (m_currentLedAnimation == HixLedAnimation::on) return;
    m_currentLedAnimation = HixLedAnimation::on;
    HixPinDigitalOutput::high();
    m_ticker.detach();
}

void HixLED::off(void) {
    if (m_currentLedAnimation == HixLedAnimation::off) return;
    m_currentLedAnimation = HixLedAnimation::off;
    HixPinDigitalOutput::low();
    m_ticker.detach();
}

void HixLED::blink(bool bOn, int nNumberOfBlinks, int nDelayMs) {
    HixPinDigitalOutput::blink(bOn, nNumberOfBlinks, nDelayMs);
}

void HixLED::slowBlink(void) {
    if (m_currentLedAnimation == HixLedAnimation::slowBlink) return;
    m_currentLedAnimation = HixLedAnimation::slowBlink;
    m_ticker.detach();
    m_ticker.attach_ms(HIXLEDANIMATION_PERIOD_SLOW_BLINK_MS, std::bind(&HixLED::tickerISR, this));
}

void HixLED::blink(void) {
    if (m_currentLedAnimation == HixLedAnimation::blink) return;
    m_currentLedAnimation = HixLedAnimation::blink;
    m_ticker.detach();
    m_ticker.attach_ms(HIXLEDANIMATION_PERIOD_BLINK_MS, std::bind(&HixLED::tickerISR, this));
}

void HixLED::fastBlink(void) {
    if (m_currentLedAnimation == HixLedAnimation::fastBlink) return;
    m_currentLedAnimation = HixLedAnimation::fastBlink;
    m_ticker.detach();
    m_ticker.attach_ms(HIXLEDANIMATION_PERIOD_FAST_BLINK_MS, std::bind(&HixLED::tickerISR, this));
}

void HixLED::fadeInOut(void) {
    if (m_currentLedAnimation == HixLedAnimation::fadeInOut) return;
    m_currentLedAnimation = HixLedAnimation::fadeInOut;
    m_nFadePercentage = 0;
    m_bFadeDirection = true;
    m_ticker.detach();
    m_ticker.attach_ms(HIXLEDANIMATION_PERIOD_FADEINOUT_MS / 100, std::bind(&HixLED::tickerISR, this));
}

void HixLED::tickerISR(void) {
    switch (m_currentLedAnimation) {
        case HixLedAnimation::slowBlink:
            HixPinDigitalOutput::toggle();
            break;
        case HixLedAnimation::blink:
            HixPinDigitalOutput::toggle();
            break;
        case HixLedAnimation::fastBlink:
            HixPinDigitalOutput::toggle();
            break;
        case HixLedAnimation::fadeInOut:
            //count up or down
            if (m_bFadeDirection)
                m_nFadePercentage++;
            else
                m_nFadePercentage--;
            //reverse direction if we hit a bounds
            if (m_nFadePercentage > m_nFadePercentage) m_bFadeDirection = false;
            if (m_nFadePercentage == 0) m_bFadeDirection = true;
            //update the led
            ::analogWrite(m_nPinNumber, PWMRANGE * m_nFadePercentage / 100);
            break;
        default:
            break;
    }
}