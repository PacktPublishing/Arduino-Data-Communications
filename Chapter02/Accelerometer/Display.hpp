#pragma once

#include <Arduino.h>

namespace Display {
  #define red 0
  #define green 0
  #define blue 255

  void initialize();

  void print_lcd(String line1, String line2);
}