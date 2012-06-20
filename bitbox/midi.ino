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

void handleNoteOn (byte channel, byte note, byte velocity) {
  dlog ("handleNoteOn() channel: %s, note: %s, vel: %s%s", channel, note, velocity, CRLF);  
}

void handleNoteOff (byte channel, byte note, byte velocity) {
  dlog ("handleNoteOff() channel: %s, note: %s, vel: %s%s", channel, note, velocity, CRLF);  
}


