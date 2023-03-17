#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <MKRWAN.h>
#include "arduino_secrets.h"

unsigned long lastRead = millis();
const int myDelay = 60000;
float t,h;
const int stationId = 1;

LoRaModem modem;

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

void setup() {
  
  Serial.begin(115200);
  while (!ENV.begin()) {
    Serial.println("Failed to initialize ENV Shield, waiting ...");
    delay(10000);
  }
  Serial.println("Initialized ENV Shield");
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Unable to initialize modem connection");
    while (true);
  }
  // Set poll interval to 60 secs.
  modem.minPollInterval(60);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - lastRead > myDelay) {
    lastRead = millis();
    t = ENV.readTemperature();
    h = ENV.readHumidity();
    String msg = String(String(stationId) + "|" + String(t) + "|" + String(h));
    Serial.println(msg);
    for (unsigned int i=0; i<msg.length(); i++) {
      Serial.print(msg[i] >> 4, HEX);
      Serial.print(msg[i] & 0xF, HEX);
      Serial.print(" ");
    }
    Serial.println();

    int err;
    modem.beginPacket();
    modem.print(msg);
    err = modem.endPacket(true);
    if (err > 0) {
      Serial.println("msg sent");
    } else {
      Serial.println("Error while sending msg");
    }
  }
}

