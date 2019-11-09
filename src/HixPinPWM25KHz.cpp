#include <Arduino.h>
#include "HixPinPWM25KHz.h"

HixPinPWM25KHz::HixPinPWM25KHz(int nPinNumber): HixPin(nPinNumber) {
}

bool HixPinPWM25KHz::begin() {
  //25KHz PWM only supported on ping 9 and 10
  if ( (m_nPinNumber != 9) && (m_nPinNumber != 10) ) {
    return false;
  }
  // Configure Timer 1 for PWM @ 25 kHz.
  TCCR1A = 0;           // undo the configuration done by...
  TCCR1B = 0;           // ...the Arduino core library
  TCNT1  = 0;           // reset timer
  TCCR1A = _BV(COM1A1)  // non-inverted PWM on ch. A
           | _BV(COM1B1)  // same on ch; B
           | _BV(WGM11);  // mode 10: ph. correct PWM, TOP = ICR1
  TCCR1B = _BV(WGM13)   // ditto
           | _BV(CS10);   // prescaler = 1
  ICR1   = 320;         // TOP = 320
  pinMode(m_nPinNumber, OUTPUT);
  analogWritePercent(50);
  //return non error condition
  return true;
}

void HixPinPWM25KHz::analogWritePercent(float fPercent) {
  if (fPercent > 100) {
    fPercent = 100;
  }
  if (fPercent < 0)   {
    fPercent = 0;
  }

  int value = (int) ( (fPercent * 320.0f) / 100.0f );
  switch (m_nPinNumber) {
    case 9:
      OCR1A = value;
      break;
    case 10:
      OCR1B = value;
      break;
    default:
      // no other pin will work
      break;
  }
}

float HixPinPWM25KHz::getPercent(void) {
  int value = 0;
  switch (m_nPinNumber) {
    case 9:
      value = OCR1A;
      break;
    case 10:
      value = OCR1B;
      break;
    default:
      // no other pin will work
      break;
  }
  return (float(value) * 100.0f) / 320.0f;
}
