#include <Arduino.h>
#include "HixPinAnalogInput.h"

HixPinAnalogInput::HixPinAnalogInput(int nPinNumber): HixPin(nPinNumber) {
}

bool HixPinAnalogInput::begin() {
  //return non error
  return true;
}

int HixPinAnalogInput::analogRead() {
	return ::analogRead(m_nPinNumber);
}