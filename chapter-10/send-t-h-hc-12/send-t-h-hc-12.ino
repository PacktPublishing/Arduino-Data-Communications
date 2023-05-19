#include <SoftwareSerial.h>
#include <Arduino_MKRENV.h>
SoftwareSerial HC12(10, 11); //TX, RX

unsigned long lastRead = millis();
const int myDelay = 60000;
float t,h;
const int stationId = 1;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);

  while (!ENV.begin()) {
    Serial.println("Failed to initialize ENV Shield, waiting ...");
    delay(10000);
  }
  Serial.println("Initialized ENV Shield");
  Serial.println("Ready ...");
}

void loop() {
  while(HC12.available()) {
    Serial.write(HC12.read()); 
  }
  while(Serial.available()) {
    HC12.write(Serial.read());
  }

  if (millis() - lastRead > myDelay) {
    lastRead = millis();
    t = ENV.readTemperature();
    h = ENV.readHumidity();
    String msg = String(String(stationId) + "|" + String(t) + "|" + String(h));
    HC12.println(msg);
    Serial.println("Sent MSG.");
  }
}
