#include "DFRobot_RGBLCD1602.h"

#define red 0
#define green 0
#define blue 255

DFRobot_RGBLCD1602 lcd(/*lcdCols*/16,/*lcdRows*/2);  //16 characters and 2 lines of show

void setup() {
    lcd.init(); 
    lcd.setRGB(red, green, blue);
    print_lcd("Hello, world", "of embedded");
}

void loop() {
    
}

void print_lcd(String l1, String l2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(l1);
  lcd.setCursor(0, 1);
  lcd.print(l2);
}