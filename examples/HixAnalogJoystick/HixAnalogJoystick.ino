/*
   HixAnalogJoystick
   By Geert Michiels
   (C) HixField.com
*/


#include "HixAnalogJoystick.h"



//joystick
HixAnalogJoystick joystick(A0, A1);


void setup()
{
  Serial.begin(19200);
  Serial.print(F("Startup HixAnalogJoystick"));
  joystick.calibrateRest();
  Serial.print(F("Move the joystick to all extreme edges"));
  joystick.calibrate(5);
  Serial.print(F("Calibration complete "));
}

void loop(void) {
  //first value is the current X in percent
  Serial.print(joystick.getXPercent());
  Serial.print(", ");
  Serial.print(joystick.getXRaw());
  Serial.print(", ");
  Serial.print(joystick.getYPercent());
  Serial.print(", ");
  Serial.print(joystick.getYRaw());
  //then we print 0 and 1024 (max raw value) so the scale remains constant in the serial plotter
  Serial.println(", 0, 1024");
}
