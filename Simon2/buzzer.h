#include "constants.h"
#include "notes.h"

void wrongSoundEffect() {
  tone(BUZZER_PIN, NOTE_G4);
  delay(200);
  tone(BUZZER_PIN, NOTE_C4);
  delay(200);
  noTone(BUZZER_PIN);
}

void buzz(byte index, byte song) {
  noTone(BUZZER_PIN);
  if (song == 1) { //jingle bells
    int melody[SONG_LENGTH] = {
      NOTE_E5, NOTE_E5, NOTE_E5,
      NOTE_E5, NOTE_E5, NOTE_E5,
      NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
      NOTE_E5,
      NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
      NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
      NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
      NOTE_D5, NOTE_G5
    };
    byte tempo[SONG_LENGTH] = {
      8, 8, 4,
      8, 8, 4,
      8, 8, 8, 8,
      2,
      8, 8, 8, 8,
      8, 8, 8, 16, 16,
      8, 8, 8, 8,
      4, 4
    };
    tone(BUZZER_PIN, melody[index], tempo[index] * 10);
  }
  else if (song == 2) { //we wish you a merry christmas
    int melody[SONG_LENGTH] = {
      NOTE_B3,
      NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
      NOTE_D4, NOTE_D4, NOTE_D4,
      NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
      NOTE_E4, NOTE_E4, NOTE_E4,
      NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
      NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3
    };
    byte tempo[SONG_LENGTH] = {
      4,
      4, 8, 8, 8, 8,
      4, 4, 4,
      4, 8, 8, 8, 8,
      4, 4, 4,
      4, 8, 8, 8, 8,
      4, 4, 8, 8
    };
    tone(BUZZER_PIN, melody[index], tempo[index] * 10);
  }
  else {
    int melody[SONG_LENGTH] = { //santa claus is coming to town
      NOTE_G4,
      NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
      NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
      NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
      NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
      NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
      NOTE_D4, NOTE_F4
    };
    byte tempo[SONG_LENGTH] = {
      8,
      8, 8, 4, 4, 4,
      8, 8, 4, 4, 4,
      8, 8, 4, 4, 4,
      8, 8, 4, 2,
      4, 4, 4, 4,
      4, 2
    };
    tone(BUZZER_PIN, melody[index], tempo[index] * 10);
  }
}
