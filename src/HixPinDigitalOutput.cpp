#include <Arduino.h>
#include "HixPinDigitalOutput.h"

HixPinDigitalOutput::HixPinDigitalOutput(int nPinNumber): HixPinDigital(nPinNumber) {
}

bool HixPinDigitalOutput::begin() {
  pinMode(m_nPinNumber, OUTPUT);
  //return non error
  return true;
}

void HixPinDigitalOutput::high(void) {
  digitalWrite(true);
}

void HixPinDigitalOutput::low(void) {
  digitalWrite(false);
}

void HixPinDigitalOutput::digitalWrite(bool value) {
  ::digitalWrite(m_nPinNumber, value);
}

void HixPinDigitalOutput::toggle(void) {
  bool currentValue = digitalRead();
  digitalWrite(!currentValue);
}

void HixPinDigitalOutput::blink(bool bOn, int nNumberOfBlinks, int nDelayMs) {
  blink(bOn, nNumberOfBlinks, nDelayMs, nDelayMs);
}

void HixPinDigitalOutput::blink(bool bOn, int nNumberOfBlinks, int nDelayOnMs, int nDelayOffMs) {
  for (int i = 0; i < nNumberOfBlinks; i++) {
    //led on
    digitalWrite(bOn);
    delay(nDelayOnMs);
    //led off
    digitalWrite(!bOn);
    delay(nDelayOffMs);
  }
}
