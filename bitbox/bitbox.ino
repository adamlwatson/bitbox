/* 
 *   bitbox
 *   a badass midi phrase looper!
 *
 */

// ** includes
#include "constants.h"

// arduino libs
#include <MIDI.h>
#include <LiquidCrystal.h>
#include <Streaming.h>

// ** c++ stl
#include <iterator>
#include <string>
#include <map>
#include <serstream>
#include <lcdostream>
#include <pnew.cpp>
#include <xmem.h>

using namespace std;



// ** sequencer midi message storage
struct seq_midimsg_t {
  byte  type;
  byte  byte1;
  byte  byte2;
  byte  byte3;
  
  seq_midimsg_t(const byte A, const byte B, const byte C, const byte D) :
    type(A),byte1(B),byte2(C),byte3(D) {}
};


// enum for currently pushed button
enum BUTTON_PRESSED {
  NONE,
  STOP,
  PLAY,
  REC,
  UP,
  DOWN,
  CLEAR
};

// sequencer states
enum SEQUENCER_STATE {
  STOPPED,
  PLAYING,
  PAUSED
};

enum RECORD_STATE {
  DISABLED,
  ENABLED
};

// ** beat counter
typedef std::multimap<uint16_t,seq_midimsg_t> EVENT_MAP;
EVENT_MAP		midi_events;

// ** sequencer / interrupt vars
uint16_t gBPM;
uint16_t gCurPulse; //current pulse tick of total per quarter note

// time sig
uint8_t gBeatsPerBar;
uint8_t gBeatUnit;

volatile unsigned long  gCurBeat;
volatile bool           gProcessBeat; // if true, beat process logic will happen in loop()                  

bool            gBtnIsPressed;
bool            gBtnPressHandled;
BUTTON_PRESSED  gCurBtnPressed; //enum
BUTTON_PRESSED  gLastBtnPressed; //enum
unsigned long   gLastBtnPressTime; // millis

// state for sequencer
SEQUENCER_STATE gSeqState;
// special state for record mode, since we want 'latch' behavior
RECORD_STATE gRecordState;



// ** utility macros

#define sbi( var, mask ) ( (var) |= (uint8_t) ( 1 << mask ) ) // Set Bit
#define cbi( var, mask ) ( (var) &= (uint8_t) ~( 1 << mask ) ) // Clear Bit
void volatile nop(void) { asm __volatile__ ("nop"); }



// ** lcd and serial streaming
LiquidCrystal 	lcd(LCD_DPIN1, LCD_DPIN2, LCD_DPIN3, LCD_DPIN4, LCD_DPIN5, LCD_DPIN6);
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
  
	// Init LCD  
  lcd.begin(LCD_CHARS, LCD_LINES);
  std::olcdstream lcdout(lcd);
  lcdout << std::clear();
  
  int appname_count = (sizeof(APP_NAME) - 1) / 2;
  int appver_count = (sizeof(APP_VERSION) - 1) / 2;
  
  lcdout << std::move((LCD_CHARS / 2) - (appname_count + appver_count) - 1, 0);
  lcdout << APP_NAME << " " << APP_VERSION;

  #if DEBUG
    Serial3.begin(SERIAL_DEBUG_CONSOLE_BAUD_RATE);
    serialmon << CRLF << "---------------------------------" << CRLF;
    serialmon << APP_NAME << APP_VERSION << ": boing, boom tschuck!" << CRLF;
    serialmon << "---------------------------------" << CRLF;    

  #endif
  
  // Set up memory
  
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


	// Set up MIDI
  
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
    
  // Set up hardware pins and button states
  pinMode(PIN_BTN_STOP, INPUT); digitalWrite(PIN_BTN_STOP, HIGH);
  pinMode(PIN_BTN_PLAY, INPUT); digitalWrite(PIN_BTN_PLAY, HIGH);
  pinMode(PIN_BTN_REC, INPUT);  digitalWrite(PIN_BTN_REC, HIGH);
  pinMode(PIN_BTN_UP, INPUT);  digitalWrite(PIN_BTN_UP, HIGH);
  pinMode(PIN_BTN_DOWN, INPUT);  digitalWrite(PIN_BTN_DOWN, HIGH);
  pinMode(PIN_BTN_CLEAR, INPUT);  digitalWrite(PIN_BTN_CLEAR, HIGH);
  
  gProcessBeat = false;
  gCurPulse = 0;
  gCurBeat = 0;
  gBeatsPerBar = DEFAULT_BEATS_PER_BAR;
  gBPM = DEFAULT_BPM;
  gLastBtnPressTime = millis();
  
  gLastBtnPressed = NONE;
  gLastBtnPressed = STOP;
  gBtnIsPressed = false;
  gBtnPressHandled = false;
  gSeqState = STOPPED;
  gRecordState = DISABLED;
  
  
  pinMode(PIN_TEMPO_LED, OUTPUT);
  pinMode(PIN_PLAY_LED, OUTPUT);
  pinMode(PIN_REC_LED, OUTPUT);
  
  
  delay(SPLASH_DELAY_MS);
  lcdout << std::clear();


  // Setup complete!
#if DEBUG
  serialmon << "MIDI_DPIN_ENABLE: " << MIDI_DPIN_ENABLE << CRLF;
  serialmon << "CPU Freq: " << F_CPU / 1000000 << "MHz"  <<  CRLF << CRLF;
  for(int b=0;b<MEMBANKS_TOTAL;b++) {
    xmem::setMemoryBank(b, true);
    serialmon << "Bank " << b << " Free Memory: " << xmem::getFreeMemory() << CRLF;
  }
#endif
  
  
}

void failMemoryCheck() {
  lcdout << std::clear();
  lcdout << "Memory Test FAIL";
 
  for(;;) {
  }
}

