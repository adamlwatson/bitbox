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
  serialmon << "handleNoteOn() channel: " << (int)channel << ", ";
  serialmon << "note: " << (int)note <<  ", ";
  serialmon << "vel: " << (int)velocity << CRLF;
}

void handleNoteOff (byte channel, byte note, byte velocity) {
  serialmon << "handleNoteOff() channel: " << (int)channel << ", ";
  serialmon << "note: " << (int)note <<  ", ";
  serialmon << "vel: " << (int)velocity << CRLF;
}


