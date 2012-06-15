/*
 *
 *    MIDI-related methods
 *
 */

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  SMidi.write(cmd);
  SMidi.write(pitch);
  SMidi.write(velocity);
  
  Serial << "Event | cmd: " << cmd << ", pitch: " << pitch << ", vel: " << velocity << CRLF;
}

