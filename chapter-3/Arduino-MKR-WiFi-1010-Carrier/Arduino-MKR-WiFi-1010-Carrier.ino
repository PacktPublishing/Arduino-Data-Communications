#include "MyWireless.hpp"
#include "MyNTPClient.hpp"
#include "MyClock.hpp"
#include "MyCarrier.hpp"

#include <Arduino_MKRIoTCarrier.h>

int status = MyWireless::getIdleStatus(); 
auto lastMillis = millis();
const int myDelay = 60000;
MyClock::MyClock rtc = MyClock::MyClock();
MyCarrier::MyCarrier myCarrier = MyCarrier::MyCarrier();
MKRIoTCarrier carrier;

void setup() {
  // put your setup code here, to run once:
  delay(1500);
  CARRIER_CASE = false;
  carrier.begin();
  myCarrier.initialize(&carrier);
  display("Starting ..");

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  //while (!Serial);

  // attempt to connect to Wifi network:
  while (status != MyWireless::getConnectedStatus()) {
    display("Network ..");
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
    display("RTC Fail!");
    Serial.println("Unable to initialize the Realtime Clock, aborting ...");
    while(1);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");

  Serial.println("----------------------------------------");
  printData();
  Serial.println("----------------------------------------");
  
  Serial.print("NTP Unix Time: ");
  Serial.println(currentTime);
  Serial.println(MyNTPClient::getTimeFromUnix(currentTime));
  Serial.print("RTC Unix Time: ");
  Serial.println(rtc.getEpochs());
  Serial.println(rtc.getWATDateTime());
  Serial.println("------------------------");
  Serial.print("Temp (C): ");
  Serial.println(myCarrier.getTemperature());
  myCarrier.displaySensors(rtc.getWATTime());
  lastMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if( (millis() - lastMillis >= myDelay)) {
    Serial.println(rtc.getWATDateTime());
    Serial.print("Temp (C): ");
    Serial.println(myCarrier.getTemperature());
    myCarrier.displaySensors(rtc.getWATTime());
    lastMillis = millis();
  }
}

void printData() {
  Serial.println("Board Information:");
  // print your board's IP address:
  IPAddress ip = MyWireless::getLocalIp();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(MyWireless::getSSID());

  // print the received signal strength:
  long rssi = MyWireless::getRSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
  // are we running the latest firmware version?
  Serial.print("running latest firmware version: ");
  Serial.println(MyWireless::isOnLatestFirmware());
}

void display(String text) {
  carrier.display.fillScreen(0x0000);
  carrier.display.setCursor(25, 100);
  carrier.display.setTextSize(3);
  carrier.display.print(text);
}
