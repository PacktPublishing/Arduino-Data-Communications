#pragma once

#include <Arduino.h>
#include <Arduino_JSON.h>

namespace MyWireless {
  int initialize();
  int getStatus();
  int getIdleStatus();
  int getConnectedStatus();
  IPAddress getLocalIp();
  String getSSID();
  String get_ssid();
  long getRSSI();
  bool isOnLatestFirmware();

  void postReadings(JSONVar readings);
}