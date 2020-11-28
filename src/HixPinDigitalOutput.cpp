#include <Arduino.h>
#include "HixPinDigitalOutput.h"

HixPinDigitalOutput::HixPinDigitalOutput(int nPinNumber): HixPinDigital(nPinNumber) {
}

bool HixPinDigitalOutput::begin(uint8_t mode = OUTPUT)) {
  pinMode(m_nPinNumber, mode);
  //return non error
  return true;
}

void HixPinDigitalOutput::high(void) {
  digitalWrite(true);
}

void HixPinDigitalOutput::low(void) {
  digitalWrite(false);
}

void HixPinDigitalOutput::digitalWrite(bool bValue) {
  ::digitalWrite(m_nPinNumber, bValue);
}

void HixPinDigitalOutput::toggle(void) {
  bool currentValue = digitalRead();
  digitalWrite(!currentValue);
}

void HixPinDigitalOutput::blink(bool bOn, int nNumberOfBlinks, int nDelayMs) {
  blink(bOn, nNumberOfBlinks, nDelayMs, nDelayMs);
}

void HixPinDigitalOutput::blink(bool bOn, int nNumberOfBlinks, int nDelayOnMs, int nDelayOffMs) {
  //save state
  bool bLastState = digitalRead();
  //do blinking
  for (int i = 0; i < nNumberOfBlinks; i++) {
    //led on
    digitalWrite(bOn);
    delay(nDelayOnMs);
    //led off
    digitalWrite(!bOn);
    delay(nDelayOffMs);
  }
  //restore state
  digitalWrite(bLastState);
}
