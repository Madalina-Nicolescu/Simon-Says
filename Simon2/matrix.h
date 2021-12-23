#pragma once
#include "constants.h"
#include "customChar.h"

#include "eepr.h"
#include "globals.h"


void matrixInitialize() {
  lc.shutdown(0, false); // turn off power saving, enables display
  matrixBrightness  = readIntFromEEPROM(MATRIX_BRIGHTNESS_ADDR);
  lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}

void setMatrixBrightness(byte newBrightness) {
  lc.setIntensity(0, newBrightness);
  matrixBrightness = newBrightness;
}

void printLogo() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, logoMatrixByte[row]);
  }
}

void matrixIntro() {
  if (!soundOff) {
    tone(BUZZER_PIN, NOTE_G5, 100);
  }

  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, upMatrixByte[row]);
  }
  delay(800);
  if (!soundOff) {
    tone(BUZZER_PIN, NOTE_A5, 100);
  }

  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, leftMatrixByte[row]);
  }
  delay(800);
  if (!soundOff) {
    tone(BUZZER_PIN, NOTE_B5, 100);
  }

  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, downMatrixByte[row]);
  }
  delay(800);
  if (!soundOff) {
    tone(BUZZER_PIN, NOTE_C6, 100);
  }

  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, rightMatrixByte[row]);
  }
  delay(800);
  if (!soundOff) {
    tone(BUZZER_PIN, NOTE_C6, 100);
  }

  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, treeMatrixByte[row]);
  }
  delay(800);
  printLogo();
}



void displayAll() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, B11111111);
  }
}

void printWrong() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, wrongMatrixByte[row]);
  }
  delay(800);
}
void printCorrect() {
  delay(300);
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, checkMatrixByte[row]);
  }
  delay(800);
}
void sadFace() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, sadMatrixByte[row]);
  }
}
void happyFace() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, happyMatrixByte[row]);
  }
}

void countdown() {
  if (!soundOff) {
    tone(BUZZER_PIN, 1500, 20);
  }
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, threeMatrixByte[row]);
  }
  delay(1000);
  if (!soundOff) {
    tone(BUZZER_PIN, 1500, 20);
  }
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, twoMatrixByte[row]);
  }
  delay(1000);
  if (!soundOff) {
    tone(BUZZER_PIN, 1500, 20);
  }
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, oneMatrixByte[row]);
  }
  delay(1000);
}


void displayMove(int x, int y, int moveDelay, bool applyDelay) {
  lc.clearDisplay(0);
  delay(300);
  if (x == 0 && y == -1) {
    for (byte row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, upMatrixByte[row]);
    }
  }
  else if (x == 0 && y == 1) {
    for (byte row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, downMatrixByte[row]);
    }
  }
  else if (x == 1 && y == 0) {
    for (byte row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, rightMatrixByte[row]);
    }
  }
  else if (x == -1 && y == 0) {
    for (byte row = 0; row < matrixSize; row++) {
      lc.setRow(0, row, leftMatrixByte[row]);
    }
  }
  if (applyDelay) {
    delay(moveDelay);
  }

}


void printQuestionMark() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, questionMatrixByte[row]);
  }
  delay(400);
}

void printSettingsIcon() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, settingsMatrixByte[row]);
  }
}

void printHighscoreIcon() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, highscoreMatrixByte[row]);
  }
}

void printAboutIcon() {
  for (byte row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, questionMatrixByte[row]);
  }
}
