#pragma once
const byte matrixSize = 8;

const byte settingsMatrixByte[matrixSize] = {
  B01100110,
  B01100110,
  B11111111,
  B01100110,
  B01100110,
  B11111111,
  B01100110,
  B01100110
};

const byte highscoreMatrixByte[matrixSize] = {
  B00000000,
  B01000010,
  B01000010,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00111100
};

const byte logoMatrixByte[matrixSize] = {
  B11100111,
  B11000011,
  B10100101,
  B00011000,
  B00011000,
  B10100101,
  B11000011,
  B11100111
};

const byte upMatrixByte[matrixSize] = {
  B00000000,
  B00001000,
  B00011100,
  B00111110,
  B01111111,
  B00011100,
  B00011100,
  B00011100
};

const byte downMatrixByte[matrixSize] = {
  B00000000,
  B00011100,
  B00011100,
  B00011100,
  B01111111,
  B00111110,
  B00011100,
  B00001000

};


const byte rightMatrixByte[matrixSize] = {
  B00000000,
  B00001000,
  B00001100,
  B01111110,
  B01111111,
  B01111110,
  B00001100,
  B00001000
};


const byte leftMatrixByte[matrixSize] = {
  B00000000,
  B00010000,
  B00110000,
  B01111111,
  B11111111,
  B01111111,
  B00110000,
  B00010000
};

const byte threeMatrixByte[matrixSize] = {
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00011100,
  B00000110,
  B01100110,
  B00111100
};

const byte twoMatrixByte[matrixSize] = {
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00001100,
  B00110000,
  B01100000,
  B01111110
};

const byte oneMatrixByte[matrixSize] = {
  B00000000,
  B00011000,
  B00011000,
  B00111000,
  B00011000,
  B00011000,
  B00011000,
  B01111110
};

byte questionMatrixByte[matrixSize] = {
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00011100,
  B00011000,
  B00000000,
  B00011000
};

byte checkMatrixByte[matrixSize] = {
  B00000000,
  B00000001,
  B00000010,
  B00000100,
  B10001000,
  B01010000,
  B00100000,
  B00000000
};

byte sadMatrixByte[matrixSize] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

byte happyMatrixByte[matrixSize] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

byte wrongMatrixByte[matrixSize] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001
};

byte verticalLine[8] {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
};


byte downArrowChar[8] {
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
};

byte upArrowChar[8] {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
};

byte heartChar[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

byte hourglassChar[8] = {
  B11111,
  B10001,
  B10001,
  B01010,
  B00100,
  B01110,
  B10101,
  B11111
};

byte checkChar[8] = {
  0b00000,
  0b00001,
  0b00011,
  0b10110,
  0b11100,
  0b01000,
  0b00000,
  0b00000
};

byte emptyBoxChar[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b11111
};
