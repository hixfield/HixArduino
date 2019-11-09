#include <Arduino.h>
#include "HixPinDigitalInput.h"

HixPinDigitalInput::HixPinDigitalInput(int nPinNumber): HixPinDigital(nPinNumber) {
}

bool HixPinDigitalInput::begin() {
  pinMode(m_nPinNumber, INPUT);
  //return non error
  return true;
}

void HixPinDigitalInput::attachInterrupt(void (isr)(void), int mode) {
::attachInterrupt(digitalPinToInterrupt(m_nPinNumber),isr, mode); 
}
