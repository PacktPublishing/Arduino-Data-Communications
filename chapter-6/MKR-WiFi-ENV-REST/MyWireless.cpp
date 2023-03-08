#include "MyWireless.hpp"

#include "arduino_secrets.h"
#include <WiFiNINA.h>

namespace MyWireless {
  char ssid[] = SECRET_SSID; 
  char pass[] = SECRET_PASS;
  int status = WL_IDLE_STATUS;     // the Wifi radio's status
  const int stationId = 1;
  IPAddress server(192,168,68,120);
  uint16_t port = 3000;
  WiFiClient client;

  int initialize() {
    return WiFi.begin(ssid, pass);
  }

  int getStatus() {
    return WiFi.status();
  }

  int getIdleStatus() {
    return WL_IDLE_STATUS;
  }

  int getConnectedStatus() {
    return WL_CONNECTED;
  }

  IPAddress getLocalIp() {
    return WiFi.localIP();
  }

  String getSSID() {
    return WiFi.SSID();
  }

  long getRSSI() {
    return WiFi.RSSI();
  }

  String get_ssid() {
    return ssid;
  }

  bool isOnLatestFirmware() {
    return WiFi.firmwareVersion() == WIFI_FIRMWARE_LATEST_VERSION;
  }

  void postReadings(JSONVar readings) {
    JSONVar payload;
    payload["stationid"] = stationId;
    payload["epochs"] = readings["unixTime"];
    payload["temperature"] = readings["temperature"];
    payload["humidity"] = readings["humidity"];

    String p = JSON.stringify(payload);

    client.stop();

    if (client.connect(server, port)) {
      client.println("POST /readings HTTP/1.1");
      client.println("Content-Type: application/json");
      client.print("Content-Length: ");
      client.println(p.length());
      client.println();
      client.println(p);
      client.println("Connection: close");
      client.println();      
    }
  }
}