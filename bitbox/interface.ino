/*
 *
 *    Methods related to UI / Hardware Interface
 *
 *
 */


// Turn an LED on or off
void ledOn(uint8_t pin, uint8_t val) {
  analogWrite(pin, val);
}

// Turn an LED on or off
void ledOn(uint8_t pin) {
  analogWrite(pin, HIGH);
}

void ledOff(uint8_t pin) {
  analogWrite(pin, LOW);
}


// Update the LCD Display

void updateDisplay() {
  //lcdout << std::clear();
  
  lcdout << std::move(0,0);

  lcdout << (uint16_t)getCurrentBar() << "." << (unsigned long)getCurrentBeatOfBar();
  //need to revisit this to shore up usage of time signatures
  lcdout << "." << (unsigned long)getCurrentPulseOfBeat() / (PPQ/_patternSettings.beatsPerBar) + 1;
  lcdout << "   ";
  
  lcdout << std::move(0,1);
  lcdout << _globalSettings.tempoBPM << " bpm";

}




// Button Handlers

// checks all buttons for a press
void checkBtnPress() {
  uint8_t state;
  
  state = digitalReadFast(PIN_BTN_PLAY);
  if (state == HIGH) gCurBtnPressed = PLAY;

  state = digitalReadFast(PIN_BTN_STOP);
  if (state == HIGH) gCurBtnPressed = STOP;
  
  state = digitalReadFast(PIN_BTN_REC);
  if (state == HIGH) gCurBtnPressed = REC;

  state = digitalReadFast(PIN_BTN_UP);
  if (state == HIGH) gCurBtnPressed = UP;
  
  state = digitalReadFast(PIN_BTN_DOWN);
  if (state == HIGH) gCurBtnPressed = DOWN;

  state = digitalReadFast(PIN_BTN_CLEAR);
  if (state == HIGH) gCurBtnPressed = CLEAR;
  
  nop();
  if (gCurBtnPressed != NONE) {
    gBtnPressHandled = false;
    
  }

}

// checks currently pressed button for button-up event
void checkBtnUp() {
  uint8_t state;
  
  switch (gCurBtnPressed) {
    case PLAY:
      state = digitalReadFast(PIN_BTN_PLAY);
      if (state == LOW) {
        gCurBtnPressed = NONE;
        gLastBtnPressed = PLAY;
      }
      break;
    case STOP:
      state = digitalReadFast(PIN_BTN_STOP);
      if (state == LOW) {
        gCurBtnPressed = NONE;
        gLastBtnPressed = STOP;
      }
      break;
    case REC:
      state = digitalReadFast(PIN_BTN_REC);
      if (state == LOW) {
        gCurBtnPressed = NONE;
        gLastBtnPressed = REC;
      }
      break;
    case UP:
      state = digitalReadFast(PIN_BTN_UP);
      if (state == LOW) {
        gCurBtnPressed = NONE;
        gLastBtnPressed = UP;
      }
      break;
    case DOWN:
      state = digitalReadFast(PIN_BTN_DOWN);
      if (state == LOW) {
        gCurBtnPressed = NONE;
        gLastBtnPressed = DOWN;
      }
      break;
    case CLEAR:
      state = digitalReadFast(PIN_BTN_CLEAR);
      if (state == LOW) {
        gCurBtnPressed = NONE;
        gLastBtnPressed = CLEAR;
      }
      break;
  }
  
  // see if we caught a button-up
  if (gCurBtnPressed == NONE) {
    gLastBtnPressTime = millis();
  }
}


// handles the result logic for button press.
void handleBtnPress() {
  switch (gCurBtnPressed) {
    case PLAY:
      handleBtnSequencerPlay();
      break;
    case STOP:
      handleBtnSequencerStop();
      break;
    case REC:
      handleBtnSequencerRec();
      break;
    case UP:
      handleBtnUp();
      break;
    case DOWN:
      handleBtnDown();
      break;
    case CLEAR:
      handleBtnClear();
      break;
  }
  
  gBtnPressHandled = true;
  
}


