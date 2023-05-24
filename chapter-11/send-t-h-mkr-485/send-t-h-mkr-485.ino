#include <Arduino_MKRENV.h>
#include <ArduinoRS485.h>

unsigned long lastRead = millis();
const int myDelay = 60000;
float t,h;
const int stationId = 1;

void setup() {
  Serial.begin(9600);
  while (!ENV.begin()) {
    Serial.println("Failed to initialize ENV Shield, waiting ...");
    delay(10000);
  }
  Serial.println("Initialized ENV Shield");
  RS485.begin(9600);
  Serial.println("Ready ...");
}

void loop() {
  if (millis() - lastRead > myDelay) {
    lastRead = millis();
    t = ENV.readTemperature();
    h = ENV.readHumidity();
    String msg = String(String(stationId) + "|" + String(t) + "|" + String(h));

    RS485.beginTransmission();
    RS485.println(msg);
    RS485.endTransmission();
    
    Serial.println(msg);
  }
}
