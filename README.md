# Simon-Says
Arduino Matrix Game using an 8x8 matrix, a 16x2 lcd display, a joystick and a buzzer

## Task Requirements

### Menu

The principal menu consists of the following options:
- Start Game
- Highscore
- Settings
- About

The user can scroll through these options using the joystick and select one by pressing the button. 

#### Start Game
 - starts the game 
 - at the beggining of the game, the player has 3 lives. The game ends when the player loses all of their lives
 - a sequence of arrows is showed on the matrix, followed by a question mark. After the question mark display, the player shoud reproduce the seen sequence. If he guesses right, a check sign will be shown on the matrix. If he guesses wrong or too slow, he loses one of his lives
#### HighScore
 - shows  highscore board
 - when a player has a score greater than the last highscore from the top, he is asked to introduce his name on the lcd display and the highscore board updates
 - the top 5 players are stored in EEPROM memory
#### Settings
 - the user can change the difficulty of the game, the contrast and the brightness of the lcd or the brightness of the matrix
 - the values that the user set for these settings are stored in EEPROM memory
#### About
 - shows the game name, the author's name and the github link of the game repository
<br>

