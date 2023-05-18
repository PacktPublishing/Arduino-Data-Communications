#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); //TX, RX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Connect Serial to Computer
  HC12.begin(9600); //Connect Serial to HC12
}

void loop() {
  // put your main code here, to run repeatedly:
  while(HC12.available()) {
    Serial.write(HC12.read()); //send data to the Serial monitor
  }
  while(Serial.available()) {
    HC12.write(Serial.read()); //send data to the HC-12
  }
}
