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
    gLastBtnPressed = PLAY;
  }
  
  state = digitalRead(PIN_BTN_STOP);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gLastBtnPressed = STOP;  
  }
  
  state = digitalRead(PIN_BTN_REC);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gLastBtnPressed = REC;
  }

  state = digitalRead(PIN_BTN_UP);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gLastBtnPressed = UP;
  }
  
  state = digitalRead(PIN_BTN_DOWN);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gLastBtnPressed = DOWN;
  }

  state = digitalRead(PIN_BTN_CLEAR);
  if (state == HIGH) {
    gBtnIsPressed = true;
    gLastBtnPressed = CLEAR;
  }
  
  if (gBtnIsPressed) {
    gBtnPressHandled = false;
  }

}

// checks currently pressed button for button-up event
void checkBtnUp() {
  uint8_t state;
  
  switch (gLastBtnPressed) {
    case PLAY:
      state = digitalRead(PIN_BTN_PLAY);
      if (state == LOW) {
        gBtnIsPressed = false;
      }
      break;
    case STOP:
      state = digitalRead(PIN_BTN_STOP);
      if (state == LOW) {
        gBtnIsPressed = false;
      }
      break;
    case REC:
      state = digitalRead(PIN_BTN_REC);
      if (state == LOW) {
        gBtnIsPressed = false;
      }
      break;
    case UP:
      state = digitalRead(PIN_BTN_UP);
      if (state == LOW) {
        gBtnIsPressed = false;
      }
      break;
    case DOWN:
      state = digitalRead(PIN_BTN_DOWN);
      if (state == LOW) {
        gBtnIsPressed = false;
      }
      break;
    case CLEAR:
      state = digitalRead(PIN_BTN_CLEAR);
      if (state == LOW) {
        gBtnIsPressed = false;
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
  
  switch (gLastBtnPressed) {
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





// LED for record state

void ledRecordOn() {
  digitalWrite(PIN_TEST_LED, HIGH);
}

void ledRecordOff() {
  digitalWrite(PIN_TEST_LED, LOW);
}

