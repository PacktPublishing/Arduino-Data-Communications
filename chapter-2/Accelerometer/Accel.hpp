#pragma once

#include <Arduino.h>

namespace Accel {
  void initialize();
  bool lisAvailable();
  float getAccelerationX();
  float getAccelerationY();
  float getAccelerationZ();
}