/*
 *
 *    Main Loop
 *
 */


  
void loop() {
  //uint8_t LastBtnPressDeltaMS = 

  if (gProcessBeat == true) {
    handleProcessBeat();
  }
  
  MIDI.read();

  if (gRecordState == ENABLED) {
    //recordMidiEvents();
  }
  
  if (gBtnIsPressed) {
    // make sure we haven't already handled the last button press    
    if (!gBtnPressHandled) {
      // check button after debouncing
      if ((millis() - gLastBtnPressTime) >= BTN_DEBOUNCE_DELAY) {
#if DEBUG
        serialmon << ">> handling button: " << gLastBtnPressed << CRLF;
#endif        
        handleBtnPress();        
      } else {
        
        gBtnPressHandled = true; 
        gBtnIsPressed = false;
      }
    } else {
      checkBtnUp();
    }
  } else {
    checkBtnPress();
  }
}

void handleProcessBeat() {
  gProcessBeat = false;
  gCurPulse = 0;
  gCurBeat++;
  
  //xmem::setMemoryBank(0, true);
  
  //midi_events.insert(pair<uint16_t,seq_midimsg_t>(beat_cnt,midi));
  
  //if (freeMem >= MEMBANK_BYTES_LOW_THRESHOLD) {
  
  //serialmon << "tick     : " << beat_cnt << CRLF;
  
  
  lcdout << std::move(0,1);
  lcdout << "beat: " << gCurBeat;
  
#if DEBUG
  size_t freeMem = xmem::getFreeMemory();		
  serialmon << "event map size: " << midi_events.size() << CRLF;
  serialmon << "free memory   : " << freeMem << CRLF;
#endif

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