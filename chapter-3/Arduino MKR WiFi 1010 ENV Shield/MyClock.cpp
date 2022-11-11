#include "MyClock.hpp"

#include <RTCZero.h>
#include <UnixTime.h>


namespace MyClock {
  RTCZero rtc;
  

  bool MyClock::initialize(unsigned long unixTime) {
    rtc.begin();
    UnixTime t(1);
    t.getDateTime(unixTime);
    uint8_t y = t.year - 2000;
    rtc.setDate(t.day, t.month, y);
    rtc.setTime(t.hour, t.minute, t.second);
    return true;
  }

  unsigned long MyClock::getEpochs() {
    UnixTime t(1);
    t.setDateTime(rtc.getYear()+2000, rtc.getMonth(), rtc.getDay(), rtc.getHours(), rtc.getMinutes(), rtc.getSeconds());
    return t.getUnix();
  }

  String MyClock::getDate() {
    String t = zeroPad(rtc.getDay());
    t.concat("-");
    t.concat(zeroPad(rtc.getMonth()));
    t.concat("-");
    t.concat(String(rtc.getYear()));
    return t;
  }

  String MyClock::getWATTime() {
    String t = zeroPad(rtc.getHours());
    t.concat(":");
    t.concat(zeroPad(rtc.getMinutes()));
    t.concat(":");
    t.concat(zeroPad(rtc.getSeconds()));
    return t;
  }

  String MyClock::getWATDateTime() {
    String t = zeroPad(rtc.getDay());
    t.concat("-");
    t.concat(zeroPad(rtc.getMonth()));
    t.concat("-");
    t.concat(String(rtc.getYear()));
    t.concat(" ");
    t.concat(zeroPad(rtc.getHours()));
    t.concat(":");
    t.concat(zeroPad(rtc.getMinutes()));
    t.concat(":");
    t.concat(zeroPad(rtc.getSeconds()));
    return t;
  }

  String zeroPad(int n) {
    if (n > 9) {
      return String(n);
    }
    String s = String(0);
    s.concat(n);
    return s;
  }
}