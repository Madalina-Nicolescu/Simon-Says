const byte noOfLCDColumns = 16;
byte menuCursor = 0;
const byte menuSize = 4;

void writeArrows() {
  if (bothArrows) {
    lcd.setCursor(noOfLCDColumns - 1, 0);
    lcd.write(byte(2));
    lcd.setCursor(noOfLCDColumns - 1, 1);
    lcd.write(byte(1));
  }
  else if (downArrow) {
    lcd.setCursor(noOfLCDColumns - 1, 0);
    lcd.write(byte(0));
    lcd.setCursor(noOfLCDColumns - 1, 1);
    lcd.write(byte(1));
  }
  else if (upArrow) {
    lcd.setCursor(noOfLCDColumns - 1, 0);
    lcd.write(byte(2));
    lcd.setCursor(noOfLCDColumns - 1, 1);
    lcd.write(byte(0));
  }
}

void showMenu() {
  if (menuCursor < menuSize - 1) {
    lcd.setCursor(1, 0);
    lcd.print('>' + menuOptions[menuCursor]);
    lcd.setCursor(1, 1);
    lcd.print(menuOptions[menuCursor + 1]);
  }
  else {
    lcd.setCursor(1, 0);
    lcd.print(menuOptions[menuCursor - 1]);
    lcd.setCursor(1, 1);
    lcd.print('>' + menuOptions[menuCursor]);
  }

  if (menuCursor == 0) {
    downArrow = true;
    bothArrows = false;
    upArrow = false;
  }
  else if (menuCursor == 1) {
    downArrow = false;
    bothArrows = true;
    upArrow = false;
  }
  else {
    downArrow = false;
    bothArrows = false;
    upArrow = true;
  }
  writeArrows();
}

byte moveMenuCursor() {
  int yValue = analogRead(yPin);
  if (millis() - lastChanged > debounceInterval) {
    lastChanged = millis();
    if (yValue < minThreshold && !joyMoved) {
      joyMoved = true;

      if (yPos > 0) {
        yPos--;
      }
    }

    if (yValue > maxThreshold && !joyMoved) {
      joyMoved = true;

      if (yPos < menuSize - 1) {
        yPos++;
      }
    }
    if ( yValue > minThreshold && yValue < maxThreshold) {
      joyMoved = false;
    }
  }
  return yPos;
}

void updateDisplay(){
  if (menuCursor != moveMenuCursor()){
    menuCursor = moveMenuCursor();
    lcd.clear();
    showMenu();
  }
}
