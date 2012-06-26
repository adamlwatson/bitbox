

/* 
 *   bitbox
 *   a badass midi phrase looper!
 *
 */


/*
 *   Main Project File: Variables & Setup
 */

#include <MIDI.h>
#include <LiquidCrystal.h>
#include <Streaming.h>
#include <ArduinoUnit.h>


#include "constants.h"

#include <xmem.h>


#include "debugging.h"




// init the lcd library
LiquidCrystal lcd(LCD_DPIN1, LCD_DPIN2, LCD_DPIN3, LCD_DPIN4, LCD_DPIN5, LCD_DPIN6);


// expanded memory buffers

byte *membuf[8];


/*
 *    SETUP()
 *
*/

// init midi library, thru enabled by default
// http://arduino.cc/playground/Main/MIDILibraryCallbacks  
void setup() {
  #if DEBUG  
    // init serial debugging port - must be on Mega2560 and have a ttl serial -> usb
    // device connected on the TX3 Pin for this to work
    Serial3.begin(SERIAL_DEBUG_CONSOLE_BAUD_RATE);
    
    dlog(CRLF);
    dlog("---------------------------------%s", CRLF);
    dlog("%s %s: boing, boom tschuck!%s", APP_NAME, APP_VERSION, CRLF);
    dlog("---------------------------------%s", CRLF);    

  #endif
    
  uint8_t  i;
  uint16_t j;

  xmem::begin(true);
  
  #if CHECK_MEM
    #if DEBUG  
      dlog("Checking expanded memory... %s", CRLF);    
    #endif

    xmem::SelfTestResults results;
    results = xmem::selfTest();
    if (!results.succeeded) {
      failMemoryCheck();
    }
  #endif

  #if DEBUG  
    dlog("Setting up expanded memory... %s", CRLF);    
  #endif
  
  for (i=0; i<8; i++) {
    xmem::setMemoryBank(i,true);
    // init bank of 54k (55,296 bytes)
    membuf[i]=(byte *) malloc(MEMBANK_TOTAL_BYTES);
  }
  
  #if DEBUG  
    dlog("Initializing MIDI... %s", CRLF);    
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
  
  stpr(lcd, "%s %s", APP_NAME, APP_VERSION);

  #if DEBUG
    dlog("MIDI_DPIN_ENABLE: %d%s", MIDI_DPIN_ENABLE, CRLF);
    dlog("CPU Freq: %dMHz%s%s", F_CPU / 1000000, CRLF, CRLF);
  #endif
  
  delay(1000);
  timerStart();
}

void failMemoryCheck() {
  lcd.clear();
  stpr(lcd, "Memory Test FAIL"); 
 
  for(;;) {
  }
}


/*
Hardware Interupt Timer5 on Mega2560 Pins:

Timer 5A: D46
Timer 5B: D45
Timer 5C: D44


T = timer period, f = clock frequency

T = 1 / f
T = 1 / 16 MHz = 1 / 2^16 Hz
T = (1 * 2^-16) s

*/
