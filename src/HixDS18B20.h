#ifndef HixDS18B20_h
#define HixDS18B20_h

#include <DallasTemperature.h>
#include <OneWireNg_CurrentPlatform.h>
#include <Print.h>
#include "HixPin.h"

class HixDS18B20: public HixPin {

    static constexpr float INVALID_TEMP  = -127.0f;

    OneWireNg_CurrentPlatform * m_pOneWire;
    OneWireNg::Id               m_sensorId;


  public:

    //lifecycle
    HixDS18B20(int nPinNumber);
    bool begin(void);
    ~HixDS18B20();

    //public api
    float getTemp(void);
    void printId(Print &os);
};


#endif
