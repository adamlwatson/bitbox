

/* 
 *   bitbox
 *   a badass midi phrase looper!
 *
 */


/*
 *   Main Project File: Variables & Setup
 */

#include "constants.h"

// arduino libs
#include <MIDI.h>
#include <LiquidCrystal.h>
#include <Streaming.h>

// c++ stl
#include <iterator>
#include <string>
#include <map>
#include <serstream>
#include <lcdostream>
#include <pnew.cpp>
#include <xmem.h>


using namespace std;


// init the lcd library
LiquidCrystal lcd(LCD_DPIN1, LCD_DPIN2, LCD_DPIN3, LCD_DPIN4, LCD_DPIN5, LCD_DPIN6);
std::olcdstream lcdout(lcd);

#if DEBUG
    // init serial debugging port - must be on Mega2560 and have a ttl serial -> usb
    // device connected on the TX3 Pin for this to work
    std::ohserialstream serialmon(Serial3);
#endif


/*
 *    SETUP()
 *
*/

void setup() {
  
  lcd.begin(LCD_CHARS, LCD_LINES);
  std::olcdstream lcdout(lcd);

  #if DEBUG
    Serial3.begin(SERIAL_DEBUG_CONSOLE_BAUD_RATE);
    serialmon << CRLF << "---------------------------------" << CRLF;
    serialmon << APP_NAME << APP_VERSION << ": boing, boom tschuck!" << CRLF;
    serialmon << "---------------------------------" << CRLF;    

  #endif
  
  #if DEBUG  
    serialmon <<  "Setting up expanded memory..." << CRLF;    
  #endif
  
  xmem::begin(true);
  xmem::setMemoryBank(0, true);
  
  #if CHECK_MEM
    #if DEBUG
      serialmon << "Checking expanded memory..." << CRLF;
    #endif

    xmem::SelfTestResults results;
    results = xmem::selfTest();
    if (!results.succeeded) {
      failMemoryCheck();
    }

    #if DEBUG
      serialmon << "Memory check complete." << CRLF;
    #endif
  #endif





  #if DEBUG  
    serialmon << "Initializing MIDI..." << CRLF;    
  #endif
  
  // init the midi ports on the midi shield, thru enabled by default
  pinMode(MIDI_DPIN_ENABLE, OUTPUT);
  digitalWrite(MIDI_DPIN_ENABLE, HIGH);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);  
  // note: to disable a callback:
  // MIDI.disconnectCallbackFromType(NoteOn);
  
  lcdout << std::clear();
  
  int appname_count = (sizeof(APP_NAME) - 1) / 2;
  int appver_count = (sizeof(APP_VERSION) - 1) / 2;
  
  lcdout << std::move((LCD_CHARS / 2) - (appname_count + appver_count) - 1, 0);
  lcdout << APP_NAME << APP_VERSION;

  #if DEBUG
    serialmon << "MIDI_DPIN_ENABLE: " << MIDI_DPIN_ENABLE << CRLF;
    serialmon << "CPU Freq: " << F_CPU / 1000000 << "MHz"  <<  CRLF << CRLF;
    for(int b=0;b<MEMBANKS_TOTAL;b++) {
      xmem::setMemoryBank(b, true);
      serialmon << "Bank " << b << " Free Memory: " << xmem::getFreeMemory() << CRLF;
    }
  #endif
  
  delay(1000);
  timerStart();
}

void failMemoryCheck() {
  lcdout << std::clear();
  lcdout << "Memory Test FAIL";
 
  for(;;) {
  }
}

