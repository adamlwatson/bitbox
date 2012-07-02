/*
 *
 *    Sequencer-related button handlers
 *
 */

void handleBtnSequencerStop() {
  gSeqState = STOPPED;
  ledOff(PIN_PLAY_LED);
  if (gLastBtnPressed == STOP) {
    setSequencerToPosition(0,0);
  }
}

// set sequencer playhead to the beat and pulse sepcified
void setSequencerToPosition(unsigned long beat, uint8_t pulse) {
  gSeqPos.pulse = pulse;
  gSeqPos.beat = beat;
  gProcessPatternBeat = false;
}

// start playback from current pos
void handleBtnSequencerPlay() {
  // match up global tempo pulse with the playhead pulse
  gTempoPulse = gSeqPos.pulse;
  //start playing
  gSeqState = PLAYING;
  ledOn(PIN_PLAY_LED, global_settings.ledBrightness);
}

void handleBtnSequencerRec() {
  gRecordState = (gRecordState == ENABLED) ? DISABLED : ENABLED;
  // toggle state of record led
  (gRecordState == ENABLED) ? ledOn(PIN_REC_LED, global_settings.ledBrightness) : ledOff(PIN_REC_LED);
}

void handleBtnUp() {
  setSequencerBPM(++global_settings.tempoBPM);
}

void handleBtnDown() {
  setSequencerBPM(--global_settings.tempoBPM);
}

void handleBtnClear() {
  
}


// initialize pattern settings to default
void initSequencerPattern() {
  pattern_settings.beatUnit = DEFAULT_BEAT_UNIT;
  pattern_settings.beatsPerBar = DEFAULT_BEATS_PER_BAR;
  pattern_settings.totalBars = 8;
}


// returns the current bar number of playback position
uint16_t getCurrentBar() {
  return (uint16_t) abs(gSeqPos.beat / pattern_settings.beatsPerBar);
  
}

// getter for readability
unsigned long getCurrentBeat() {
  return gSeqPos.beat;
}

unsigned long getTotalTicksPerBar() {
  return (unsigned long)PPQ * pattern_settings.beatsPerBar;
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
  setSequencerTimerFrequency( global_settings.tempoBPM );
  bitWrite( TIMSK4, OCIE4A, 1 ); // Enable Timer Compare Interrupt
  interrupts();
}

// stops the interrupt timer for the ppq clock
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




