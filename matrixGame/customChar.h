
const byte matrixSize = 8;
byte matrixByte[matrixSize] = {
  B00000000,
  B00010000,
  B00111000,
  B01000100,
  B11000110,
  B01000100,
  B00111000,
  B00010000
};

byte upMatrixByte[matrixSize] = {
  B00000000,
  B00001000,
  B00011100,
  B00111110,
  B01111111,
  B00011100,
  B00011100,
  B00011100
};

byte downMatrixByte[matrixSize] = {
  B00000000,
  B00011100,
  B00011100,
  B00011100,
  B01111111,
  B00111110,
  B00011100,
  B00001000

};


byte rightMatrixByte[matrixSize] = {
  B00000000,
  B00001000,
  B00001100,
  B01111110,
  B01111111,
  B01111110,
  B00001100,
  B00001000
};


byte leftMatrixByte[matrixSize] = {
  B00000000,
  B00010000,
  B00110000,
  B01111111,
  B11111111,
  B01111111,
  B00110000,
  B00010000
};

byte threeMatrixByte[matrixSize] = {
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00011100,
  B00000110,
  B01100110,
  B00111100
};

byte twoMatrixByte[matrixSize] = {
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00001100,
  B00110000,
  B01100000,
  B01111110
};

byte oneMatrixByte[matrixSize] = {
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

byte fullChar[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
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
