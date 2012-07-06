/*
 *
 *    MIDI-related methods
 *
 */
 
 
void noteOn(byte noteNum, byte velocity, byte channel) {
  MIDI.sendNoteOn(noteNum, velocity, channel);
}

void noteOff(byte noteNum, byte velocity, byte channel) {
  MIDI.sendNoteOff(noteNum, velocity, channel);
}


// MIDI Lib callback handlers

// note: also acts as note off if velocity == 0
void handleNoteOn (byte channel, byte note, byte velocity) {
#if DEBUG
  serialmon << "handleNoteOn() channel: " << (int)channel << ", ";
  serialmon << "note: " << (int)note <<  ", ";
  serialmon << "vel: " << (int)velocity << CRLF;
#endif

  if (isRunRecording()) {
#if DEBUG
    serialmon << "RECORDING EVENT!" << CRLF;
#endif  
    recordSeqEvent(0, channel, note, velocity);
  
  }

}

void handleNoteOff (byte channel, byte note, byte velocity) {
  #if DEBUG
		serialmon << "handleNoteOff() channel: " << (int)channel << ", ";
		serialmon << "note: " << (int)note <<  ", ";
		serialmon << "vel: " << (int)velocity << CRLF;
	#endif

  if (isRunRecording) {
    recordSeqEvent(0, channel, note, velocity);
  }
}




/*
 // play notes from F#-0 (0x1E) to F#-5 (0x5A):
for (int note = 0x1E; note < 0x5A; note ++) {
 //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
 sendNoteOn(0x90, note, 0x45);
 delay(100);
 //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
 sendNoteOn(0x90, note, 0x00);   
 delay(100);
}
*/  
