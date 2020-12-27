#include "HixMQTTBase.h"
#include <Arduino.h>

HixMQTTBase::HixMQTTBase(const char* szWifi_SSID,
                         const char* szWiFi_Password,
                         const char* szMQTT_Server,
                         const char* szDeviceType,
                         const char* szDeviceVersion,
                         const char* szRoom,
                         const char* szDeviceTag) : EspMQTTClient(szWifi_SSID, szWiFi_Password, szMQTT_Server, createClientName(szRoom, szDeviceType, szDeviceTag)),
                                                    m_deviceType(szDeviceType),
                                                    m_deviceVersion(szDeviceVersion),
                                                    m_room(szRoom),
                                                    m_deviceTag(szDeviceTag) {
}

char* HixMQTTBase::createClientName(const char* szRoom, const char* szDeviceType, const char* szDeviceTag) {
    sprintf(m_szClientName, "%s_%s_%s", szRoom, szDeviceType, szDeviceTag);
    return m_szClientName;
}

bool HixMQTTBase::begin() {
    enableDebuggingMessages();  // Enable debugging messages sent to serial output
    //return non error
    return true;
}

String HixMQTTBase::topicForPath(const char* path) {
    return String(m_room + String("/") + String(m_deviceType) + String("/") + String(m_deviceTag) + String("/") + String(path));
}

bool HixMQTTBase::publishDeviceValues(void) {
    if (isConnected()) {
        //static values are published with retain!
        publish(topicForPath("device/count"), m_nPublishCountDevice, true);
        publish(topicForPath("device/room"), m_room, true);
        publish(topicForPath("device/device_type"), m_deviceType, true);
        publish(topicForPath("device/device_version"), m_deviceVersion, true);
        publish(topicForPath("device/device_tag"), m_deviceTag, true);
        publish(topicForPath("device/device_name"), getMqttClientName(), true);
        publish(topicForPath("device/wifi_mac"), WiFi.macAddress(), true);
        publish(topicForPath("device/wifi_ssid"), WiFi.SSID(), true);
        publish(topicForPath("device/wifi_ip"), WiFi.localIP().toString(), true);
        //increment our publish ounter
        m_nPublishCountDevice++;
        //return non error
        return true;
    }
    //not connected, return error
    return false;
}

bool HixMQTTBase::publishStatusValues(void) {
    if (isConnected()) {
        //static values are published with retain!
        publish(topicForPath("status/count"), m_nPublishCountStatus, false);
        publish(topicForPath("status/wifi_rssi"), WiFi.RSSI(), false);
        //increment our publish ounter
        m_nPublishCountStatus++;
        //return non error
        return true;
    }
    //not connected, return error
    return false;
}