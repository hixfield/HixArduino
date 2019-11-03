#include "HixAnalogJoystick.h"
#include <arduino.h>

HixAnalogJoystick::HixAnalogJoystick(int nPinX,
                                     int nPinY,
                                     int nMinX, int nMaxX, int nRestX,
                                     int nMinY, int nMaxY, int nRestY
                                    ): m_nPinX(nPinX), m_nPinY(nPinY) {
  //set X values
  m_nMinX = nMinX;
  m_nMaxX = nMaxX;
  m_nRestX = nRestX;
  //set Y values
  m_nMinY = nMinY;
  m_nMaxY = nMaxY;
  m_nRestY = nRestY;
  //make sure reference is default meaning 0...5v
  analogReference(DEFAULT);
}

int HixAnalogJoystick::getXRaw(void) {
  return analogRead(m_nPinX);
}

int HixAnalogJoystick::getYRaw(void) {
  return analogRead(m_nPinY);
}

int HixAnalogJoystick::getX(int nOutputMin, int nOutputMax) {
  return get(getXRaw(), m_nMinX, m_nMaxX, m_nRestX, nOutputMin, nOutputMax);
}

int HixAnalogJoystick::getY(int nOutputMin, int nOutputMax) {
  return get(getYRaw(), m_nMinY, m_nMaxY, m_nRestY, nOutputMin, nOutputMax);
}

int HixAnalogJoystick::get(int nValue, int nJoystickMin, int nJoystickMax,  int nJoystickRest, int nOutputMin, int nOutputMax) {
  const int nOffset = nValue - nJoystickRest;
  const int nHalfRangeOutput = (nOutputMax - nOutputMin) / 2;

  if (nOffset > 0) {
    const int nHalfRangeJoystick = nJoystickMax - nJoystickRest;
    return map(nOffset, 0, nHalfRangeJoystick, 0, nHalfRangeOutput) + nHalfRangeOutput;
  }
  else {
    const int nHalfRangeJoystick = m_nRestX - m_nMinX;
    return nHalfRangeOutput - map(-nOffset, 0, nHalfRangeJoystick, 0, nHalfRangeOutput);
  }
}

void HixAnalogJoystick::calibrateRest(void) {
  m_nRestX = getXRaw();
  m_nRestY = getYRaw();
}

void HixAnalogJoystick::calibrate(int nDurationSeconds = 5) {
  //reset to extreme values so they will certainly be overwritten
  m_nMinX = 1024;
  m_nMaxX = 0;
  m_nMinY = 1024;
  m_nMaxY = 0;
  
  for (int i = 0; i< (nDurationSeconds * 1000); i++) {
    
    int x = getXRaw();
    if ( x < m_nMinX) m_nMinX = x;
    if ( x > m_nMaxX) m_nMaxX = x;
    
    int y = getYRaw();    
    if ( y < m_nMinY) m_nMinY = y;
    if ( y > m_nMaxY) m_nMaxY = y;
    
    delay(1);
  }
}

int HixAnalogJoystick::getXPercent(void) {
  return getX(0, 100);
}

int HixAnalogJoystick::getYPercent(void) {
  return getY(0, 100);
}
