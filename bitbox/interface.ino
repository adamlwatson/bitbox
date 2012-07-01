/*
 *
 *    Methods related to UI / Hardware Interface
 *
 *
 */


// checks all buttons for a press
void checkBtnPress() {
  uint8_t state;
  
  state = digitalRead(PIN_BTN_PLAY);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gCurBtnPressed = PLAY;
  }
  
  state = digitalRead(PIN_BTN_STOP);
  if (state == HIGH) {
    gBtnIsPressed = true;  
    gCurBtnPressed = STOP;
  }
  
  state = digitalRead(PIN_BTN_REC);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gCurBtnPressed = REC;
  }

  state = digitalRead(PIN_BTN_UP);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gCurBtnPressed = UP;
  }
  
  state = digitalRead(PIN_BTN_DOWN);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gCurBtnPressed = DOWN;
  }

  state = digitalRead(PIN_BTN_CLEAR);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gCurBtnPressed = CLEAR;
  }
  
  if (gBtnIsPressed) {
    gBtnPressHandled = false;
  }

}

// checks currently pressed button for button-up event
void checkBtnUp() {
  uint8_t state;
  
  switch (gCurBtnPressed) {
    case PLAY:
      state = digitalRead(PIN_BTN_PLAY);
      if (state == LOW) {
        gBtnIsPressed = false;
        gLastBtnPressed = PLAY;
      }
      break;
    case STOP:
      state = digitalRead(PIN_BTN_STOP);
      if (state == LOW) {
        gBtnIsPressed = false;
        gLastBtnPressed = STOP;
      }
      break;
    case REC:
      state = digitalRead(PIN_BTN_REC);
      if (state == LOW) {
        gBtnIsPressed = false;
        gLastBtnPressed = REC;
      }
      break;
    case UP:
      state = digitalRead(PIN_BTN_UP);
      if (state == LOW) {
        gBtnIsPressed = false;
        gLastBtnPressed = UP;
      }
      break;
    case DOWN:
      state = digitalRead(PIN_BTN_DOWN);
      if (state == LOW) {
        gBtnIsPressed = false;
        gLastBtnPressed = DOWN;
      }
      break;
    case CLEAR:
      state = digitalRead(PIN_BTN_CLEAR);
      if (state == LOW) {
        gBtnIsPressed = false;
        gLastBtnPressed = CLEAR;
      }
      break;
  }
  
  // see if we caught a button-up
  if (!gBtnIsPressed) {
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





// LED on / off

void ledOn(uint8_t pin) {
  digitalWrite(pin, HIGH);
}

void ledOff(uint8_t pin) {
  digitalWrite(pin, LOW);
}

