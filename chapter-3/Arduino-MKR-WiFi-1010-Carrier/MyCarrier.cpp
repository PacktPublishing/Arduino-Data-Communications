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
    // displaying temperature
    myCarrier->display.setCursor(25, 60);
    myCarrier->display.setTextSize(3);
    //myCarrier->display.print("Temperature");
    float temperature = myCarrier->Env.readTemperature();   //storing temperature value in a variable
    myCarrier->display.drawBitmap(25, 60, matl_thermostat, 48, 48, 0xDAC9); //0xDA5B4A); //draw a thermometer on the MKR IoT carrier's display
    myCarrier->display.setCursor(75, 70);
    myCarrier->display.print(temperature); // display the temperature on the screen
    myCarrier->display.print(" C");
    //delay(10000);
  
    // displaying humidity
    //myCarrier->display.fillScreen(0x0000);
    myCarrier->display.setCursor(25, 110);
    //myCarrier->display.setTextSize(3);
    //myCarrier->display.print("Humidity");
    myCarrier->display.drawBitmap(25, 110, matl_humidity, 48, 48, 0x0D14); //0x0CA1A6); //draw a humidity figure on the MKR IoT carrier's display
    float humidity = myCarrier->Env.readHumidity(); //storing humidity value in a variable
    myCarrier->display.setCursor(75, 120);
    myCarrier->display.print(humidity); // display the humidity on the screen
    myCarrier->display.print(" %");
    //delay(10000);
  
    // displaying pressure
    //myCarrier->display.fillScreen(0x0000);
    myCarrier->display.setCursor(25, 170);
    myCarrier->display.setTextSize(3);
    //myCarrier->display.print("Pressure");
    myCarrier->display.drawBitmap(25, 160, matl_pressure, 48, 48, 0xF621); //0xF1C40F); //draw a pressure figure on the MKR IoT carrier's display
    float press = myCarrier->Pressure.readPressure(); //storing pressure value in a variable
    myCarrier->display.setCursor(75, 165);
    myCarrier->display.print(press); // display the pressure on the screen
    //myCarrier->display.setCursor(160, 160);
    myCarrier->display.print("KPa");
    //delay(10000);
  }
}