#include <Arduino.h>
#include "HixPinDigitalInput.h"

HixPinDigitalInput::HixPinDigitalInput(int nPinNumber): HixPinDigital(nPinNumber) {
}

bool HixPinDigitalInput::begin(uint8_t mode = INPUT) {
  pinMode(m_nPinNumber, mode);
  //return non error
  return true;
}

void HixPinDigitalInput::attachInterrupt(void (isr)(void), int mode) {
::attachInterrupt(digitalPinToInterrupt(m_nPinNumber),isr, mode); 
}
