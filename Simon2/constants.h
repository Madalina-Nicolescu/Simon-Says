#pragma once
#include "notes.h"
#define RS 13
#define ENABLE 9
#define D4 7
#define D5 6
#define D6 4
#define D7 3
//#define CONTRAST_PIN 3

#define DIN_PIN 12
#define CLOCK_PIN 11
#define LOAD_PIN 10

#define BUZZER_PIN 5

#define pinSW 2
#define xPin A0
#define yPin A1

#define MATRIX_BRIGHTNESS_ADDR 44
#define CONTRAST_ADDR 40
#define BRIGHTNESS_ADDR 42
#define DIFFICULTY_ADDR 46


#define MAX_CONTR_BRIGHT 255
#define MAX_MATRX_BRIGHT 15
#define BAR_LENGTH 12

#define TOP_PLAYERS_SIZE 5

const byte highscoreAddresses[TOP_PLAYERS_SIZE] = {
  0, 2, 4, 6, 8
};

const byte topPlayersAddresses[TOP_PLAYERS_SIZE] = {
  10, 16, 22, 28, 34
};

#define NAME_MAX_LENGTH 5

#define NOTE_SUSTAIN 20

int* highscore  = new int[TOP_PLAYERS_SIZE];;
String* playersNames = new String[TOP_PLAYERS_SIZE];
int finalScore = 0;
char playerName[NAME_MAX_LENGTH + 1] = "_____\n";


byte soundOff = 0;



#define SONG_LENGTH 26




#define  minThreshold 100
#define  maxThreshold 700
#define debounceInterval 200


#define noOfColumns 16
#define noOfLines 2

#define timeBarLength 12
