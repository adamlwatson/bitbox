/*
 *
 *    Sequencer-related button handlers
 *
 */

void handleBtnSequencerStop() {
  sequencerTimerStop();
}

void handleBtnSequencerPlay() {
  sequencerTimerStart();
}

void handleBtnSequencerRec() {
  gRecordState = (gRecordState == ENABLED) ? DISABLED : ENABLED;
  serialmon << "Record State: " << gRecordState << CRLF;
}

void handleBtnUp() {

}

void handleBtnDown() {
  
}

void handleBtnClear() {
  
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
  TCCR4A = TCCR4B = 0;
  bitWrite( TCCR4B, CS41, 1 ); // Set prescaler to 8
  bitWrite( TCCR4B, WGM42, 1 ); // CTC Mode
  setSequencerTimerFrequency( gBPM ); // TODO : change BPM from a constant to a variable for on-the-fly changes in timer frequency
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
  gCurPulse++;
  if ( gCurPulse == PPQ ) {
    gProcessBeat = true;
    gCurPulse = 0;
  } 
}




