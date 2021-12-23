#pragma once
#include<EEPROM.h>
#include "constants.h"
#include "globals.h"


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
  for (byte i = 0; i < len; i++)
  {
    EEPROM.update(address + 1 + i, strToWrite[i]);
  }
}

String readStringFromEEPROM(int address) {
  int newStrLen = EEPROM.read(address);
  char data[newStrLen + 1];
  for (byte i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(address + 1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}

void clearIntFromAddress(int address) {
  EEPROM.update(address, 0);
}

void clearCharFromAddress(int address) {
  EEPROM.update(address, "");
}

String readHighscorePosition(int hsPosition) {
  int score = max(0, readIntFromEEPROM(highscoreAddresses[hsPosition]));
  String playerName = readStringFromEEPROM(topPlayersAddresses[hsPosition]);
  if (playerName != "") {
    String highscoreLine = String(hsPosition + 1) + "." + playerName + " " + String(score);
    return highscoreLine;
  }
  return (String(hsPosition + 1) + "." + "EMPTY");
}

void saveScore(int score, String playerName) {

  playerName = playerName.substring(0, NAME_MAX_LENGTH);
  for (byte i = 0; i < TOP_PLAYERS_SIZE; i++)
  {
    if (score > highscore[i]) {
      for (byte j = TOP_PLAYERS_SIZE - 1; j > i; j--) {
        highscore[j] = highscore[j - 1];
        playersNames[j] = playersNames[j - 1];
      }
      highscore[i] = score;
      playersNames[i] = playerName;
      break;
    }
  }
  for (byte i = 0; i < TOP_PLAYERS_SIZE; i++) {
    writeIntIntoEEPROM(highscoreAddresses[i], highscore[i]);
    writeStringToEEPROM(topPlayersAddresses[i], playersNames[i]);
  }
}
