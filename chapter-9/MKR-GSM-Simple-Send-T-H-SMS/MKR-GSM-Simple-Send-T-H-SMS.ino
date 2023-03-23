#include <Arduino_MKRENV.h>
#include <MKRGSM.h>
#include "arduino_secrets.h"

unsigned long lastRead = millis();
const int myDelay = 60000;
float t,h;
const int stationId = 1;

const char PHONE[] = SECRET_PHONE;

GSM gsmAccess;
GSM_SMS sms;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  while (!ENV.begin()) {
    Serial.println("Failed to initialize ENV Shield, waiting ...");
    delay(10000);
  }
  Serial.println("Initialized ENV Shield");

  bool connected = false;
  while (!connected) {
    if (gsmAccess.begin() == GSM_READY) {
      connected = true;
    } else {
      Serial.println("Couldn't initialize modem, waiting ...");
      delay(1000);
    }
  }
  Serial.println("Modem initialized."); 

  Serial.println("Ready ...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - lastRead > myDelay) {
    lastRead = millis();
    t = ENV.readTemperature();
    h = ENV.readHumidity();
    String msg = String(String(stationId) + "|" + String(t) + "|" + String(h));
    Serial.println(msg);
    sms.beginSMS(PHONE);
    sms.print(msg);
    sms.endSMS();
    Serial.println("Sent SMS.");
  }
}
