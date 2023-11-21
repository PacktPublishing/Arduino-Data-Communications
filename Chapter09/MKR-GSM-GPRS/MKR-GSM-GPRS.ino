#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <Arduino_JSON.h>
#include <MKRGSM.h>
#include "arduino_secrets.h" 

unsigned long lastRead = millis();
const int myDelay = 60000;

float temperature, humidity;
const int stationId = 1;

char apn[] = SECRET_APN;
char user[] = SECRET_USER;
char pass[] = SECRET_PASS;

GPRS gprs;
GSM gsmAccess;
GSMClient client;

char server[] = SECRET_SERVER;
char path[] = SECRET_PATH;
int port = 80;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!ENV.begin()) {
    Serial.println("Failed to initialive ENV Shield, waiting ...");
    delay(10000);
  }
  boolean connected = false;
  while (!connected) {
    if ( gsmAccess.begin() == GSM_READY) {
      if (gprs.attachGPRS(apn, user, pass) == GPRS_READY) {
        Serial.println("GPRS connected.");
        connected = true;        
      }
    } else {
      Serial.println("Unable to initialize the modem");
      delay(1000);     
    }
  }
  Serial.println("Ready ...");
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
    

    if (client.connect(server, port)) {
      JSONVar payload;
      payload["stationid"] = stationId;
      payload["epochs"] = 1;
      payload["temperature"] = temperature;
      payload["humidity"] = humidity;

      String p = JSON.stringify(payload);

      Serial.println("Connected to server, posting data");
      
      client.print("POST ");
      client.print(path);
      client.println(" HTTP/1.1");
      client.print("HOST: ");
      client.println(server);
      client.println("Content-Type: application/json");
      client.print("Content-Length: ");
      client.println(p.length());
      client.println();
      client.println(p);
      client.println("Connection: close");
      client.println();

      Serial.println("Payload sent.");

      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }
      Serial.println();

      if(!client.available() && !client.connected()) {
        client.stop();
      }
    } else {
      Serial.println("Can't connect to server");
    }
  }  
}
