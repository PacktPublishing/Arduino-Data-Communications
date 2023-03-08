#pragma once

#include <Arduino.h>
#include <Arduino_JSON.h>

namespace MyEnv {
  bool initialize();
  float getTemp();
  float getHumid();
  JSONVar getJSONReadings(unsigned long unixTime);
  String getCSVReadings(unsigned long unixTime); 
  String getTSVReadings(unsigned long unixTime);
  void writeTSVToFile(String y, String m, String d, unsigned long unixtime);
}