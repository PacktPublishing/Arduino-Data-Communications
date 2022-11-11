#pragma once

#include <Arduino.h>
#include <Arduino_JSON.h>

namespace MyEnv {
  bool initialize();
  float getTemp();
  float getHumid();
  float getPressure();
  float getLux();
  JSONVar getJSONReadings(unsigned long unixTime);
  String getReadings(unsigned long unixTime); 
}