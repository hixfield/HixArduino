#ifndef HixMQTTBase_h
#define HixMQTTBase_h
#define MQTT_MAX_PACKET_SIZE 512
#include <EspMQTTClient.h>

class HixMQTTBase : public EspMQTTClient {
   protected:
    //type of this ensor
    const String m_deviceType;
    //version of this sensor
    const String m_deviceVersion;
    //in which room this sensor is mounted
    const String m_room;
    //If multiple devices of same type are used in same room, this is used to differentiate between them
    const String m_deviceTag;
    //timestamp of this build (firmware)
    const String m_deviceBuildTimestamp;
    //my constructed client name
    char m_szClientName[255];
    char *createClientName(const char *szRoom, const char *szDeviceType, const char *szDeviceTag);
    //counters for the sections
    unsigned int m_nPublishCountDevice = 0;
    unsigned int m_nPublishCountStatus = 0;

   public:
    HixMQTTBase(const char *szWifi_SSID,
                const char *szWiFi_Password,
                const char *szMQTT_Server,
                const char *szDeviceType,
                const char *szDeviceVersion,
                const char *szRoom,
                const char *szDeviceTag,
                const char * szDeviceBuildTimestamp);
    //returns fals if init fails
    bool begin();
    //this creates a absolute path in the format of MyName/path" (do not start the path with a /!)
    String topicForPath(const char *path);
    //published the device values e.g room, type...
    bool publishDeviceValues(void);
    //published status value; base implementation pushed and increements the count
    bool publishStatusValues(void);
};

#endif
