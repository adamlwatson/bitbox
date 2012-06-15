/*
 *
 *    constants and definitions
 *
 */
#ifndef CONFIG_h
#define CONFIG_h

  
  // app-related
  #define APP_NAME     "bitbox"
  #define APP_VERSION  "0.1a"
  #define DEBUG        true

  // misc
  #define CRLF "\r\n"

  // serial uart (console)
  #define SERIAL_CONSOLE_BAUD_RATE 9600
  
  // lcd
  #define LCD_LINES 2
  #define LCD_CHARS 16
  
  #define LCD_DPIN1 4
  #define LCD_DPIN2 5
  #define LCD_DPIN3 6
  #define LCD_DPIN4 7
  #define LCD_DPIN5 8
  #define LCD_DPIN6 9
  
  // midi
  #define MIDI_DPIN_IN    2
  #define MIDI_DPIN_OUT   3
  #define MIDI_BAUD_RATE  31250
  
  






#endif
