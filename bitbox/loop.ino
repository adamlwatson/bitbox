/*
 *
 *    Main Loop
 *
 */

  
void loop() {
  unsigned long time = millis();
  if ((gSeqPos.lastPulsePlayed != gSeqPos.pulse) && (gSeqState == PLAYING)) {
    
#if DEBUG
    //serialmon << "last pulse played: " << (unsigned long)gSeqPos.lastPulsePlayed;
    serialmon << " cur pulse: " << (unsigned long) gSeqPos.pulse << CRLF;
#endif
    
    // play all events since last tick played
    // need a faster processor to get sample-accurrate playback with current code
    // or investigate writing out events to be played to a buffer in ISR?
    uint8_t delta = gSeqPos.pulse - gSeqPos.lastPulsePlayed;
    for (unsigned long p = (gSeqPos.lastPulsePlayed+1); p <= gSeqPos.pulse; p++) {
      playSeqEventsAtPulse(p);
    }

    gSeqPos.lastPulsePlayed = gSeqPos.pulse;
    
  }
  

  MIDI.read();
  
  if (gProcessTempoBeat == true) {
    handleProcessTempoBeat();
  }

  if (gProcessPatternBeat == true) {
    handleProcessPatternBeat();
  }
    
  if (gCurBtnPressed != NONE) {
    // make sure we haven't already handled the last button press    
    if (!gBtnPressHandled) {
      // check button after debouncing
      if ((time - gLastBtnPressTime) >= BTN_DEBOUNCE_DELAY) {
        #if DEBUG
          serialmon << ">> handling button: " << gCurBtnPressed << CRLF;
        #endif
        handleBtnPress();        
      } else {
        //debounce the erratic input
        gBtnPressHandled = true; 
        gCurBtnPressed = NONE;
      }
    } else {
      checkBtnUp();
    }
  } else {
    checkBtnPress();
  }
  
  if (time % CHECK_ENCODER_DELAY == 0) {
    checkEncoder();
  }

  // update the display
  if (time % UPDATE_DISPLAY_DELAY == 0) {
    updateDisplay();
  }
  
  // run global simpletimer object 1 tick
  // this handles setTimeout() callback timing
  gTimer.run();
}


unsigned char pin1_prev=0;

void checkEncoder() {
  
  uint16_t pin1;
  uint16_t pin2;
  uint16_t pin3;
  
  pin1 = digitalReadFast(PIN_ENCODER_1);
  pin2 = digitalReadFast(PIN_ENCODER_2);
  pin3 = digitalReadFast(PIN_ENCODER_BTN);

  uint8_t inc = 1;

  if (!pin3) {
    inc = 10;
  }
  
  if ((!pin1) && (pin1_prev)) {
    if (pin2) {
      //clockwise
      _globalSettings.tempoBPM += inc;
    } else {
      //counter-clockwise
      _globalSettings.tempoBPM -= inc;
    }
    
    if (_globalSettings.tempoBPM >= MAX_BPM) {
      _globalSettings.tempoBPM = MAX_BPM;
    } else if (_globalSettings.tempoBPM <= MIN_BPM) {
      _globalSettings.tempoBPM = MIN_BPM;      
    }
    setSequencerBPM(_globalSettings.tempoBPM);
  }
  
  pin1_prev = pin1;
  //nop();
      
}





void handleProcessPatternBeat() {
  gProcessPatternBeat = false;
  
#if DEBUG
  size_t freeMem = xmem::getFreeMemory();		
  serialmon << "event map size: " << gMidiEvents.size() << CRLF;
  serialmon << "free memory   : " << freeMem << CRLF;
#endif

}



void turnOffTempoLed() {
  ledOff(PIN_TEMPO_LED);
}

void handleProcessTempoBeat() {
  gProcessTempoBeat = false;

  ledOn(PIN_TEMPO_LED, _globalSettings.ledBrightness * 2);
  // set up timer to turn off the led in 10ms;
  gTimer.setTimeout(5, turnOffTempoLed);

  
}
