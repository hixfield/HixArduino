#include "HixDS18B20.h"

/* DS therms commands */
#define CONVERT_T           0x44
#define COPY_SCRATCHPAD     0x48
#define WRITE_SCRATCHPAD    0x4e
#define RECALL_EEPROM       0xb8
#define READ_POW_SUPPLY     0xb4
#define READ_SCRATCHPAD     0xbe


HixDS18B20::HixDS18B20(int nPinNumber): HixPin(nPinNumber) {
}

bool HixDS18B20::begin(void) {
  m_pOneWire = new OneWireNg_CurrentPlatform(m_nPinNumber, false);
  //small delay, because otherwise the search would not work reliably...
  delay(500);
  //search our device
  OneWireNg::ErrorCode ec;
  m_pOneWire->searchReset();
  ec = m_pOneWire->search(m_sensorId);
  return ec == OneWireNg::EC_SUCCESS;
}

HixDS18B20::~HixDS18B20() {
  if (m_pOneWire) delete m_pOneWire;
}

float HixDS18B20::getTemp(void) {
  //start temperature conversion
  m_pOneWire->addressSingle(m_sensorId);
  m_pOneWire->writeByte(CONVERT_T);
  delay(750);
  //read scratchpad
  uint8_t touchScrpd[] = {
    READ_SCRATCHPAD,
    /* the read scratchpad will be placed here (9 bytes) */
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  };
  m_pOneWire->addressSingle(m_sensorId);
  m_pOneWire->touchBytes(touchScrpd, sizeof(touchScrpd));
  //pointer to the scratchpad data
  uint8_t *scrpd = &touchScrpd[1];
  //if invalid crc return error
  if (OneWireNg::crc8(scrpd, 8) != scrpd[8]) {
    return INVALID_TEMP;
  }
  //extract temperatur
  long temp = ((long)(int8_t)scrpd[1] << 8) | scrpd[0];
  unsigned res = (scrpd[4] >> 5) & 3;
  temp = (temp >> (3 - res)) << (3 - res); /* zeroed undefined bits */
  temp = (temp * 1000) / 16;
  return (float)temp / (float)1000;
}

void HixDS18B20::printId(Print &os)
{
  for (size_t i = 0; i < sizeof(OneWireNg::Id); i++) {
    if (i != 0) {
      os.print(':');
    }
    os.print(m_sensorId[i], HEX);
  }
}
