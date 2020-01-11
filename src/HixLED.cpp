#include "HixLED.h"

HixLED::HixLED(int nPinNumber) : HixPinDigitalOutput(nPinNumber) {
}

void HixLED::digitalWrite(bool bValue) {
    if (bValue)
        on();
    else
        off();
};

void HixLED::on(void) {
    if (m_mode == HixLedMode::on) return;
    m_mode = HixLedMode::on;
    HixPinDigitalOutput::high();
    m_ticker.detach();
}

void HixLED::off(void) {
    if (m_mode == HixLedMode::off) return;
    m_mode = HixLedMode::off;
    HixPinDigitalOutput::low();
    m_ticker.detach();
}

void HixLED::blink(bool bOn, int nNumberOfBlinks, int nDelayMs) {
    HixPinDigitalOutput::blink(bOn, nNumberOfBlinks, nDelayMs);
}

void HixLED::slowBlink(void) {
    if (m_mode == HixLedMode::slowBlink) return;
    m_mode = HixLedMode::slowBlink;
    m_ticker.detach();
    m_ticker.attach_ms(m_delaySlowBlinkMs, std::bind(&HixLED::tickerISR, this));
}

void HixLED::blink(void) {
    if (m_mode == HixLedMode::blink) return;
    m_mode = HixLedMode::blink;
    m_ticker.detach();
    m_ticker.attach_ms(m_delayBlinkMs, std::bind(&HixLED::tickerISR, this));
}

void HixLED::fastBlink(void) {
    if (m_mode == HixLedMode::fastBlink) return;
    m_mode = HixLedMode::fastBlink;
    m_ticker.detach();
    m_ticker.attach_ms(m_delayFastBlinkMs, std::bind(&HixLED::tickerISR, this));
}

void HixLED::fadeInOut(void) {
    if (m_mode == HixLedMode::fadeInOut) return;
    m_mode = HixLedMode::fadeInOut;
    m_nFadeCounter = 0;
    m_bFadeDirection = true;
    m_ticker.detach();
    m_ticker.attach_ms(m_delayFadeInOutMs / m_nFadeSteps, std::bind(&HixLED::tickerISR, this));
}

void HixLED::tickerISR(void) {
    switch (m_mode) {
        case HixLedMode::slowBlink:
            HixPinDigitalOutput::toggle();
            break;
        case HixLedMode::blink:
            HixPinDigitalOutput::toggle();
            break;
        case HixLedMode::fastBlink:
            HixPinDigitalOutput::toggle();
            break;
        case HixLedMode::fadeInOut:
            //count up or down
            if (m_bFadeDirection)
                m_nFadeCounter++;
            else
                m_nFadeCounter--;
            //reverse direction if we hit a bounds
            if (m_nFadeCounter > m_nFadeSteps) m_bFadeDirection = false;
            if (m_nFadeCounter == 0) m_bFadeDirection = true;
            //update the led
            ::analogWrite(m_nPinNumber, m_nPWMStep * m_nFadeCounter);
            break;
        default:
            break;
    }
}