//The project is divided into 11 headers, some of them corresponds to the hardware components,
//others keeping track of used variables

//LCD  - display the menus, different messages
//        - main functions:
//          - updateMenu (calls the logic for every different submenu and then display the submenu)
//          - showMenu (depending on the menu you are in and the menu cursor, it displays a custom design)
//          - fillMenu (fills the "options" array for the current menu)
//buzzer - emitting sounds in different moments of the game and scrolling through menus
//         - main functions:
//           - wrongSoundEffect (emits the sound effect for failure)
//           - buzz (gets an index and a song number and emits the corresponding song's note)
//eepr  - saving variables in eeprom
//        - main functions:
//          - readIntFromEEPROM
//          - writeIntToEEPROM
//          - readStringFromEEPROM
//          - writeStringToEEPROM
//          - saveScore
//joystick - navigating through menus, used for input in the game
//           - main functions:
//             - readSWState
//             - yMoveJoystick
//             - xMoveJoystick
//matrix - showing animations and displaying the game
//photoRes - adjusting contrast and brightness depending on the environment
//         - main functions:
//            - photoResistorAdjust

//constants - all the constants used
//customChars - all the custom characters created
//globals - global variables
//notes - tones used by the buzzer

//game - the game logic
//     - main functions: 
//        - addMove (adds a move to the sequence)
//        - decreaseLives
//        - decreaseTime
//        - startGame (the game flow)
//        - newRound (resets the time and shows again the sequence)

//When the project is powered up, a welcome message appears on the lcd and an animation
//is running on the matrix. After that, the main menu is displayed on the screen.
//Moving the joystick upwards and downwards, you can scroll through the menu.
//Pressing the joystick button, you access a submenu.

//Pressing "start game" will lead you to the game itself
//At the beggining of the game, you 3 lives. The game ends when you lose all of your lives
//A sequence of arrows is showed on the matrix, followed by a question mark. After the question mark display, you should reproduce the seen sequence.
//If you guess right, a check sign will be shown on the matrix. If you guess wrong or too slow, you lose one of your lives


#include "LCD.h";
#include "constants.h"
#include "eepr.h"
#include "joystick.h"
#include "photoRes.h"
#include "matrix.h"
#include "customChar.h"
#include "game.h"
#include "globals.h"

bool intro = false;
bool initialize = false;

void setup() {
  noTone(BUZZER_PIN);
}

void loop() {
  //depending on the environment, the contrast and the brightness are
  //automatically setted using a photoresistor
  photoResistorAdjust();

  if (!initialize) {
    lcdInitialize();
    matrixInitialize();
    menuInitialize();
    joystickInitialize();
    initialize = true;
  }

  //intro animations
  if (!intro) {
    lcdIntro();
    matrixIntro();
    intro = true;
  }

  delay(5);

  //if the user pressed "start Game", the game is created and
  //the game logic starts flowing
  if (menuState == "game" && gameNotOver) {
    if (!gameCreated) {
      gameInitialize(max(1, readIntFromEEPROM(DIFFICULTY_ADDR)));
      gameDisplay(max(1, readIntFromEEPROM(DIFFICULTY_ADDR)));
      createSequence();
      gameCreated = true;
    }
    startGame();
  }

  //if the switch changed its state, the user entered a different menu
  //so the menu should be updated
  if (buttonPressed) {
    fillMenu(menuState);
    buttonPressed = false;
  }

  //the game state has a different logic from
  //the others menu options
  //so the menu updates only if we are not in the game
  if (menuState != "game") {
    updateMenu();
  }
}
