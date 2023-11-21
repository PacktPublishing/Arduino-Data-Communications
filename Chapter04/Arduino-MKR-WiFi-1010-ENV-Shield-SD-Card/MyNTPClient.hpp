#pragma once

#include <Arduino.h>

namespace MyNTPClient {
  void initialize();
  unsigned long getUnixTime();
  unsigned long sendNTPpacket(IPAddress& address);
  String getTimeFromUnix(unsigned long unixTime);
}