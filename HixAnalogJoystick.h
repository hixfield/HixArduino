#ifndef HixAnalogJoystick_h
#define HixAnalogJoystick_h

class HixAnalogJoystick {

  private:

  const int m_nPinX; //used for reading the analogue value for X
  int m_nMinX;       //min possible value (put stick all the way left)
  int m_nMaxX;       //max possible value (put stick all the way right)
  int m_nRestX;      //value when stick is at rest


  public:
  //connects the X to the specified pin, and calibrates for min, max and rest values
  HixAnalogJoystick(int nPinX, int nMinX, int nMaxX, int nRestX);
  //returns the current X ranging from specified min to max
  int getX(int nMin, int nMax);
  //returns X position in percent 0 = left and 100 = right (50 is middle/rest)
  int getXPercent(void);
  
};

#endif
