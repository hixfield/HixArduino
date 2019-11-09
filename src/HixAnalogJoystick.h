#ifndef HixAnalogJoystick_h
#define HixAnalogJoystick_h


#include "HixPinAnalogInput.h"

class HixAnalogJoystick {

  private:

    HixPinAnalogInput m_cAnalogInputX; //used for reading the analogue value for X
    int m_nMinX;                       //min possible value (put stick all the way left)
    int m_nMaxX;                       //max possible value (put stick all the way right)
    int m_nRestX;                      //value when stick is at rest

    HixPinAnalogInput m_cAnalogInputY;  //used for reading the analogue value for Y
    int m_nMinY;                        //min possible value (put stick all the way up)
    int m_nMaxY;                        //max possible value (put stick all the way down)
    int m_nRestY;                       //value when stick is at rest

  public:
    
    //connects the X to the specified pin, and calibrates for min, max and rest values
    HixAnalogJoystick(int nPinX,
                      int nPinY,
                      int nMinX = 0, int nMaxX = 1024, int nRestX = 512,
                      int nMinY = 0, int nMaxY = 1024, int nRestY = 512
                     );
    //returns the raw value
    int getXRaw(void);
    int getYRaw(void);
    //returns the current X ranging from specified min to max
    int getX(int nOutputMin, int nOutputMax);
    int getY(int nOutputMin, int nOutputMax);
    //returns X position in percent 0 = left and 100 = right (50 is middle/rest)
    int getXPercent(void);
    int getYPercent(void);
    //calibrates current position as the rest position
    void calibrateRest(void);
    //calibrate the max and min values for X and Y, move the stick extreme left, right, up and down (takes the min and max)
    void calibrate(int nDurationSeconds = 5);
  private:
    //translates value to new range taken into account the min max and rest positions
    int get(int nValue, int nJoystickMin, int nJoystickMax,  int nJoystickRest, int nOutputMin, int nOutputMax);

};


#endif
