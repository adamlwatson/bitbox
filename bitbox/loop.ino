/*
 *
 *    Main Loop
 *
 */

#if DEBUG

TestSuite unitTests;

// example test
test(addition) {
    assertEquals(3, 1 + 2);
}


#endif

uint8_t tick_cnt = 0;

void loop() {
  #if DEBUG
    //unitTests.run();
  #endif
  
  if (tick == 1) {
    dlog("tick: %u%s", tick_cnt, CRLF);
    tick = 0;
    tick_cnt++;
    lcd.setCursor(0,1);
    stpr(lcd, "tick: %i", tick_cnt);

  }
  
  MIDI.read();
  
  
  
}

  
  
  
  
  
/*  
  // check expanded memory
  uint8_t  i;
  uint16_t j;

  for (i=0; i<8; i++) {
    xmem::setMemoryBank(i, true);  
    for (j=0; j < MEMBANK_TOTAL_BYTES; j++) {
      if ( membuf[i][j] != 0xaa+i )
        fail();
    }
  }
*/

  
/*
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x45);
    delay(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);   
    delay(100);
  }
*/  
  
  
