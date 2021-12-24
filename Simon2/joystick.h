#pragma once
#include "photoRes.h"
#include "eepr.h"
#include "globals.h"

void readSWState() {
  if (millis() - lastChange > DEBOUNCE_INTERVAL) {
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
      previousMenuCursor = menuCursor;
      if (menuCursor == 0) {
        menuState = "principal";
        menuCursor = 3;
      }
      else if(menuCursor == 1){
        menuState = "gameName";
        menuCursor = 0;
      }
      else if(menuCursor == 2){
        menuState = "author";
        menuCursor = 0;
      }
      else if(menuCursor == 3){
        menuState = "github";
        menuCursor = 0;
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
      }
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
      else if (menuState == "gameName" || menuState == "author" || menuState == "github"){
        previousState = menuState;
        menuState = "about";
        menuCursor = previousMenuCursor;
      }
    }
    buttonPressed = true;
    lastChange = millis();
}

void joystickInitialize() {
  char playerName = new char[5];
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(PIN_SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_SW), readSWState, FALLING);
}

int xMoveJoystick(int xCursor, int minX, int maxX, bool loopActivated) {
  int xValue = analogRead(X_PIN);
  if (millis() - lastChange  > DEBOUNCE_INTERVAL) {
    if (xValue < MIN_THRESHOLD && !xJoyMoved) {
      if (xCursor > minX) {
        xCursor--;
      }
      else if (loopActivated) {
        xCursor = maxX;
      }
      xJoyMoved = 1;
      lastChange = millis();
    }
    if (xValue > MAX_THRESHOLD && !xJoyMoved) {
      if (xCursor < maxX) {
        xCursor++;
      }
      else if (loopActivated) {
        xCursor = minX;
      }
      xJoyMoved = 1;
      lastChange = millis();
    }
    if (xValue > MIN_THRESHOLD && xValue < MAX_THRESHOLD) {
      xJoyMoved = 0;
    }
  }
  return xCursor;
}

int yMoveJoystick(int yCursor, int minY, int maxY, bool loopActivated) {
  int yValue = analogRead(Y_PIN);
  if (millis() - lastChange  > DEBOUNCE_INTERVAL) {
    if (yValue < MIN_THRESHOLD && !yJoyMoved) {
      if (yCursor > minY) {
        yCursor--;
      }
      else if (loopActivated) {
        yCursor = maxY;
      }
      yJoyMoved = 1;
      lastChange = millis();
    }
    if (yValue > MAX_THRESHOLD && !yJoyMoved) {
      if (yCursor < maxY) {
        yCursor++;
      }
      else if (loopActivated) {
        yCursor = minY;
      }
      yJoyMoved = 1;
      lastChange = millis();
    }
    if (yValue > MIN_THRESHOLD && yValue < MAX_THRESHOLD) {
      yJoyMoved = 0;
    }
  }
  return yCursor;
}
