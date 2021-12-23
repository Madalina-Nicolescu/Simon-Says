#pragma once
#include <LiquidCrystal.h>
#include "customChar.h"
#include "matrix.h"
#include "globals.h"



void photoResistorAdjust(){
  int lowThreshold = 250;
  int highThreshold = 600;
  if(!lightSettingsChanged && millis() - lastAdjust > LIGHT_ADJUSTMENT_DELAY){
    int photoCellValue =analogRead(PHOTORES_PIN);
    if(photoCellValue < lowThreshold) {
      contrast = 40;
      brightness = 40;
      matrixBrightness = 3;
    }
    else if(photoCellValue > highThreshold){
      contrast = 60;
      brightness = 255;
      matrixBrightness = 12;
    }
    else{
      contrast = 50;
      brightness = 150;
      matrixBrightness = 6;
    }
    analogWrite(CONTRAST_PIN, contrast);
    analogWrite(BRIGHTNESS_PIN, brightness);
    setMatrixBrightness(matrixBrightness);
    writeIntIntoEEPROM(CONTRAST_ADDR, contrast);
    writeIntIntoEEPROM(BRIGHTNESS_ADDR, brightness);
    writeIntIntoEEPROM(MATRIX_BRIGHTNESS_ADDR, matrixBrightness);
    lastAdjust = millis();
  }
}
