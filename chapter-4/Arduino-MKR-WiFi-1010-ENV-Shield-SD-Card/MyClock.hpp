#pragma once

#include <Arduino.h>

namespace MyClock {
  class MyClock{
    public:
      bool initialize(unsigned long unixTime);
      unsigned long getEpochs();
      String getYear();
      String getMonth();
      String getDay();
      String getDate();
      String getWATTime();
      String getWATDateTime();
  };
  String zeroPad(int n);
}