#pragma once
#include <ArduinoQueue.h>
#include "matrix.h"
#include "joystick.h"
#include "buzzer.h"
#include "globals.h"


//depending on the difficulty, the game details are established
void gameInitialize(int currentLevel) {
  level = currentLevel;
  if (level == 1) {
    guessTime = 12000;
    scoreStep = 1;
    moveDelay = 600;
  }
  else if (level == 2) {
    guessTime = 10000;
    scoreStep = 5;
    moveDelay = 500;
  }
  else if (level == 3) {
    guessTime = 9000;
    scoreStep = 10;
    moveDelay = 400;
  }
  sequenceLength = 1;
  lives = 3;
  score = 0;
  remainingTime = guessTime;
  decreaseTimeBarInterval = float(guessTime) / float(TIME_BAR_LENGTH);
  gameNotOver = true;
  timeExpired = false;
  lastTimeDecrease = millis();
  for (byte i = 0 ; i < TOP_PLAYERS_SIZE; i++) {
    highscore[i] = readIntFromEEPROM(highscoreAddresses[i]);
    playersNames[i] = readStringFromEEPROM(topPlayersAddresses[i]);
  }
  losed = false;
  winned = false;
}


//starting with a sequence of legth 1,
//the function adds an arrow (randomly chosen) when the user has made a correct guess,
//increasing the sequnece's length
void addMove() {
  if (sequenceLength < SONG_LENGTH) {
    int x = random(-1, 2);
    xMoves[sequenceLength - 1] = x;
    int y = 0;
    if (x != 0) {
      y = 0;
    }
    else {
      while (y == 0) {
        y = random(-1, 2);
      }
    }
    yMoves[sequenceLength - 1] = y;
  }
}

//display every arrow in the sequence and buzz the coresponding note of the song
void showSequence() {
  melodyIndex = 0;
  for (byte i = 0; i < sequenceLength; i++) {
    displayMove(xMoves[i], yMoves[i], moveDelay, true);
    if (!soundOff) {
      buzz(melodyIndex, song);
      melodyIndex++;
    }
  }
  melodyIndex = 0;
  printQuestionMark();
}



void createSequence() {
  melodyIndex = 0;
  int x = random(-1, 2);
  xMoves[sequenceLength - 1] = x;
  int y = 0;
  if (x != 0) {
    y = 0;
  }
  else {
    while (y == 0) {
      y = random(-1, 2);
    }
  }
  yMoves[sequenceLength - 1] = y;
  showSequence();
}


bool checkUserMove(int x, int y, int index) {
  return (x == xMoves[index] && y == yMoves[index]);
}



void newRound() {
  showSequence();
  remainingTime = guessTime;
  timeExpired = false;
}



void decreaseLives() {
  lives--;
  remainingTime = guessTime;
  if (lives) {
    updateGame(lives, remainingTime, score);
  }
  else {
    gameNotOver = false;
  }
}


void gameOver() {
  gameStarted = false;
  gameCreated = false;
  //new highscore
  if (score > highscore[TOP_PLAYERS_SIZE - 1]) {
    happyFace();
    winningDisplay(score);
    winned = true;
    finalScore = score;
  }
  else { //game over
    sadFace();
    losingDisplay(score);
    losed = true;
  }
}

void decreaseTime() {
  int decrStep = guessTime / BAR_LENGTH;
  if (millis() - lastTimeDecrease >= decrStep) {
    remainingTime -= decrStep;
    if (remainingTime <= 0) {
      timeExpired = true;
    }
    else {
      int x = remainingTime / decrStep;
      updateGame(lives, x, score);
    }
    lastTimeDecrease = millis();
  }
}


void startGame() {
  if (gameNotOver) {
    if (moveIndex != sequenceLength && sequenceLength < SONG_LENGTH) {
      decreaseTime();
      int x = xMoveJoystick(0, -1, 1, false);
      int y = yMoveJoystick(0, -1, 1, false);
      if (x != 0 || y != 0 || timeExpired) {
        displayMove(x, y, moveDelay, false);
        if (!soundOff) {
          buzz(melodyIndex, song);
          melodyIndex++;
        }
        bool userIsCorrect = checkUserMove(x, y, moveIndex);
        if (!userIsCorrect || timeExpired) {
          if (!soundOff) {
            wrongSoundEffect();
          }
          printWrong();
          decreaseLives();
          if (lives == 0) {
            gameOver();
          }
          else {
            moveIndex = 0;
            newRound();
          }
        }
        else if (userIsCorrect) {
          moveIndex++;
        }
      }
    }
    if (moveIndex == sequenceLength && gameNotOver) {
      moveIndex = 0;
      printCorrect();
      score += scoreStep;
      sequenceLength++;
      addMove();
      updateGame(lives, remainingTime, score);
      newRound();
    }
  }
}
