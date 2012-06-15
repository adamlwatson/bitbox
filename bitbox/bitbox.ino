/* 
 *   bitbox
 *   a badass midi phrase looper!
 *
 */


/*
 *   Main Project File: Variables & Setup
 */

#include "constants.h" //where all constants are kept

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Streaming.h>
#include <ArduinoUnit.h>

TestSuite unitTests;

test(addition) {
    assertEquals(3, 1 + 2);
}

// init the lcd library
LiquidCrystal lcd( LCD_DPIN1, LCD_DPIN2, LCD_DPIN3, LCD_DPIN4, LCD_DPIN5, LCD_DPIN6 );

// init the midi software serial line
SoftwareSerial SMidi( MIDI_DPIN_IN, MIDI_DPIN_OUT );


void setup() {
  // init serial and midi
  SMidi.begin( MIDI_BAUD_RATE ); //MIDI IN/OUT
  Serial.begin( SERIAL_CONSOLE_BAUD_RATE ); // USB hardware serial port
   
  Serial << CRLF << APP_NAME << ": boing, boom tschuck!" << CRLF;

  lcd.begin( 16, 2 );
  
  //turn lcd off and on
  lcd.noDisplay();
  lcd.display();
  
  lcd.println( APP_NAME );

}

