#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_JSON.h>
#include "arduino_secrets.h" 

unsigned long lastRead = millis();
const int myDelay = 15000;

float temperature, humidity;
const int stationId = 1;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int status = WL_IDLE_STATUS;
IPAddress server(192,168,68,120);
uint16_t port = 3000;
WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!ENV.begin()) {
    Serial.println("Failed to initialive ENV Shield, waiting ...");
    delay(10000);
  }
  while (status != WL_CONNECTED) {
    Serial.println("Attempting WiFi connection ...");
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.println("Connected to WiFi");
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

    client.stop();

    if (client.connect(server, port)) {
      JSONVar payload;
      payload["stationid"] = stationId;
      payload["epochs"] = 1;
      payload["temperature"] = temperature;
      payload["humidity"] = humidity;

      String p = JSON.stringify(payload);

      Serial.println("Connected to server, posting data");
      /*client.println("GET /readings HTTP/1.1");
      client.println();*/
      client.println("POST /readings HTTP/1.1");
      client.println("Content-Type: application/json");
      client.print("Content-Length: ");
      client.println(p.length());
      client.println();
      client.println(p);
      client.println("Connection: close");
      client.println();
    } else {
      Serial.println("Can't connect to server");
    }
  }
}
