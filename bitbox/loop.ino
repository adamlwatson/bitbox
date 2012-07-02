/*
 *
 *    Main Loop
 *
 */


  
void loop() {
  unsigned long time = millis();
  
  MIDI.read();

  if (gProcessTempoBeat == true) {
    handleProcessTempoBeat();
  }

  if (gProcessPatternBeat == true) {
    handleProcessPatternBeat();
  }
  

  if (gRecordState == ENABLED) {
    //recordMidiEvents();
  }
  
  if (gBtnIsPressed) {
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
        gBtnIsPressed = false;
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
  
  //xmem::setMemoryBank(0, true);
  //midi_events.insert(pair<uint16_t,seq_midimsg_t>(beat_cnt,midi));
  //if (freeMem >= MEMBANK_BYTES_LOW_THRESHOLD) {
  //serialmon << "tick     : " << beat_cnt << CRLF;
    
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

  ledOn(PIN_TEMPO_LED, global_settings.ledBrightness);
  // set up timer to turn off the led in 10ms;
  gTimer.setTimeout(5, turnOffTempoLed);
}


  
/*
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x45);
    delay(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);   
    delay(100);
  }
*/  
  
  
/*

      multimap<uint16_t,seq_midimsg_t>::iterator it;
      //std::pair<iterator, iterator> itp = midi_events.
      for (it = midi_events.begin(); it != midi_events.end(); ++it) {
        serialmon << "midi message at tick " << (*it).first << ": ";
        serialmon << (int)(*it).second.type << "," << (int)(*it).second.byte3 << CRLF;
      }
      //midi_events.erase(midi_events.begin(), midi_events.end());
      midi_events.clear();
      serialmon << "cleared memory!" << CRLF;
      serialmon << "midi_events size after: " << midi_events.size() << CRLF;
      serialmon << "free  mem after: " << xmem::getFreeMemory() << CRLF;

*/