#include "MyWireless.hpp"

#include "arduino_secrets.h"
#include <WiFiNINA.h>

namespace MyWireless {
  char ssid[] = SECRET_SSID; 
  char pass[] = SECRET_PASS;
  int status = WL_IDLE_STATUS;     // the Wifi radio's status

  int initialize() {
    return WiFi.begin(ssid, pass);
  }

  int getStatus() {
    return WiFi.status();
  }

  int getIdleStatus() {
    return WL_IDLE_STATUS;
  }

  int getConnectedStatus() {
    return WL_CONNECTED;
  }

  IPAddress getLocalIp() {
    return WiFi.localIP();
  }

  String getSSID() {
    return WiFi.SSID();
  }

  long getRSSI() {
    return WiFi.RSSI();
  }

  String get_ssid() {
    return ssid;
  }

  bool isOnLatestFirmware() {
    return WiFi.firmwareVersion() == WIFI_FIRMWARE_LATEST_VERSION;
  }
}