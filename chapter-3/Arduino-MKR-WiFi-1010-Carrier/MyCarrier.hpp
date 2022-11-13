#pragma once

#include <Arduino.h>
#include <Arduino_MKRIoTCarrier.h>

namespace MyCarrier {
  class MyCarrier {
    public:
      void initialize(MKRIoTCarrier* carrier);
      float getTemperature();
      float getPressure();
      float getHumidity();
      void displaySensors(String time);
  };
}