#include <SoftwareSerial.h>

 SoftwareSerial mySerial(2, 3); // software serial RX = pin 10 -> connect to Tx of ESP01
          // software serial TX = pin 11 -> connect to resistor network, before going to Rx of ESP01

 void setup() {
   Serial.begin(9600);
   while (!Serial) {
   }
   Serial.println("Please enter AT commands...");
   mySerial.begin(9600);
 }

 void loop() {
   // This part allows you to issue AT commands from serial monitor, to test ESP01:
   if (Serial.available()) {
     // UNO receives AT commands from hardware serial/PC, and sends to software serial/ESP01.
     mySerial.write(Serial.read());
   }
   
   if (mySerial.available()) {
     // UNO receives responses from software serial/ESP01, and sends to hardware serial/PC. 
     Serial.write(mySerial.read());
   }
 }

