#include "MyCarrier.hpp"

#include "logos.h"

namespace MyCarrier {
  MKRIoTCarrier* myCarrier;

  void MyCarrier::initialize(MKRIoTCarrier* carrier) {
    myCarrier = carrier;
  }

  float MyCarrier::getTemperature() {
    return myCarrier->Env.readTemperature();
  }

  float MyCarrier::getPressure() {
    return myCarrier->Pressure.readPressure();
  }

  float MyCarrier::getHumidity() {
    return myCarrier->Env.readHumidity();
  }

  void MyCarrier::displaySensors(String time) {
    myCarrier->display.fillScreen(0x0000);
    myCarrier->display.setCursor(60, 30);
    myCarrier->display.setTextSize(3);
    myCarrier->display.print(time);
    myCarrier->display.setCursor(25, 60);
    myCarrier->display.setTextSize(3);
    float temperature = myCarrier->Env.readTemperature();   //storing temperature value in a variable
    myCarrier->display.drawBitmap(25, 60, matl_thermostat, 48, 48, 0xDAC9); //0xDA5B4A); //draw a thermometer on the MKR IoT carrier's display
    myCarrier->display.setCursor(75, 70);
    myCarrier->display.print(temperature); 
    myCarrier->display.print(" C");
  
    myCarrier->display.setCursor(25, 110);
    myCarrier->display.drawBitmap(25, 110, matl_humidity, 48, 48, 0x0D14); 
    float humidity = myCarrier->Env.readHumidity(); 
    myCarrier->display.setCursor(75, 120);
    myCarrier->display.print(humidity); 
    myCarrier->display.print(" %");
    
    myCarrier->display.setCursor(25, 170);
    myCarrier->display.setTextSize(3);
    myCarrier->display.drawBitmap(25, 160, matl_pressure, 48, 48, 0xF621); 
    float press = myCarrier->Pressure.readPressure(); 
    myCarrier->display.setCursor(75, 165);
    myCarrier->display.print(press); 
    myCarrier->display.print("KPa");
  }
}