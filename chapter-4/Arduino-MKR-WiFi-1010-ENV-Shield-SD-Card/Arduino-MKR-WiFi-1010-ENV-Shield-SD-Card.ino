#include "MyWireless.hpp"
#include "MyNTPClient.hpp"
#include "MyClock.hpp"
#include "MyEnv.hpp"

#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <SD.h>

float temp, humid;
const int chipSelect = 4;
unsigned long lastRead = millis();
const int myDelay = 60000;
int status = MyWireless::getIdleStatus(); 
MyClock::MyClock rtc = MyClock::MyClock();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }

  Serial.print("\nInitializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  }
  Serial.println("Card detected.");

  // attempt to connect to Wifi network:
  while (status != MyWireless::getConnectedStatus()) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(MyWireless::get_ssid());
    // Connect to WPA/WPA2 network:
    status = MyWireless::initialize();

    // wait 10 seconds for connection:
    delay(10000);
  }
  MyNTPClient::initialize();
  unsigned long currentTime = MyNTPClient::getUnixTime();
  if(!rtc.initialize(currentTime)) {
    Serial.println("Unable to initialize the Realtime Clock, aborting ...");
    while(1);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - lastRead > myDelay) {
    lastRead = millis();
    readEnv();
    Serial.print("T: ");
    Serial.println(temp);
    Serial.print("H: ");
    Serial.println(humid);
    String y = rtc.getYear();
    String m = rtc.getMonth();
    String d = rtc.getDay();
    unsigned long epochs = rtc.getEpochs();
    MyEnv::writeTSVToFile(y, m, d, epochs);
  }
}

void readEnv() {
  temp = MyEnv::getTemp();
  humid = MyEnv::getHumid();
}

