/*
 *
 *    Main Loop
 *
 */


TestSuite unitTests;

// example test
test(addition) {
    assertEquals(3, 1 + 2);
}

void loop() {
  #if DEBUG
    //unitTests.run();
  #endif
  
  
  MIDI.read();
  
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
  
  
}
