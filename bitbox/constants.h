/*
 *
 *    constants and definitions
 *
 */

// notes about interrupts:
/*
 
 USED:
 
 Interrupt    Pins      Used For
  0           2         Button Interrupts
 
 Timer        Pins      Used For
  4           6,7,8     Sequencer Timer
 
 
 INFO: 
 
 External Interrupts:
 0: Pin 2
 1: Pin 3
 2: Pin 21
 3: Pin 20
 4: Pin 19
 5: Pin 18
 
 Timers:
 Timer0: Pins 4 and 13
 Timer1: Pins 11 and 12
 Timer2: Pins 9 and10
 Timer3: Pin 2, 3 and 5
 Timer4: Pin 6, 7 and 8
 Timer5: Pin 46, 45 and 44

 
*/


#ifndef CONFIG_h
#define CONFIG_h
  
  // app-related
  #define APP_NAME                      "bitbox"
  #define APP_VERSION                   "0.1a"
  #define DEBUG                         true
  #define CHECK_MEM                     false
  #define SPLASH_DELAY_MS               1000
  // misc
  #define CRLF std::crlf

  //expanded memory
  #define MEMBANKS_TOTAL 8
  #define MEMBANK_BYTES_MAX  64 * 1024 //Single memory max. 65536 bytes.
                                       //Each bank has an 8K Heap, and 
  
  #define MEMBANK_BYTES_LOW_THRESHOLD 10 * 1024 // 8k and below reserved for heap
                                                // 2k buffer to avoid low memory conditions.
  
  // serial uart (console)
  #define SERIAL_DEBUG_CONSOLE_BAUD_RATE 9600

  // lcd
  #define LCD_LINES 2
  #define LCD_CHARS 16
  
  #define LCD_DPIN1 9
  #define LCD_DPIN2 8
  #define LCD_DPIN3 7
  #define LCD_DPIN4 6
  #define LCD_DPIN5 5
  #define LCD_DPIN6 4
  
  // midi
  #define MIDI_DPIN_IN     0
  #define MIDI_DPIN_OUT    1
  
  #if defined( __AVR_ATmega1280__ ) || defined( __AVR_ATmega2560__ )
    #define MIDI_DPIN_ENABLE 57     // PF3 = 57 ... TODO: check this assignment
  #else
    #define MIDI_DPIN_ENABLE 17
  #endif

  #define MIDI_BAUD_RATE 31250
  
  // sequencer / seq timer
  // using TIMER4 for hardware clock
	#define PPQ                   96
  #define DEFAULT_BPM           120
  #define DEFAULT_BEATS_PER_BAR 4 // time signature, upper numeric
  #define DEFAULT_BEAT_UNIT     4 // time signature, lower numeric
	#define TIMER4_PRESCALER      8
	

	// button pin mappings
	#define PIN_BTN_STOP  A6 
	#define PIN_BTN_PLAY  A7
	#define PIN_BTN_REC   A8
	#define PIN_BTN_UP    A9
	#define PIN_BTN_DOWN  A10
	#define PIN_BTN_CLEAR A11
	
  #define PIN_TEST_LED 13

  // button debouncing - how long to wait between checking for press after letting go
  #define BTN_DEBOUNCE_DELAY 100 // ms


#endif
