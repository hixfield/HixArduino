#include <Arduino.h>
#include "HixPin.h"

HixPin::HixPin(int nPinNumber): m_nPinNumber(nPinNumber) {
}

int HixPin::getPinNumber() {
  return m_nPinNumber;
}
