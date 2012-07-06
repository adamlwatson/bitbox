/*
 *
 *    Main Loop
 *
 */

  
void loop() {
  unsigned long time = millis();
  
  MIDI.read();
  
  if (gSeqState == PLAYING) {
    playSeqEventsAtPulse(gSeqPos.pulse);
  }
  
  if (gProcessTempoBeat == true) {
    handleProcessTempoBeat();
  }

  if (gProcessPatternBeat == true) {
    handleProcessPatternBeat();
  }
  

  if (gRecordState == ENABLED) {
    //recordMidiEvents();
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
  
  // update the display
  if (time % UPDATE_DISPLAY_DELAY == 0) {
    updateDisplay();
  }
  
  // run global simpletimer object 1 tick
  // this handles setTimeout() callback timing
  gTimer.run();
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
