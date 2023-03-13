#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <LoRa.h>

unsigned long lastRead = millis();
const int myDelay = 15000;

float temperature, humidity;
const int stationId = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!ENV.begin()) {
    Serial.println("Failed to initialive ENV Shield, waiting ...");
    delay(10000);
  }
  Serial.println("Initialized ENV Shield");
  if (!LoRa.begin(915E6)) {
    Serial.println("Failed to initialize LoRa, aborting");
    while(true);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - lastRead > myDelay) {
    lastRead = millis();
    temperature = ENV.readTemperature();
    humidity = ENV.readHumidity();
    Serial.print("T: ");
    Serial.println(temperature);
    Serial.print("H: ");
    Serial.println(humidity);

    LoRa.beginPacket();
    LoRa.print(stationId);
    LoRa.print(":");
    LoRa.print(temperature);
    LoRa.print("|");
    LoRa.print("humidity");
    LoRa.endPacket();
  }
}
