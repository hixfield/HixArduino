#include <Arduino.h>
#include "HixPinDigitalInput.h"

HixPinDigitalInput::HixPinDigitalInput(int nPinNumber): HixPinDigital(nPinNumber) {
}

void HixPinDigitalInput::begin() {
  pinMode(m_nPinNumber, INPUT);
}

void HixPinDigitalInput::attachInterrupt(void (isr)(void), int mode) {
::attachInterrupt(digitalPinToInterrupt(m_nPinNumber),isr, mode); 
}
