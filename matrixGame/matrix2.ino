#include <ArduinoQueue.h>
#include "customChar.h"

ArduinoQueue<char> moves(20);

#include "LedControl.h" //  need the library

#include <LiquidCrystal.h>
#include <EEPROM.h>


//----PINS----
// lcd display
const int RS = 13;
const int enable = 9;
const int d4 = 7;
const int d5 = 6;
const int d6 = 5;
const int d7 = 4;
const int contrastPin = 3;

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

const int pinSW = 2;
const int xPin = A0;
const int yPin = A1;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

int matrixBrightness = 2;

int contrast = 130;
int brightness = 130;
const int minThreshold = 200;
const int maxThreshold = 600;

const byte moveInterval = 100;
unsigned long long lastMoved = 0;

//const byte matrixSize = 8;
bool matrixChanged = true;

byte gameOver = 0;
byte gameStarted = 0;
byte joyMoved = false;

const byte noOfDirections = 4;
char directions[noOfDirections] = {
  'u', 'd', 'l', 'r'
};


unsigned int debounceInterval = 100;
unsigned long lastChanged = 0;
unsigned long lastDebounceTime = 0;
bool menuInitialized = false;

unsigned int introInterval = 5000;
byte noOfMoves = 2;
byte somethingChanged = 0;
bool lcdIntroPrinted = false;


int barLength = 5;
int maxBarLength = 10;
int maxContrast = 255;
int maxBrightness = 255;
int maxMatrBrightness = 15;
int incrStep;
byte contrastAddress = 35;
byte brightnessAddress = 37;
byte matrixBrightnessAddress = 39;

byte menuCursor;
byte menuSize;
String menuOptions[10];
byte menuYPos;
String menuState = "principal";
String previousMenuState = "principal";

byte principalYPos = 0;
byte principalMenuCursor = 0;
const byte principalMenuSize = 4;
String principalMenuOptions[principalMenuSize] = {
  "Start game", "Highscore", "Settings", "About"
};

byte settingsYPos = 1;
byte settingsMenuCursor = 1;
const byte settingsMenuSize = 5;
String settingsMenuOptions[settingsMenuSize] = {
  "< BACK", "Difficulty", "Contrast", "Brightness", "Matrix Brightness"
};

byte aboutYPos = 1;
byte aboutMenuCursor = 1;
const byte aboutMenuSize = 4;
String aboutMenuOptions[aboutMenuSize] = {
  "< BACK", "Game name: Simon Says", "Author : Madalina Nicolescu", "Github"
};

byte highscoreYPos = 1;
byte highscoreMenuCursor = 1;
const byte highscoreMenuSize = 6;
String highscoreMenuOptions[highscoreMenuSize] = {
  "< BACK", "1.", "2.", "3.", "4.", "5."
};



int minScore = 0;
byte maxNameLength = 5;
byte enterNameCursor = 0;
int nameLetter = 97;
bool xJoyMoved = false;
bool yJoyMoved = false;
String playerName = "";
const byte topPlayersSize = 5;

int highscore[topPlayersSize] = {
  0, 0, 0, 0, 0
};

int highscoreAddresses[topPlayersSize] = {
  0, 2, 4, 6, 8
};

String topPlayers[topPlayersSize] = {
  "", "", "", "", ""
};

int topPlayersAddresses[topPlayersSize] = {
  10, 15, 20, 25, 30
};


void setup() {
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), readSWState, FALLING);
  pinMode(contrastPin, OUTPUT);
  initialize();
}


void loop() {
  //countdown();
  if (!menuInitialized) {
    if (millis() < introInterval) {
      if (!lcdIntroPrinted) {
        lcdIntro();
        matrixIntro();
      }
    }
    else {
      menuInitialize();
    }
  }
  else {

    if (menuState == "game") {
      startGame();
    }
    else if (menuState == "difficulty") {
      if (previousMenuState != "difficulty") {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Set difficulty");
        lcd.setCursor(0, 1);
        lcd.print(">EASY");
        previousMenuState = "difficulty";
      }
      chooseDifficulty();
    }
    else if (menuState == "contrast") {
      if (previousMenuState != "contrast") {
        contrast  = readIntFromEEPROM(contrastAddress);
        Serial.println(contrast);

        calculateIncrStep(menuState);
        Serial.println(contrast / incrStep);

        barLength = contrast / incrStep;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Set contrast");
        lcd.setCursor(1, 1);
        lcd.print("-");
        lcd.setCursor(14, 1);
        lcd.print("+");
        lcd.setCursor(3, 1);
        for (int i = 3; i <= 12; i++) {
          if (i - 3 < barLength) {
            lcd.write(255);
          }
          else {
            lcd.print(" ");
          }
        }
        previousMenuState = "contrast";
      }
      barSet(menuState);
    }
    else if (menuState == "brightness") {
      if (previousMenuState != "brightness") {
        brightness  = readIntFromEEPROM(brightnessAddress);
        calculateIncrStep(menuState);
        barLength = brightness / incrStep;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Set brightness");
        lcd.setCursor(1, 1);
        lcd.print("-");
        lcd.setCursor(14, 1);
        lcd.print("+");
        lcd.setCursor(3, 1);
        for (int i = 3; i <= 12; i++) {
          if (i - 3 < barLength) {
            lcd.write(255);
          }
          else {
            lcd.print(" ");
          }
        }
        previousMenuState = "brightness";
      }
      barSet(menuState);
    }
    else if (menuState == "matrixBrightness") {
      if (previousMenuState != "matrixBrightness") {

        matrixBrightness  = readIntFromEEPROM(matrixBrightnessAddress);
        calculateIncrStep(menuState);
        barLength = matrixBrightness / incrStep;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Set brightness");
        lcd.setCursor(1, 1);
        lcd.print("-");
        lcd.setCursor(14, 1);
        lcd.print("+");
        lcd.setCursor(3, 1);
        for (int i = 3; i <= 12; i++) {
          if (i - 3 < barLength) {
            lcd.write(255);
          }
          else {
            lcd.print(" ");
          }
        }
        previousMenuState = "matrixBrightness";
      }
      barSet(menuState);
    }
    else {
      updateDisplay(menuState);
    }
  }
}

void writeIntIntoEEPROM(int address, int number) {
  EEPROM.update(address, number >> 8);
  EEPROM.update(address + 1, number & 0xFF);
}

int readIntFromEEPROM(int address) {
  return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}

void writeStringToEEPROM(int address, String strToWrite) {
  byte len = strToWrite.length();
  EEPROM.update(address, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.update(address + 1 + i, strToWrite[i]);
  }
}

String readStringFromEEPROM(int address) {
  int newStrLen = EEPROM.read(address);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(address + 1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}


void calculateIncrStep(String menuState) {
  if (menuState == "contrast" || menuState == "brightness") {
    incrStep = maxContrast /  maxBarLength;
  }
  else {
    incrStep = maxMatrBrightness / maxBarLength;
  }
}


void barSet(String menuState) {
  calculateIncrStep(menuState);
  int yValue = analogRead(yPin);
  if (millis() - lastChanged > debounceInterval) {
    lastChanged = millis();
    if (yValue < minThreshold && !joyMoved) {
      joyMoved = true;

      if (barLength > 0) {
        barLength--;
      }
    }

    if (yValue > maxThreshold && !joyMoved) {
      joyMoved = true;

      if (barLength < 10) {
        barLength++;
      }
    }
    if ( yValue > minThreshold && yValue < maxThreshold) {
      joyMoved = false;
    }
  }
  if (joyMoved) {
    lcd.setCursor(1, 1);
    lcd.print("-");
    lcd.setCursor(14, 1);
    lcd.print("+");
    lcd.setCursor(3, 1);
    for (int i = 3; i <= 12; i++) {
      if (i - 3 < barLength) {
        lcd.write(255);
      }
      else {
        lcd.print(" ");
      }
    }
    if (menuState == "contrast") {
      lcd.setCursor(1, 0);
      lcd.print("Set contrast");
      contrast = barLength * incrStep;
      writeIntIntoEEPROM(contrastAddress, contrast);
    }
    else if (menuState == "brightness") {
      lcd.setCursor(1, 0);
      lcd.print("Set brightness");
      brightness = barLength * incrStep;
      writeIntIntoEEPROM(brightnessAddress, brightness);
    }
    else if (menuState == "matrixBrightness") {
      lcd.setCursor(1, 0);
      lcd.print("Set brightness");
      matrixBrightness = barLength * incrStep;
      Serial.println(matrixBrightness);
      lc.setIntensity(0, matrixBrightness);
      writeIntIntoEEPROM(matrixBrightnessAddress, matrixBrightness);
    }
  }
}



void readSWState() {
  if (millis() - lastDebounceTime > debounceInterval) {
    if (menuState == "principal") {
      if (principalMenuCursor == 0) {
        menuState = "game";
      }
      else if (principalMenuCursor == 1) {
        menuState = "highscore";
      }
      else if (principalMenuCursor == 2) {
        menuState = "settings";
      }
      else if (principalMenuCursor == 3) {
        menuState = "about";
      }
    }
    else if (menuState == "about") {
      if (aboutMenuCursor == 0) {
        menuState = "principal";
      }
    }
    else if (menuState == "settings") {
      if (settingsMenuCursor == 0) {
        menuState = "principal";
      }
      else if (settingsMenuCursor == 1) {
        menuState = "difficulty";
      }
      else if (settingsMenuCursor == 2) {
        menuState = "contrast";
      }
      else if (settingsMenuCursor == 3) {
        menuState = "brightness";
      }
      else if (settingsMenuCursor == 4) {
        menuState = "matrixBrightness";
      }
    }
    else if (menuState == "name" && enterNameCursor == maxNameLength) {
      menuState = "highscore";
    }
    else if (menuState == "highscore" && highscoreMenuCursor == 0) {
      menuState = "principal";
    }
    else if (menuState == "difficulty" || menuState == "contrast" || menuState == "brightness" || menuState == "matrixBrightness") {
      menuState = "settings";
    }
  }
  lastDebounceTime = millis();
}

void initialize() {
  lc.shutdown(0, false); // turn off power saving, enables display
  matrixBrightness  = readIntFromEEPROM(matrixBrightnessAddress);
  lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  lcd.createChar(0, verticalLine);
  lcd.createChar(1, downArrowChar);
  lcd.createChar(2, upArrowChar);
  lcd.createChar(3, heartChar);
  lcd.createChar(4, fullChar);
  lcd.createChar(5, hourglassChar);
  lcd.createChar(6, checkChar);
  lcd.begin(16, 2);
  analogWrite(contrastPin, 130);
  initializeHighscoreMenu();
}

void initializeHighscoreMenu() {
  readHighScore();
  readTopPlayers();
  for (int i = 0; i < topPlayersSize; i++) {
    highscoreMenuOptions[i + 1] = String(i + 1) + "." +  topPlayers[i] + " -> " + highscore[i];
  }
}


int guessTime = 10000;
unsigned long long startTime = 0;
int lives = 3;
int timeBarLength = 12;
unsigned int decreaseTimeBarInterval = guessTime / timeBarLength;
unsigned long long lastBarDecrease = 0;
int level = 1;
int score = 0;
int scoreStep;


int previousCursor = 0;
byte timeExpired = 0;

void enterPlayerName() {
  menuState = "name";
  playerName = "aaaaa";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter your name:");
  lcd.setCursor(13, 1);
  lcd.print(" OK");
  lcd.blink();
  lcd.setCursor(1, 1);
  while (menuState == "name") {
    choosePosition();
    lcd.setCursor(enterNameCursor + 1, 1);
    chooseLetter();
    if (previousCursor != enterNameCursor) {
      if (enterNameCursor == maxNameLength) {
        lcd.noBlink();
        lcd.setCursor(13, 1);
        lcd.print(">OK");
      }
      else {
        lcd.setCursor(13, 1);
        lcd.print(" OK");
      }

      previousCursor = enterNameCursor;
      nameLetter = 97;
    }
  }
  Serial.println(playerName);
}

void chooseLetter() {
  int yValue = analogRead(yPin);
  if (millis() - lastChanged > debounceInterval) {
    lastChanged = millis();
    if (yValue < minThreshold && !yJoyMoved) {
      yJoyMoved = true;
      if (nameLetter > 97) {
        nameLetter--;

      }
      else {
        nameLetter = 122;
      }
      lcd.print(char(nameLetter));
      playerName[enterNameCursor] = char(nameLetter);
    }

    if (yValue > maxThreshold && !yJoyMoved) {
      yJoyMoved = true;

      if (nameLetter < 122) {
        nameLetter++;
      }
      else {
        nameLetter = 97;
      }
      lcd.print(char(nameLetter));
      playerName[enterNameCursor] = char(nameLetter);
    }
    if ( yValue > minThreshold && yValue < maxThreshold) {
      yJoyMoved = false;
    }
  }
}

void choosePosition() {
  int xValue = analogRead(xPin);
  if (millis() - lastChanged > debounceInterval) {
    lastChanged = millis();
    if (xValue < minThreshold && !xJoyMoved) {
      xJoyMoved = true;

      if (enterNameCursor > 0) {
        enterNameCursor--;
      }
    }

    if (xValue > maxThreshold && !xJoyMoved) {
      xJoyMoved = true;

      if (enterNameCursor < maxNameLength) {
        enterNameCursor++;
      }
    }
    if ( xValue > minThreshold && xValue < maxThreshold) {
      xJoyMoved = false;
    }
  }
}


void setNewHighscore(int score) {
  int i;
  for (i = 0; i < topPlayersSize; i++) {
    if (score > highscore[i]) {
      for (int j = topPlayersSize - 1; j > i; j--) {
        highscore[j] = highscore[j - 1];
        topPlayers[j] = topPlayers[j - 1] ;
      }
      highscore[i] = score;
      enterPlayerName();
      topPlayers[i] = playerName;
      break;
    }
  }

  updateTopPlayers();
  updateHighScore();
}

void updateHighScore() {
  for (int i = 0; i <  topPlayersSize; i++) {
    writeIntIntoEEPROM(highscoreAddresses[i], highscore[i]);
    highscoreMenuOptions[i + 1] = String(i + 1) + "." +  topPlayers[i] + " -> " + highscore[i];
  }
}

void readHighScore() {
  for (int i = 0; i <  topPlayersSize; i++) {
    highscore[i] = readIntFromEEPROM(highscoreAddresses[i]);
  }
}


void updateTopPlayers() {
  for (int i = 0; i <  topPlayersSize; i++) {
    writeStringToEEPROM(topPlayersAddresses[i], topPlayers[i]);
  }
}

void readTopPlayers() {
  for (int i = 0; i <  topPlayersSize; i++) {
    topPlayers[i] = readStringFromEEPROM(topPlayersAddresses[i]);
  }
}


void initializeGame(int level) {
  minScore = highscore[4];
  score = 0;
  if (level == 1) {
    guessTime = 10000;
    scoreStep = 5;
  }
  else if (level == 2) {
    guessTime = 9000;
    scoreStep = 10;
  }
  else if (level == 3) {
    guessTime = 8000;
    scoreStep = 20;
  }
  lives = 3;
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("The game");
  lcd.setCursor(3, 1);
  lcd.print("starts in...");
  countdown();
  lcd.clear();
  gameOver = 0;
  timeBarLength = 12;
  startTime = millis();
  initGameDisplay();
  createSequence();
}

void newRound() {
  delay(1000);
  gameOver = 0;
  timeBarLength = 12;
  startTime = millis();
  displayRemainingTime();
  createSequence();
  timeExpired = 0;
}

void startGame() {
  if (!gameStarted) {
    initializeGame(level);
    gameStarted = 1;
  }
  if (!gameOver) {
    while (!moves.isEmpty()) {
      decreasingTime();
      char userMove = moveJoystick();
      if (userMove != 'n' || timeExpired) {
        if (!timeExpired) {
          displayMove(userMove);
        }
        char correctMove = moves.dequeue();
        if (userMove != correctMove || timeExpired ) {
          gameOver = 1;
          for (int row = 0; row < matrixSize; row++) {
            lc.setRow(0, row, wrongMatrixByte[row]);
          }
          delay(1000);
          break;
        }
      }
    }
    if (gameOver) {
      decreasingLives();
    }
    if (moves.isEmpty() && !gameOver) {
      for (int row = 0; row < matrixSize; row++) {
        lc.setRow(0, row, checkMatrixByte[row]);
      }
      increasingScore();
      newRound();
    }
  }
}

void initGameDisplay() {
  lcd.setCursor(0, 0);
  lcd.write(byte(3));
  lcd.print(lives);
  lcd.setCursor(6, 0);
  lcd.write(byte(6));
  lcd.print(score);
  lcd.setCursor(11, 0);
  lcd.print("Lvl:");
  lcd.setCursor(15, 0);
  lcd.print(level);
  lcd.setCursor(0, 1);
  lcd.write(byte(5));
  displayRemainingTime();
}

void displayRemainingTime() {
  for (int i = 2; i < timeBarLength + 2; i++) {
    lcd.setCursor(i, 1);
    lcd.write(byte(4));
  }
  for (int i = timeBarLength + 2; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.print(" ");
  }
}

void decreasingLives() {
  if (lives > 1) {
    lives--;
    lcd.setCursor(1, 0);
    lcd.print(lives);
    newRound();
  }
  else {
    gameStarted = 0;
    gameOver = 1;
    lcd.clear();
    if (score > minScore) {
      lcd.setCursor(1, 0);
      lcd.print("New Highscore");
      lcd.setCursor(4, 1);
      lcd.print("Score :");
      lcd.print(score);
      delay(1500);
      setNewHighscore(score);
      //updateDisplay(menuState);
    }
    else {
      lcd.setCursor(2, 0);
      lcd.print("Game over :(");
      lcd.setCursor(4, 1);
      lcd.print("Score :");
      lcd.print(score);
      menuState = "principal";
      while (moves.isEmpty()) {
        moves.dequeue();
      }
      delay(1500);
      showMenu(principalMenuSize, principalMenuCursor, principalMenuOptions, menuState);
    }


  }
}

void increasingScore() {
  score += scoreStep;
  lcd.setCursor(7, 0);
  lcd.print(score);
}

void decreasingTime() {
  if (millis() - startTime < guessTime &&  millis() - lastBarDecrease >= decreaseTimeBarInterval) {
    if (timeBarLength > 0) {
      timeBarLength --;
      lastBarDecrease = millis();
      displayRemainingTime();
    }
  }
  else if (millis() - startTime > guessTime && !gameOver) {
    timeExpired = 1;
    decreasingLives();
  }
}

void displayMove(char dir) {
  lc.clearDisplay(0);
  delay(300);
  if (dir == 'u') {
    for (int row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, upMatrixByte[row]);
    }
  }
  if (dir == 'd') {
    for (int row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, downMatrixByte[row]);
    }
  }
  if (dir == 'l') {
    for (int row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, leftMatrixByte[row]);
    }
  }
  if (dir == 'r') {
    for (int row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, rightMatrixByte[row]);
    }
  }
  if (dir == '?') {
    for (int row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, questionMatrixByte[row]);
    }
  }
}

void createSequence() {
  while (!moves.isEmpty()) {
    moves.dequeue();
  }
  for (int i = 0; i < noOfMoves; i++) {
    delay(800);
    char dir = directions[random(noOfDirections)];
    moves.enqueue(dir);
    displayMove(dir);
  }
  delay(800);
  displayMove('?');
}

void countdown() {
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, threeMatrixByte[row]);
  }
  delay(800);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, twoMatrixByte[row]);
  }
  delay(800);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, oneMatrixByte[row]);
  }
  delay(800);
}


void matrixIntro() {
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, upMatrixByte[row]);
  }
  delay(800);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, leftMatrixByte[row]);
  }
  delay(800);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, downMatrixByte[row]);
  }
  delay(800);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, rightMatrixByte[row]);
  }
  delay(800);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, questionMatrixByte[row]);
  }
  delay(800);
}

void generateFood() {
  // lastFoodPos = currentPos;
  // newFoodPos = random(ceva);
  // matrix[lastFoodPos] = 0;
  // matrix[newFoodPos] = 1;
  matrixChanged = true;
}



char moveJoystick() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  if (millis() - lastChanged > debounceInterval) {
    lastChanged = millis();
    if (xValue < minThreshold && yValue > minThreshold && yValue < maxThreshold && !joyMoved) {
      joyMoved = true;
      return 'l';
    }

    if (xValue > maxThreshold && yValue > minThreshold && yValue < maxThreshold && !joyMoved) {
      joyMoved = true;
      return 'r';
    }

    if (yValue > maxThreshold && xValue > minThreshold && xValue < maxThreshold && !joyMoved) {
      joyMoved = true;
      return 'd';
    }

    if (yValue < minThreshold && xValue > minThreshold && xValue < maxThreshold && !joyMoved) {
      joyMoved = true;
      return 'u';
    }
    if ( yValue > minThreshold && yValue < maxThreshold && xValue > minThreshold && xValue < maxThreshold) {
      joyMoved = false;
    }
  }

  return 'n';
}





byte noOfLCDColumns = 16;


bool bothArrows = false;
bool upArrow = false;
bool downArrow = true;

void writeArrows() {
  if (bothArrows) {
    lcd.setCursor(noOfLCDColumns - 1, 0);
    lcd.write(byte(2));
    lcd.setCursor(noOfLCDColumns - 1, 1);
    lcd.write(byte(1));
  }
  else if (downArrow) {
    lcd.setCursor(noOfLCDColumns - 1, 0);
    lcd.write(byte(0));
    lcd.setCursor(noOfLCDColumns - 1, 1);
    lcd.write(byte(1));
  }
  else if (upArrow) {
    lcd.setCursor(noOfLCDColumns - 1, 0);
    lcd.write(byte(2));
    lcd.setCursor(noOfLCDColumns - 1, 1);
    lcd.write(byte(0));
  }
}

void menuInitialize() {
  showMenu(principalMenuSize, principalMenuCursor,  principalMenuOptions,  menuState);
  menuInitialized = 1;
}

void lcdIntro() {
  analogWrite(contrastPin, 130);
  lcd.setCursor(4, 0);
  lcd.print("Simon");
  lcd.setCursor(7, 1);
  lcd.print("says");
  lcdIntroPrinted = true;
}

int difficultyCursor = 1;

void chooseDifficulty() {
  int yValue = analogRead(yPin);
  if (millis() - lastChanged > debounceInterval) {
    lastChanged = millis();
    if (yValue < minThreshold && !joyMoved) {
      joyMoved = true;

      if (difficultyCursor > 1) {
        difficultyCursor--;
      }
    }

    if (yValue > maxThreshold && !joyMoved) {
      joyMoved = true;

      if (difficultyCursor < 3) {
        difficultyCursor++;
      }
    }
    if ( yValue > minThreshold && yValue < maxThreshold) {
      joyMoved = false;
    }
  }

  if (level != difficultyCursor) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Set difficulty");
    if (difficultyCursor == 1) {
      lcd.setCursor(0, 1);
      lcd.print(">EASY");
    }
    else if (difficultyCursor == 2) {
      lcd.setCursor(0, 1);
      lcd.print(">MEDIUM");
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print(">HARD");
    }
    level = difficultyCursor;
  }
}

void showMenu(byte menuSize, byte menuCursor, String menuOptions[], volatile String menuState) {
  if (menuState != "principal" && menuCursor == 0) {
    lcd.setCursor(0, 0);
    lcd.print(menuOptions[menuCursor]);
    lcd.setCursor(1, 1);
    lcd.print(menuOptions[menuCursor + 1]);
  }
  else if (menuCursor < menuSize - 1) {
    lcd.setCursor(0, 0);
    lcd.print('>' + scrollText(menuOptions[menuCursor]));
    lcd.setCursor(1, 1);
    lcd.print(menuOptions[menuCursor + 1]);
    lcd.setCursor(0, 1);
  }
  else {
    lcd.setCursor(1, 0);
    lcd.print(menuOptions[menuCursor - 1]);
    lcd.setCursor(0, 1);
    lcd.print('>' +  scrollText(menuOptions[menuCursor]));
    lcd.setCursor(0, 1);
  }

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
  writeArrows();
}

byte moveMenuCursor(byte menuSize, byte yPos) {
  int yValue = analogRead(yPin);
  if (millis() - lastChanged > debounceInterval) {
    lastChanged = millis();
    if (yValue < minThreshold && !joyMoved) {
      joyMoved = true;

      if (yPos > 0) {
        yPos--;
      }
    }

    if (yValue > maxThreshold && !joyMoved) {
      joyMoved = true;

      if (yPos < menuSize - 1) {
        yPos++;
      }
    }
    if ( yValue > minThreshold && yValue < maxThreshold) {
      joyMoved = false;
    }
  }
  return yPos;
}

unsigned long long elapsedTime = 0;
unsigned int changeInterval = 600;
int letter = 0;
byte menuPositionChanged = 0;
int previousLetter = 0;

void restartScrolling() {
  letter = 0;
  elapsedTime = 0;
}

String scrollText(String textToBeScrolled) {

  if (textToBeScrolled.length() > 14) {
    if (letter >= textToBeScrolled.length() - 13 || menuPositionChanged) {
      Serial.println(menuPositionChanged);
      restartScrolling();
      menuPositionChanged = 0;
    }
    if (letter <= textToBeScrolled.length() - 14) {
      if (millis() - elapsedTime > changeInterval) {
        previousLetter = letter;
        letter ++;
        elapsedTime = millis();
      }
      return textPadding(letter, textToBeScrolled);
    }
  }
  else {
    previousLetter = 0;
    letter = 0;
  }
  return textToBeScrolled;
}

String textPadding(int firstLetter, String textToBePadded) {
  String paddedText = "";
  for (int letter = firstLetter; letter <= firstLetter + 14; letter++) {
    paddedText += textToBePadded[letter];
  }
  return paddedText;
}

void updateDisplay(String menuState) {
  if (menuState == "principal") {
    menuSize =  principalMenuSize;
    menuCursor =  principalMenuCursor;
    menuYPos =  principalYPos;
  }
  else if (menuState == "about") {
    menuSize =  aboutMenuSize;
    menuCursor =  aboutMenuCursor;
    menuYPos =  aboutYPos;
  }
  else if (menuState == "settings") {
    menuSize =  settingsMenuSize;
    menuCursor =  settingsMenuCursor;
    menuYPos =  settingsYPos;
  }
  else if (menuState == "highscore") {
    menuSize =  highscoreMenuSize;
    menuCursor =  highscoreMenuCursor;
    menuYPos =  highscoreYPos;
  }
  int currentPosition = moveMenuCursor(menuSize, menuYPos);
  menuYPos = currentPosition;
  if (menuCursor != currentPosition) {
    menuPositionChanged = 1;
  }
  if (menuCursor != currentPosition || menuState != previousMenuState || (previousLetter != letter)) {
    menuCursor = currentPosition;
    lcd.clear();

    if (menuState == "principal") {
      principalMenuCursor = menuCursor;
      principalYPos = menuYPos;
      showMenu(menuSize, menuCursor, principalMenuOptions, menuState);
    }
    else if (menuState == "about") {
      aboutMenuCursor = menuCursor;
      aboutYPos = menuYPos;
      showMenu(menuSize, menuCursor, aboutMenuOptions, menuState);
    }
    else if (menuState == "settings") {
      settingsMenuCursor = menuCursor;
      settingsYPos = menuYPos;
      showMenu(menuSize, menuCursor, settingsMenuOptions, menuState);
    }
    else if (menuState == "highscore") {
      highscoreMenuCursor = menuCursor;
      highscoreYPos = menuYPos;
      showMenu(menuSize, menuCursor, highscoreMenuOptions, menuState);
    }
    previousMenuState = menuState;
  }
}
