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

  JSONVar getJSONReadings() {
    JSONVar readings;
    readings["temperature"] = getTemp();
    readings["humidity"] = getHumid();
    readings["pressure"] = getPressure();
    readings["illuminance"] = getLux();
    return readings;
  }

  String getReadings() {
    JSONVar readings = getJSONReadings();
    return JSON.stringify(readings);
  }
}