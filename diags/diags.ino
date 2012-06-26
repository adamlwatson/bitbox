//
// This sketch will print some of interesting predefined constants to Serial.
//
// For more information, look at
// http://electronics4dogs.blogspot.com/2011/01/arduino-predefined-constants.html

// helper macro
#define LINE(name,val) Serial3.print(name); Serial3.print("\t"); Serial3.println(val);

void setup()
{
  Serial3.begin(9600);
  
  // Compile file path (internal file of compilation proccess)
  LINE("__FILE__", __FILE__);
  
  // Current line (but in __FILE__)
  LINE("__LINE__", __LINE__);
  
  // Name of current function
  LINE("__func__", __func__);
  
  // Date of compliation
  LINE("__DATE__", __DATE__);
  
  // Time of compilation
  LINE("__TIME__", __TIME__);
  
  // Version of comilator (avr-gcc)
  LINE("__VERSION__", __VERSION__);
  
  // Version of Lib C
  LINE("__AVR_LIBC_VERSION_STRING__", __AVR_LIBC_VERSION_STRING__);
  
  // Counter
  LINE("__COUNTER__",__COUNTER__); // 0
  LINE("__COUNTER__",__COUNTER__); // 1
  LINE("__COUNTER__",__COUNTER__); // 2
  
  
  Serial.println("\nCPU:");
  
  #if defined(__AVR_ATmega168__)
    // Arduino Diecimila and older
    LINE("__AVR_ATmega168__", __AVR_ATmega168__);
  #endif
  
  #if defined(__AVR_ATmega328P__)
    // Arduino Duemilanove and Uno
    LINE("__AVR_ATmega328P__", __AVR_ATmega328P__);
  #endif
  
  #if defined(__AVR_ATmega2560__)
    // Arduino Mega 2560
    LINE("__AVR_ATmega2560__", __AVR_ATmega2560__);
  #endif
  
  #if defined(__AVR_ATmega1280__)
    // Arduino Mega
    LINE("__AVR_ATmega1280__", __AVR_ATmega1280__);
  #endif
  
  // Determine board type
  #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
    Serial.println("Regular Arduino");
  #elif defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
    Serial.println("Arduino Mega");
  #else
    Serial.println("Unknown");
  #endif
  
  
  Serial.println("\nArduino:");
  
  // Arduino SW version
  LINE("ARDUINO", ARDUINO);
  
  // Oscillator frequency
  LINE("F_CPU", F_CPU);
  
}

void loop(){}
