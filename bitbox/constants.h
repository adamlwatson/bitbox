/*
 *
 *    constants and definitions
 *
 */
#ifndef CONFIG_h
#define CONFIG_h

  
  // app-related
  #define APP_NAME                      "bitbox"
  #define APP_VERSION                   "0.1a"
  #define DEBUG                         true
  #define CHECK_MEM                     false

  // misc
  #define CRLF "\r\n"

  //expanded memory
  #define MEMBANK_TOTAL_BYTES  54 * 1024 //55296 bytes

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
    #  define MIDI_DPIN_ENABLE 57     // PF3 = 57 ... TODO: check this assignment
  #else
    #  define MIDI_DPIN_ENABLE 17
  #endif

  #define MIDI_BAUD_RATE   31250
  

#endif
