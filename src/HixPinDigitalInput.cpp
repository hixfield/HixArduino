#include <Arduino.h>
#include "HixPinDigitalInput.h"

HixPinDigitalInput::HixPinDigitalInput(int nPinNumber): HixPinDigital(nPinNumber) {
}

bool HixPinDigitalInput::begin() {
  return begin(INPUT);
}


bool HixPinDigitalInput::begin(int mode) {
  pinMode(m_nPinNumber, mode);
  //return non error
  return true;
}

void HixPinDigitalInput::attachInterrupt(void (isr)(void), int mode) {
::attachInterrupt(digitalPinToInterrupt(m_nPinNumber),isr, mode); 
}
