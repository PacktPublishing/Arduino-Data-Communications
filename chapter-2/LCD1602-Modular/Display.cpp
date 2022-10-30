#include "Display.hpp"
#include "DFRobot_RGBLCD1602.h"

namespace Display {
  DFRobot_RGBLCD1602 lcd(/*lcdCols*/16,/*lcdRows*/2);  //16 characters and 2 lines of show

  void initialize() {
    lcd.init(); 
    lcd.setRGB(red, green, blue);
  }

  void print_lcd(String line1, String line2){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);    
  }
}