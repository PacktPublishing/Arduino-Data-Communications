#include <MKRWAN.h>

LoRaModem modem;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial); 

  if (!modem.begin(US915)) {
    Serial.println("Failed to initialize LoRa modem, aborting");
    while(true);
  }
  Serial.println("Initialized LoRa modem");
}

void loop() {
  if(!modem.available()) {
    return;
  }
  char buffer[64];
  int i = 0;
  while(modem.available()) {
    buffer[i++] = (char)modem.read();
  }
  Serial.print("Received: ");
  for (unsigned int j = 0; j < i; j++) {
    Serial.print(buffer[j] >> 4, HEX);
    Serial.print(buffer[j] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();
}
