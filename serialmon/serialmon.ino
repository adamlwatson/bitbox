/*
 *    Utility for using an Arduino Uno into a Serial -> USB TTL Debugging Device
 *
*/


#define LED_PIN   13
#define BAUD_RATE 9600

void setup() {
  Serial.begin(BAUD_RATE);
 
  // set up onboard led for blinking during serial events
  pinMode(LED_PIN, OUTPUT);
 
}


void loop() {

}


void serialEvent() {
  digitalWrite(LED_PIN, HIGH);
  while (Serial.available()) {
    Serial.print((char)Serial.read());
  }
  
  digitalWrite(LED_PIN, LOW);
}


