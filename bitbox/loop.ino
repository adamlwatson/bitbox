/*
 *
 *    Main Loop
 *
 */


struct msg {
  byte  type;
  byte  byte1;
  byte  byte2;
  byte  byte3;
  
  msg(const byte A, const byte B, const byte C, const byte D) :
    type(A),byte1(B),byte2(C),byte3(D) {}
};


uint16_t tick_cnt = 0;
std::multimap<uint16_t,msg> data;

  
void loop() {
  
  if (tick == 1) {
    xmem::setMemoryBank(0, true);
    size_t freeMem = xmem::getFreeMemory();
    
    if (freeMem >= MEMBANK_BYTES_LOW_THRESHOLD) {
      //use some memory...
      msg midi(0x07, 0x01, 0x02, abs(tick_cnt / 2));
      
      data.insert(pair<uint16_t,msg>(tick_cnt,midi));
            
      serialmon << "data size: " << data.size() << CRLF;
      serialmon << "free  mem: " << freeMem << CRLF;
    } else {
      multimap<uint16_t,msg>::iterator it;
      //std::pair<iterator, iterator> itp = data.
      for (it = data.begin(); it != data.end(); ++it) {
        serialmon << "midi message at tick " << (*it).first << ": " << (int)(*it).second.type << "," << (int)(*it).second.byte3 << CRLF;
      }
      //data.erase(data.begin(), data.end());
      data.clear();
      serialmon << "cleared memory!" << CRLF;
      serialmon << "data size after: " << data.size() << CRLF;
      serialmon << "free  mem after: " << xmem::getFreeMemory() << CRLF;

    }      
    //serialmon << "tick     : " << tick_cnt << CRLF;
    tick = 0;
    tick_cnt++;
    lcdout << std::move(0,1);
    lcdout << "tick: " << tick_cnt;
   
  }
  
  MIDI.read();
}

  
  
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
  
  
