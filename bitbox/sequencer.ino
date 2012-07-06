/*
 *
 *    Sequencer
 *
 */


// utility

// set sequencer playhead to the beat and pulse sepcified
void setSequencerToPosition(unsigned long beat, uint8_t pulse) {
  gSeqPos.pulse = pulse;
  gSeqPos.beat = beat;
  gProcessPatternBeat = false;
}

// initialize pattern settings to default
void initSequencerPattern() {
  _patternSettings.beatUnit = DEFAULT_BEAT_UNIT;
  _patternSettings.beatsPerBar = DEFAULT_BEATS_PER_BAR;
  _patternSettings.totalBars = 8;
}


// returns the current bar number of playback position
uint16_t getCurrentBar() {
  return (uint16_t) abs(gSeqPos.beat / _patternSettings.beatsPerBar);
  
}

// getter for readability
unsigned long getCurrentBeat() {
  return gSeqPos.beat;
}

unsigned long getTotalTicksPerBar() {
  return (unsigned long)PPQ * _patternSettings.beatsPerBar;
}

// returns the current pattern position in pulses, relative to start of pattern
unsigned long getAbsoluteSeqPulse() {
  return gSeqPos.pulse + (gSeqPos.beat * PPQ);
}



bool isRunRecording() {
#if DEBUG
  serialmon << gSeqState << " : " << gRecordState << CRLF;
#endif
  
  if ((gSeqState == PLAYING) && (gRecordState == ENABLED))
    return true;
  else
    return false;
}


void recordSeqEvent(byte type, byte channel, byte note, byte velocity) {
  
  xmem::setMemoryBank(0, true);
  SEQ_MIDIMSG_T msg = SEQ_MIDIMSG_T(type, channel, note, velocity);
  
  
  gMidiEvents.insert(pair<uint16_t,SEQ_MIDIMSG_T>(getAbsoluteSeqPulse(), msg));
  //if (freeMem >= MEMBANK_BYTES_LOW_THRESHOLD) {
  //serialmon << "tick     : " << beat_cnt << CRLF;
}




//typedef pair<multimap<uint16_t, SEQ_MIDIMSG_T>::iterator, multimap<uint16_t, SEQ_MIDIMSG_T>::iterator> EVENT_RANGE_T


void playSeqEventsAtPulse(unsigned long pulse) {
  
  pair<multimap<uint16_t, SEQ_MIDIMSG_T>::iterator, multimap<uint16_t, SEQ_MIDIMSG_T>::iterator> range = gMidiEvents.equal_range(getAbsoluteSeqPulse());
  
  multimap<uint16_t, SEQ_MIDIMSG_T>::iterator it2;
  for (it2 = range.first; it2 != range.second; ++it2)
  {
#if DEBUG
    serialmon << "midi message playing at pulse " << (*it2).first << ": ";
    serialmon /*<< (int)(*it2).second.type << "," */<< (int)(*it2).second.byte1 << "," << (int)(*it2).second.byte2 << "," << (int)(*it2).second.byte3 << CRLF;
#endif
    MIDI.sendNoteOn((*it2).second.byte1, (*it2).second.byte2, (*it2).second.byte3);

  }


}




// sequencer button handlers


void handleBtnSequencerStop() {
  gSeqState = STOPPED;
  ledOff(PIN_PLAY_LED);
  if (gLastBtnPressed == STOP) {
    setSequencerToPosition(0,0);
  }
}

// start playback from current pos
void handleBtnSequencerPlay() {
  // match up global tempo pulse with the playhead pulse
  gTempoPulse = gSeqPos.pulse;
  //start playing
  gSeqState = PLAYING;
  ledOn(PIN_PLAY_LED, _globalSettings.ledBrightness);
}

void handleBtnSequencerRec() {
  gRecordState = (gRecordState == ENABLED) ? DISABLED : ENABLED;
  // toggle state of record led
  (gRecordState == ENABLED) ? ledOn(PIN_REC_LED, _globalSettings.ledBrightness) : ledOff(PIN_REC_LED);
}

void handleBtnUp() {
  setSequencerBPM(++_globalSettings.tempoBPM);
}

void handleBtnDown() {
  setSequencerBPM(--_globalSettings.tempoBPM);
}

void handleBtnClear() {
  multimap<uint16_t, SEQ_MIDIMSG_T>::iterator it;
  //std::pair<iterator, iterator> itp = midi_events.
  for (it = gMidiEvents.begin(); it != gMidiEvents.end(); ++it) {
#if DEBUG
    serialmon << "midi message at tick " << (*it).first << ": ";
    serialmon << (int)(*it).second.type << "," << (int)(*it).second.byte1 << "," << (int)(*it).second.byte2 << "," << (int)(*it).second.byte3 << CRLF;
#endif
  }

  
}



/*
 *
 *    Timer4 Interrupt - For driving the sequencer timing
 *
 */

void setSequencerBPM( uint16_t bpm ) {
  setSequencerTimerFrequency(bpm);
}

// Calculates the frequency for Timer4, which pushes the PPQ Clock
// Note: Timer4 *only* exists on ATMega/ATMega2560
void setSequencerTimerFrequency( uint16_t bpm ) {
  float frequency = ( bpm * PPQ ) / 60;
  OCR4A = ( F_CPU / TIMER4_PRESCALER ) / frequency - 1;
}

// starts the interrupt timer for the ppq click
void sequencerTimerStart() {
  noInterrupts();
  gTempoPulse = 0;
  TCCR4A = TCCR4B = 0;
  bitWrite( TCCR4B, CS41, 1 ); // Set prescaler to 8
  bitWrite( TCCR4B, WGM42, 1 ); // CTC Mode
  setSequencerTimerFrequency( _globalSettings.tempoBPM );
  bitWrite( TIMSK4, OCIE4A, 1 ); // Enable Timer Compare Interrupt
  interrupts();
}

// stops the interrupt timer for the ppq clock
// TODO: legacy. this should be removed.
void sequencerTimerStop( void ) {
  noInterrupts();
  bitWrite( TIMSK4, OCIE4A, 0 ); // Disable Timer Compare Interrupt
  TCCR4A = TCCR4B = OCR4A = 0; // Reset frquency, mode of TCC Register
  interrupts();
}


// Interrupt service routine for Timer4
// Logic for sequencer timer...  count pulses, and beats
ISR( TIMER4_COMPA_vect ) {

  gTempoPulse++;
  if ( gTempoPulse == PPQ ) {
    gProcessTempoBeat = true;
    gTempoPulse = 0;
  }
  
  if (gSeqState == PLAYING) {
    gSeqPos.pulse++;
    if ( gSeqPos.pulse == PPQ ) {
      gProcessPatternBeat = true;
      gSeqPos.pulse = 0;
      gSeqPos.beat++;
    }
    
  }  

}







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
