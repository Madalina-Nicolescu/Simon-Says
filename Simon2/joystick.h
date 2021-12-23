#pragma once
#include "menu.h"
#include "eepr.h"

byte xJoyMoved = 0;
byte yJoyMoved = 0;
volatile  unsigned long long lastChange = 0;
volatile bool gameStarted = false;
volatile bool losed = false;
volatile bool winned = false;
byte setNameCursor = 0;
bool gameNotOver = true;
volatile bool nameSetted = false;


void readSWState() {
  if (millis() - lastChange > debounceInterval) {
    if (menuState == "principal") {
      previousMenuCursor = menuCursor;
      if (menuCursor == 0) {
        menuState = "game";
      }
      else if (menuCursor == 1) {
        menuState = "highscore";
      }
      else if (menuCursor == 2) {
        menuState = "settings";
      }
      else if (menuCursor == 3) {
        menuState = "about";
      }
      menuCursor = 0;
    }
    else if (menuState == "game") {
      previousState = "game";
      if (losed) {
        menuState = "principal";
        menuCursor = 0;
      }
      else if (winned) {
        menuState = "name";
        menuCursor = 0;
        nameSetted = false;
      }
    }
    else if (menuState == "about") {
      if (menuCursor == 0) {
        menuState = "principal";
        menuCursor = 3;
      }
    }
    else if (menuState == "settings") {
      previousMenuCursor = menuCursor;

      if (menuCursor == 0) {
        menuCursor = 2;
        menuState = "principal";
      }
      else if (menuCursor == 1) {
        menuCursor = 0;
        menuState = "difficulty";
      }
      else if (menuCursor == 2) {
        menuCursor = 0;
        menuState = "contrast";
      }
      else if (menuCursor == 3) {
        menuCursor = 0;
        menuState = "brightness";
      }
      else if (menuCursor == 4) {
        menuCursor = 0;
        menuState = "matrixBrightness";
      }
      else if (menuCursor == 5) {
        menuCursor = 0;
        menuState = "confirmation";
      }
      else if (menuCursor == 6) {
        menuCursor = 0;
        menuState = "sound";
      }
      else if (menuCursor == 7) {
        menuCursor = 0;
        menuState = "song";
      }
    }
    else if (menuState == "confirmation") {
      if (menuCursor == 0) {
        menuCursor = previousMenuCursor;
        menuState = "settings";
      if (menuCursor == 1) {
        menuCursor = 0;
        menuState = "clearHighscore";
      }
    }
    else if (menuState == "name" && setNameCursor == NAME_MAX_LENGTH) {
      saveScore(finalScore, playerName);
      previousState = "name";
      menuState = "highscore";
      menuCursor = 0;
      nameSetted = true;

    }
    else if (menuState == "highscore" && menuCursor == 0) {
      menuState = "principal";
      menuCursor = 1;
    }
    else if (menuState == "difficulty" || menuState == "contrast" || menuState == "brightness" || menuState == "matrixBrightness" || menuState == "clearHighscore" || menuState == "sound" || menuState == "song") {
      previousState = menuState;
      menuState = "settings";
      menuCursor = previousMenuCursor;
    }
  }
  buttonPressed = true;
  lastChange = millis();
}


void joystickInitialize() {
  char playerName = new char[5];
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), readSWState, FALLING);
}

int xMoveJoystick(int xCursor, int minX, int maxX, bool loopActivated) {
  int xValue = analogRead(xPin);
  if (millis() - lastChange  > debounceInterval) {
    if (xValue < minThreshold && !xJoyMoved) {
      if (xCursor > minX) {
        xCursor--;
      }
      else if (loopActivated) {
        xCursor = maxX;
      }
      xJoyMoved = 1;
      lastChange = millis();
    }
    if (xValue > maxThreshold && !xJoyMoved) {
      if (xCursor < maxX) {
        xCursor++;
      }
      else if (loopActivated) {
        xCursor = minX;
      }
      xJoyMoved = 1;
      lastChange = millis();
    }
    if (xValue > minThreshold && xValue < maxThreshold) {
      xJoyMoved = 0;
    }
  }
  return xCursor;
}

int yMoveJoystick(int yCursor, int minY, int maxY, bool loopActivated) {
  int yValue = analogRead(yPin);
  if (millis() - lastChange  > debounceInterval) {
    if (yValue < minThreshold && !yJoyMoved) {
      if (yCursor > minY) {
        yCursor--;
      }
      else if (loopActivated) {
        yCursor = maxY;
      }
      yJoyMoved = 1;
      lastChange = millis();
    }
    if (yValue > maxThreshold && !yJoyMoved) {
      if (yCursor < maxY) {
        yCursor++;
      }
      else if (loopActivated) {
        yCursor = minY;
      }
      yJoyMoved = 1;
      lastChange = millis();
    }
    if (yValue > minThreshold && yValue < maxThreshold) {
      yJoyMoved = 0;
    }
  }
  return yCursor;
}
