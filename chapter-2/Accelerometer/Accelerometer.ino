#include "Display.hpp"
#include "Accel.hpp"

void setup() {
  Serial.begin(115200);
  Accel::initialize();
  Display::initialize();
  if (Accel::lisAvailable()) {
    Display::print_lcd("Accel Demo", "Open serial mon");
    Serial.println("LIS3DHTR connected.");
  } else {
    Display::print_lcd("Accel Demo", "Couldn't Start");
    Serial.println("LIS3DHTR didn't connect.");
    while (1)
      ;
    return;
  }
  
}

void loop() {
  Serial.print(Accel::getAccelerationX()); 
  Serial.print("\t");
  Serial.print(Accel::getAccelerationY()); 
  Serial.print("\t");
  Serial.println(Accel::getAccelerationZ());
  delay(1000);
}
