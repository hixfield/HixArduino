#include <Arduino.h>
#include "HixPinPWM.h"

HixPinPWM::HixPinPWM(int nPinNumber): HixPin(nPinNumber) {
}

bool HixPinPWM::begin() {
  pinMode(m_nPinNumber, OUTPUT);
  m_nCurrentValue = 50;
  analogWritePercent(m_nCurrentValue);
  //return non error condition
  return true;
}

void HixPinPWM::analogWriteRaw(int nValue) {
  m_nCurrentValue = nValue;
  ::analogWrite(m_nPinNumber, m_nCurrentValue);
}

void HixPinPWM::analogWritePercent(float fPercent) {
  if (fPercent > 100) {
    fPercent = 100;
  }
  if (fPercent < 0)   {
    fPercent = 0;
  }
  analogWriteRaw( (int) (fPercent * 255.0f / 100.0f) );
}

int HixPinPWM::getRaw(void) {
 return m_nCurrentValue;
}

float HixPinPWM::getPercent(void) {
 return (float(getRaw()) * 100.0f) / 255.0f;
}