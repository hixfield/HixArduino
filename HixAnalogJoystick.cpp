#include "HixAnalogJoystick.h"
#include <arduino.h>

HixAnalogJoystick::HixAnalogJoystick(int nPinX, int nMinX, int nMaxX, int nRestX): m_nPinX(nPinX) {
  m_nMinX = nMinX;
  m_nMaxX = nMaxX;
  m_nRestX = nRestX;
  analogReference(DEFAULT);
}

int HixAnalogJoystick::getX(int nMin, int nMax) {
  const int value = analogRead(m_nPinX);
  const int offset = value - m_nRestX;
  const int halfRangeOutput = (nMax - nMin)/2;

  if (offset > 0) {
    const int halfRangeJoystick = m_nMaxX - m_nRestX;
    return map(offset, 0, halfRangeJoystick, 0, halfRangeOutput) + halfRangeOutput;
  }
  else {
    const int halfRangeJoystick = m_nRestX - m_nMinX;
    return halfRangeOutput - map(-offset, 0, halfRangeJoystick, 0, halfRangeOutput);
  }
}

int HixAnalogJoystick::getXPercent(void) {
  return getX(0, 100);
}
