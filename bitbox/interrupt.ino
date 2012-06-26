/*
 *
 *    INTERRUPT CODE - For driving the sequencer timing
 *
*/

// pulse per quartner note
#define PPQ 96
#define BPM 120

#define TIMER4_PRESCALER 8

#define sbi( var, mask ) ( (var) |= (uint8_t) ( 1 << mask ) ) // Set Bit
#define cbi( var, mask ) ( (var) &= (uint8_t) ~( 1 << mask ) ) // Clear Bit

void volatile nop(void) { asm __volatile__ ("nop"); }

// Calculates the frequency for Timer4, which pushes the PPQ Clock
// Note: Timer4 *only* exists on ATMega/ATMega2560
void setFrequencyTimer4( int bpm ) {
  float frequency = ( bpm * PPQ ) / 60;
  OCR4A = ( F_CPU / TIMER4_PRESCALER ) / frequency - 1;
}

// starts the interrupt timer for the ppq click
void timerStart() {
  noInterrupts();
  TCCR4A = TCCR4B = 0;
  bitWrite( TCCR4B, CS41, 1 ); // Set prescaler to 8
  bitWrite( TCCR4B, WGM42, 1 ); // CTC Mode
  setFrequencyTimer4( BPM ); // TODO : change BPM from a constant to a variable for on-the-fly changes in timer frequency
  bitWrite( TIMSK4, OCIE4A, 1 ); // Enable Timer Compare Interrupt
  interrupts();
}

// stops the interrupt timer for the ppq clock
void timerStop( void ) {
  noInterrupts();
  bitWrite( TIMSK4, OCIE4A, 0 ); // Disable Timer Compare Interrupt
  TCCR4A = TCCR4B = OCR4A = 0; // Reset frquency, mode of TCC Register
  interrupts();
}

int i = 0;
int tick = 0;

// Interrupt service routine for Timer4
ISR( TIMER4_COMPA_vect ) {
  i++;
  if ( i >= PPQ ) {
    tick = 1;
    i = 0;
  } 
}




