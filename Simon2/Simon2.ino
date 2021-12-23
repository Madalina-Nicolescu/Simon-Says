#include "LCD.h";
#include "constants.h"
#include "eepr.h"
#include "joystick.h"
#include "menu.h"
#include "matrix.h"
#include "customChar.h"
#include "game.h"

bool intro = false;
bool initialize = false;

void setup() {
  noTone(BUZZER_PIN);
}


void loop() {
  if (!initialize) {
    lcdInitialize();
    matrixInitialize();
    menuInitialize();
    joystickInitialize();
    initialize = true;
  }

  delay(5);
  if (!intro) {
    lcdIntro();
    matrixIntro();
    intro = true;
  }
  if (menuState == "game" && gameNotOver) {
    if (!gameCreated) {
      gameInitialize(max(1, readIntFromEEPROM(DIFFICULTY_ADDR)));
      gameDisplay(max(1, readIntFromEEPROM(DIFFICULTY_ADDR)));
      createSequence();
      gameCreated = true;
    }
    startGame();
  }


  if (buttonPressed) {
    fillMenu(menuState);
    buttonPressed = false;
  }
  if (menuState != "game") {
    updateMenu();
  }
}
