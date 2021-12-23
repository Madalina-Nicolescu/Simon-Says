#pragma once
#include <LiquidCrystal.h>
#include "LedControl.h"

bool buttonPressed = false;
String menuState = "principal";
byte menuSize;
String* options = new String[10];
volatile byte previousCursor;
volatile byte menuCursor;
String previousState;
volatile byte previousMenuCursor;
unsigned long lastAdjust = 0;
LedControl lc = LedControl(DIN_PIN, CLOCK_PIN, LOAD_PIN, 1);
byte matrixBrightness;


byte xJoyMoved = 0;
byte yJoyMoved = 0;
volatile  unsigned long long lastChange = 0;
volatile bool gameStarted = false;
volatile bool losed = false;
volatile bool winned = false;
byte setNameCursor = 0;
bool gameNotOver = true;
volatile bool nameSetted = false;


byte lives;
int guessTime;
byte level;
int score;
byte scoreStep;
byte sequenceLength;
bool timeExpired = false;
unsigned long lastTimeDecrease;
int remainingTime;
float decreaseTimeBarInterval;
int xMoves[SONG_LENGTH];
int yMoves[SONG_LENGTH];
bool gameCreated = false;
byte melodyIndex = 0;
int moveDelay = 0;
byte moveIndex = 0;



byte difficulty;
bool displayNameScreenInitialized = false;
byte song = 1;
LiquidCrystal lcd = LiquidCrystal(RS, ENABLE, D4, D5, D6, D7);
unsigned long lastScroll = 0;
byte scrollIndex = 0;


int* highscore  = new int[TOP_PLAYERS_SIZE];;
String* playersNames = new String[TOP_PLAYERS_SIZE];
int finalScore = 0;
char playerName[NAME_MAX_LENGTH + 1] = "_____\n";


byte soundOff = 1;
byte lightSettingsChanged = 0;
int brightness;
int contrast;

const byte highscoreAddresses[TOP_PLAYERS_SIZE] = {
  0, 2, 4, 6, 8
};

const byte topPlayersAddresses[TOP_PLAYERS_SIZE] = {
  10, 16, 22, 28, 34
};
