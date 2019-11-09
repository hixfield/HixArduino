#include <Arduino.h>
#include "HixPinDigital.h"

HixPinDigital::HixPinDigital(int nPinNumber): HixPin(nPinNumber) {
}

bool HixPinDigital::digitalRead(void) {
  return ::digitalRead(m_nPinNumber);
}

bool HixPinDigital::isHigh(void) {
  return digitalRead();
}

bool HixPinDigital::isLow(void) {
  return !digitalRead();
}
