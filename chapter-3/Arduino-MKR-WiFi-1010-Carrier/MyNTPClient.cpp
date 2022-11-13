#include "MyNTPClient.hpp"

#include <WiFiUdp.h>
#include "UnixTime.h"

namespace MyNTPClient {
  unsigned int localPort = 2390; //local port for UDP packets
  IPAddress timeServer(129, 6, 15, 28); //time.nist.gov NTP server
  const int NTP_PACKET_SIZE = 48;
  byte packetBuffer[NTP_PACKET_SIZE];

  WiFiUDP myUDP;

  void initialize() {
    myUDP.begin(localPort);
  }

  unsigned long getUnixTime() {
    sendNTPpacket(timeServer);
    delay(1000);

    if (myUDP.parsePacket()) {
      myUDP.read(packetBuffer, NTP_PACKET_SIZE);
      // timestamp starts at byte 40. four bytes long
      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]); 

      unsigned long ntpTime = highWord << 16 | lowWord;
      const unsigned long seventyYearsInSecs = 2208988800UL;

      unsigned long unixTime = ntpTime - seventyYearsInSecs;
      return unixTime;     
    }
    return 0;
  }

  String getTimeFromUnix(unsigned long unixTime) {
    UnixTime t(1);
    t.getDateTime(unixTime);
    String dt = String(t.day);
    dt.concat("-");
    dt.concat(t.month);
    dt.concat("-");
    dt.concat(t.year);
    dt.concat(" ");
    dt.concat(t.hour);
    dt.concat(":");
    dt.concat(t.minute);
    dt.concat(":");
    dt.concat(t.second);
    return dt;    
  }

  unsigned long sendNTPpacket(IPAddress& addy) {
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    packetBuffer[0] = 0b11100011; //LI, Version, Mode
    packetBuffer[1] = 0; //type of clock
    packetBuffer[2] = 6; //polling interval
    packetBuffer[3] = 0xEC; //peer clock precision
    // 8bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;

    myUDP.beginPacket(addy, 123); //send a packet requesting a timestamp
    myUDP.write(packetBuffer, NTP_PACKET_SIZE);
    myUDP.endPacket();
  }
}

