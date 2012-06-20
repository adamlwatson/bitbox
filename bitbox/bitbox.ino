
/* 
 *   bitbox
 *   a badass midi phrase looper!
 *
 */


/*
 *   Main Project File: Variables & Setup
 */

#include <LiquidCrystal.h>
#include <Streaming.h>
#include <ArduinoUnit.h>
#include <MIDI.h>

#include "constants.h"
#include "debugging.h"

// init the lcd library
LiquidCrystal lcd(LCD_DPIN1, LCD_DPIN2, LCD_DPIN3, LCD_DPIN4, LCD_DPIN5, LCD_DPIN6);


/*
 *    SETUP()
 *
*/

void setup() {
  // init midi library, thru enabled by default
  // http://arduino.cc/playground/Main/MIDILibraryCallbacks
  

  #if DEBUG  
    // init serial debugging port - must be on Mega2560 and have a ttl serial -> usb
    // device connected on the TX3 Pin for this to work
    Serial3.begin(SERIAL_DEBUG_CONSOLE_BAUD_RATE);
    
    dlog(CRLF);
    dlog("---------------------------------%s", CRLF);
    dlog("%s %s: boing, boom tschuck!%s", APP_NAME, APP_VERSION, CRLF);
    dlog("---------------------------------%s", CRLF);    

  #endif

  // init the midi ports on the midi shield
  pinMode(MIDI_DPIN_ENABLE, OUTPUT);
  digitalWrite(MIDI_DPIN_ENABLE, HIGH);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  
  
  // note: to disable a callback:
  // MIDI.disconnectCallbackFromType(NoteOn);
  
  lcd.begin(LCD_CHARS, LCD_LINES);  
  lcd.clear();
  
  int appname_count = (sizeof(APP_NAME) - 1) / 2;
  int appver_count = (sizeof(APP_VERSION) - 1) / 2;
  
  lcd.setCursor((LCD_CHARS / 2) - (appname_count + appver_count) - 1, 0);
  
  stpr(lcd, "stream %s", APP_VERSION);
  
  delay(1000);

  for (int pos = 0; pos < LCD_CHARS; pos++) {
    //lcd.scrollDisplayLeft();
    //delay(22);
  }

  #if DEBUG
    dlog("memory available: %d bytes%s",freeRam(), CRLF);
    dlog("MIDI_DPIN_ENABLE: %d%s", MIDI_DPIN_ENABLE, CRLF);    
  #endif
}

