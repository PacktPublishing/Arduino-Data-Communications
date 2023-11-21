#include "MyEnv.hpp"

#include "MyNTPClient.hpp"
#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <SD.h>

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

  JSONVar getJSONReadings(unsigned long unixTime) {
    JSONVar readings;
    readings["unixTime"] = unixTime;
    readings["temperature"] = getTemp();
    readings["humidity"] = getHumid();
    return readings;
  }

  String getCSVReadings(unsigned long unixTime) {
    String readings = String(unixTime);
    readings.concat(", ");
    readings.concat(getTemp());
    readings.concat(", ");
    readings.concat(getHumid());
    return readings;
  }

  String getTSVReadings(unsigned long unixTime) {
    String readings = String(unixTime);
    readings.concat("\t");
    readings.concat(getTemp());
    readings.concat("\t");
    readings.concat(getHumid());
    return readings;
  }

  void writeTSVToFile(String y, String m, String d, unsigned long unixtime) {
    SD.begin(4);
    String f = String("/");
    f.concat(y);
    f.concat("/");
    f.concat(m);
    if(!SD.exists(f)) {
      SD.mkdir(f);
    }
    f.concat("/");
    f.concat(d);
    f.concat(".tsv");
    
    File myFile = SD.open(f, FILE_WRITE);
    if(myFile) {
      myFile.println(getTSVReadings(unixtime));
      myFile.close();
    }
  }
}