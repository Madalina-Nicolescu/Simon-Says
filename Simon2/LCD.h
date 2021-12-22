#pragma once
#include <Vector.h>
#include <LiquidCrystal.h>
#include "eepr.h"
#include "joystick.h"
#include "menu.h"
#include "matrix.h"
#include "customChar.h"


int brightness;
int contrast;
byte difficulty;
bool displayNameScreenInitialized = false;
byte song = 1;
LiquidCrystal lcd = LiquidCrystal(RS, ENABLE, D4, D5, D6, D7);



void lcdInitialize() {
  brightness = readIntFromEEPROM(BRIGHTNESS_ADDR);
  contrast = readIntFromEEPROM(CONTRAST_ADDR);
  lcd.createChar(0, verticalLine);
  lcd.createChar(1, downArrowChar);
  lcd.createChar(2, upArrowChar);
  lcd.createChar(3, heartChar);
  //lcd.createChar(4, fullChar);
  lcd.createChar(5, hourglassChar);
  lcd.createChar(6, checkChar);
  lcd.createChar(7, emptyBoxChar);
  lcd.begin(noOfColumns, noOfLines);
}

void printBar(byte barLength) {
  lcd.setCursor(1, 1);
  lcd.print(F("-"));
  lcd.setCursor(14, 1);
  lcd.print(F("+"));
  lcd.setCursor(3, 1);
  for (byte i = 3; i <= 12; i++) {
    if (i - 3 < barLength) {
      lcd.write(255);
    }
    else {
      lcd.print(" ");
    }
  }
}

void updateGame(byte lives, int remainingTime, int score) {
  lcd.setCursor(1, 0);
  lcd.print(lives);
  lcd.setCursor(7, 0);
  lcd.print(score);

  lcd.setCursor(3, 1);
  for (byte i = 3; i <= 12; i++) {
    if (i - 3 < remainingTime) {
      lcd.write(255);
    }
    else {
      lcd.print(" ");
    }
  }
}

void gameDisplay(int level) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(F("The game"));
  lcd.setCursor(3, 1);
  lcd.print(F("starts in..."));
  countdown();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(3));
  lcd.print(3);
  lcd.setCursor(6, 0);
  lcd.write(byte(6));
  lcd.print(0);
  lcd.setCursor(11, 0);
  lcd.print("Lvl:");
  lcd.setCursor(15, 0);
  lcd.print(level);
  lcd.setCursor(0, 1);
  lcd.write(byte(5));
  lcd.setCursor(3, 1);
  for (byte i = 3; i <= 12; i++) {
    lcd.write(255);
  }
}

void chooseName() {
  if (setNameCursor != NAME_MAX_LENGTH) {
    lcd.setCursor(12, 1);
    lcd.print(F(" OK"));
    byte x = xMoveJoystick(setNameCursor, 0, NAME_MAX_LENGTH, false);
    setNameCursor = x;
    char letter = playerName[setNameCursor];
    byte y;
    if (letter != '_') {
      y = yMoveJoystick(letter, 97, 122, true);
    }
    else {
      y = yMoveJoystick(97, 97, 122, true);
    }
    letter = y;
    playerName[setNameCursor] = letter;
    if (setNameCursor != NAME_MAX_LENGTH) {
      lcd.setCursor(4 + setNameCursor, 1);
      lcd.print(letter);
    }
  }
  else {
    playerName[setNameCursor] = '\n';
    lcd.setCursor(12, 1);
    lcd.print(F(">OK"));
    byte x = xMoveJoystick(setNameCursor, 0, NAME_MAX_LENGTH, false);
    setNameCursor = x;
  }
}
void displayNameScreen() {
  lcd.setCursor(4, 1);
  for (byte i = 0; i < NAME_MAX_LENGTH; i++) {
    lcd.print('_');
  }
  lcd.setCursor(13, 1);
  lcd.print(F("OK"));
  lcd.setCursor(4, 1);
}

void setBrightness() {
  byte incrStep = MAX_CONTR_BRIGHT / BAR_LENGTH;
  byte contrastCursor = (readIntFromEEPROM(CONTRAST_ADDR)) / incrStep;
  byte x = xMoveJoystick(contrastCursor, 0, BAR_LENGTH, false);
  if (x > BAR_LENGTH) {
    x = BAR_LENGTH;
  }
  printBar(x);
  byte newContrast = x * incrStep;
  contrast = newContrast;
  if (newContrast > MAX_CONTR_BRIGHT) {
    contrast = MAX_CONTR_BRIGHT;
  }
  writeIntIntoEEPROM(CONTRAST_ADDR, newContrast);
}

void setContrast() {
  byte incrStep = MAX_CONTR_BRIGHT / BAR_LENGTH;
  byte brightnessCursor = (readIntFromEEPROM(BRIGHTNESS_ADDR)) / incrStep;
  byte x = xMoveJoystick(brightnessCursor, 0, BAR_LENGTH, false);
  if (x > BAR_LENGTH) {
    x = BAR_LENGTH;
  }
  printBar(x);
  byte newBrightness = x * incrStep;
  brightness = newBrightness;
  if (newBrightness > MAX_CONTR_BRIGHT) {
    brightness = MAX_CONTR_BRIGHT;
  }
  writeIntIntoEEPROM(BRIGHTNESS_ADDR, newBrightness);
}

void setMatrixBrightness() {
  displayAll();
  byte incrStep = MAX_MATRX_BRIGHT / BAR_LENGTH;
  byte brightnessCursor = readIntFromEEPROM(MATRIX_BRIGHTNESS_ADDR) / incrStep;
  byte x = xMoveJoystick(brightnessCursor, 0, BAR_LENGTH, false);
  if (x > BAR_LENGTH) {
    x = BAR_LENGTH;
  }
  printBar(x);
  byte newBrightness = x * incrStep;
  if (newBrightness > MAX_MATRX_BRIGHT) {
    newBrightness = MAX_MATRX_BRIGHT;
  }
  setMatrixBrightness(newBrightness);
  writeIntIntoEEPROM(MATRIX_BRIGHTNESS_ADDR, newBrightness);
}



void setSound() {
  soundOff = xMoveJoystick(soundOff, 0, 1, false);
  if (soundOff) {
    lcd.setCursor(7, 1);
    lcd.write(7);
    lcd.write(255);
  }
  else {
    lcd.setCursor(7, 1);
    lcd.write(255);
    lcd.write(7);
  }
}

void lcdIntro() {
  lcd.setCursor(4, 0);
  lcd.print(F("Simon"));
  lcd.setCursor(7, 1);
  lcd.print(F("says"));
}

void writeArrows(bool bothArrows, bool downArrow, bool upArrow) {
  if (bothArrows) {
    lcd.setCursor(noOfColumns - 1, 0);
    lcd.write(byte(2));
    lcd.setCursor(noOfColumns - 1, 1);
    lcd.write(byte(1));
  }
  else if (downArrow) {
    lcd.setCursor(noOfColumns - 1, 0);
    lcd.write(byte(0));
    lcd.setCursor(noOfColumns - 1, 1);
    lcd.write(byte(1));
  }
  else if (upArrow) {
    lcd.setCursor(noOfColumns - 1, 0);
    lcd.write(byte(2));
    lcd.setCursor(noOfColumns - 1, 1);
    lcd.write(byte(0));
  }
}

void showMenu() {
  bool showArrows = false;
  if (menuSize >= 3) {
    showArrows = true;
  }
  if (menuSize == 1) {
    lcd.setCursor(0, 0);
    lcd.print(options[menuCursor]);
  }
  else if (menuState == "difficulty" || menuState == "song") {
    if (menuCursor < menuSize - 1) {
      lcd.setCursor(0, 0);
      lcd.print(options[0]);
      lcd.setCursor(1, 1);
      lcd.print('>' + options[menuCursor + 1]);
    }
  }
  else if (menuState != "principal" && menuCursor == 0) {
    lcd.setCursor(0, 0);
    lcd.print(options[menuCursor]);
    lcd.setCursor(1, 1);
    lcd.print(options[menuCursor + 1]);
  }
  else if (menuCursor < menuSize - 1) {
    lcd.setCursor(0, 0);
    lcd.print('>' + options[menuCursor]);
    lcd.setCursor(1, 1);
    lcd.print(options[menuCursor + 1]);
    lcd.setCursor(0, 1);
  }
  else {
    lcd.setCursor(1, 0);
    lcd.print(options[menuCursor - 1]);
    lcd.setCursor(0, 1);
    lcd.print('>' +  options[menuCursor]);
    lcd.setCursor(0, 1);
  }

  if (showArrows) {
    bool downArrow = false;
    bool  bothArrows = false;
    bool upArrow = false;

    if (menuCursor == 0) {
      downArrow = true;
      bothArrows = false;
      upArrow = false;
    }
    else if (menuCursor >= menuSize - 2) {
      downArrow = false;
      bothArrows = false;
      upArrow = true;
    }
    else {
      downArrow = false;
      bothArrows = true;
      upArrow = false;
    }

    writeArrows( bothArrows, downArrow,  upArrow);
  }
}

void updateMenu() {

  if (menuState == "difficulty") {
    menuCursor = yMoveJoystick(menuCursor, 0, menuSize - 2, false);
    difficulty = menuCursor + 1;
  }
  if (menuState == "song") {
    menuCursor = yMoveJoystick(menuCursor, 0, menuSize - 2, false);
    song = menuCursor + 1;
  }
  else if (menuState == "contrast") {
    setContrast();

  }
  else if (menuState == "brightness" ) {
    setBrightness();

  }
  else if (menuState == "matrixBrightness") {
    setMatrixBrightness();
  }
  else if (menuState == "sound") {
    setSound();
  }
  else if (menuState == "name") {
    if (!displayNameScreenInitialized) {
      displayNameScreen();
      displayNameScreenInitialized = true;
    }
    chooseName();
  }
  if (previousState == "name") {
    if (nameSetted) {
      saveScore(finalScore, playerName);
      for (byte i = 0; i < NAME_MAX_LENGTH; i++) {
        playerName[i] = '_';
      }
      playerName[NAME_MAX_LENGTH] = '\n';
      setNameCursor = 0;
    }
  }
  else if (menuState == "clearHighscore") {
    for (byte i = 0; i < TOP_PLAYERS_SIZE; i++) {
      for (byte j = 0; j < sizeof(int); j++) {
        clearIntFromAddress(highscoreAddresses[i] + j);
      }
      clearIntFromAddress(topPlayersAddresses[i]);
      for (byte j = 0; j < NAME_MAX_LENGTH * sizeof(char); j++) {
        clearCharFromAddress(topPlayersAddresses[i] + 1 + j);
      }
    }
  }
  else {
    menuCursor = yMoveJoystick(menuCursor, 0, menuSize - 1, false);
  }
  if (menuChanged()) {
    if (!soundOff) {
      tone(BUZZER_PIN, 1500, 10);
    }

    if (previousState == "principal") {
      if (menuState == "settings") {
        printSettingsIcon();
      }
      else if (menuState == "highscore") {
        printHighscoreIcon();
      }
      else if (menuState == "about") {
        printAboutIcon();
      }
    }
    else if (menuState == "principal") {
      printLogo();
    }
    if (previousState == "matrixBrightness") {
      printSettingsIcon();
    }
    else if (previousState == "game") {
      gameNotOver = true;
      printLogo();
    }

    if (previousState == "difficulty") {
      writeIntIntoEEPROM(DIFFICULTY_ADDR, difficulty);
    }
    lcd.clear();
    showMenu();
    previousCursor = menuCursor;
    previousState = menuState;
  }
}

void fillMenu(String newState) {
  menuState = newState;
  //delete []options;
  if (menuState == "principal") {
    menuSize = 4;
    //options = new String[menuSize];
    options[0] = "Start Game";
    options[1] = "Highscore";
    options[2] = "Settings";
    options[3] = "About";
  }
  else if (menuState == "settings") {
    menuSize = 8;
    //options = new String[menuSize];
    options[0] = "< BACK";
    options[1] = "Difficulty";
    options[2] = "Contrast";
    options[3] = "Brightness";
    options[4] = "Matrix Brightness";
    options[5] = "Clear Highscore";
    options[6] = "Sound";
    options[7] = "Game Song";
  }
  else if (menuState == "about") {
    menuSize = 4;
    //options = new String[menuSize];
    options[0] = "< BACK";
    options[1] = "Game name: Simon Says";
    options[2] = "Author : Madalina Nicolescu";
    options[3] = "Github";
  }
  else if (menuState == "highscore") {
    menuSize = 6;
    //options = new String[menuSize];
    options[0] = "< BACK";
    options[1] = readHighscorePosition(0);
    options[2] = readHighscorePosition(1);
    options[3] = readHighscorePosition(2);
    options[4] = readHighscorePosition(3);
    options[5] = readHighscorePosition(4);
  }
  else if (menuState == "difficulty") {
    menuSize = 4;
    //options = new String[menuSize];
    options[0] = "Set Difficulty";
    options[1] = "LOW";
    options[2] = "MEDIUM";
    options[3] = "HIGH";
  }
  else if (menuState == "song") {
    menuSize = 4;
    //options = new String[menuSize];
    options[0] = "Choose song";
    options[1] = "Jingle Bells";
    options[2] = "We wish you a merry Christmas";
    options[3] = "Santa Claus is coming to town";
  }
  else if (menuState == "contrast") {
    menuSize = 1;
    //options = new String[menuSize];
    options[0] = "Set Contrast";
  }
  else if (menuState == "brightness") {
    menuSize = 1;
    //options = new String[menuSize];
    options[0] = "Set Brightness";
  }
  else if (menuState == "matrixBrightness") {
    menuSize = 1;
    //options = new String[menuSize];
    options[0] = F("Set Brightness");
  }
  else if (menuState == "clearHighscore") {
    menuSize = 2;
    //options = new String[menuSize];
    options[0] = F("   Highscore ");
    options[1] = F("      deleted!");
  }
  else if (menuState == "name") {
    menuSize = 1;
    //options = new String[menuSize];
    options[0] = F("   Set name");
  }
  else if (menuState == "sound") {
    menuSize = 2;
    //options = new String[menuSize];
    options[0] = F("     Sound");
    options[1] = F("   ON    OFF");
  }
}

void winningDisplay(int score) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(F("New Highscore"));
  lcd.setCursor(4, 1);
  lcd.print(F("Score:"));
  lcd.print(score);
}

void losingDisplay(int score) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(F("Game Over"));
  lcd.setCursor(4, 1);
  lcd.print(F("Score:"));
  lcd.print(score);
}
