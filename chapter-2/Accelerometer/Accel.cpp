#include "Accel.hpp"
#include "LIS3DHTR.h"
#include <Wire.h>


namespace Accel {
  LIS3DHTR<TwoWire> LIS; //IIC
  #define WIRE Wire

  void initialize() {
    LIS.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); //IIC init
    delay(100);
    LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  }

  bool lisAvailable() {
    if (!LIS) {
      return false;
    }
    return true;
  }

  float getAccelerationX() {
    return LIS.getAccelerationX();
  }

  float getAccelerationY() {
    return LIS.getAccelerationY();
  }

  float getAccelerationZ() {
    return LIS.getAccelerationZ();
  }
}