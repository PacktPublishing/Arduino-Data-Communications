#include "MyEnv.hpp"

#include "MyNTPClient.hpp"
#include <Arduino_MKRENV.h>

namespace MyEnv {
  bool initialize() {
    return ENV.begin();
  }

  float getTemp() {
    return ENV.readTemperature();
  }

  float getHumid() {
    return ENV.readHumidity();
  }

  float getPressure() {
    return ENV.readPressure();
  }

  float getLux() {
    return ENV.readIlluminance();
  }

  JSONVar getJSONReadings(unsigned long unixTime) {
    JSONVar readings;
    readings["unixTime"] = unixTime;
    readings["temperature"] = getTemp();
    readings["humidity"] = getHumid();
    readings["pressure"] = getPressure();
    readings["illuminance"] = getLux();
    return readings;
  }

  String getReadings(unsigned long unixTime) {
    JSONVar readings = getJSONReadings(unixTime);
    return JSON.stringify(readings);
  }
}