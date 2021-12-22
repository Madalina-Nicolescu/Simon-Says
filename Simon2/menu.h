#pragma once
#include <LiquidCrystal.h>
#include "customChar.h"

bool buttonPressed = false;
String menuState = "principal";
byte menuSize;
String* options = new String[10];
volatile byte previousCursor;
volatile byte menuCursor;
String previousState;
volatile byte previousMenuCursor;

void menuInitialize() {
  menuState = "principal";
  previousState = "";
  previousCursor = 0;
  menuCursor = 0;
  menuSize = 4;
  options[0] = "Start Game";
  options[1] = "Highscore";
  options[2] = "Settings";
  options[3] = "About";
}



bool menuChanged() {
  bool changed =  (previousCursor != menuCursor || previousState != menuState || buttonPressed);
  return changed;
}
