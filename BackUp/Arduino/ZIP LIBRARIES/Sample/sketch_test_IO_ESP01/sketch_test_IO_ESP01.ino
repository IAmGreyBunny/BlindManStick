#include <SoftwareSerial.h>

 SoftwareSerial mySerial(10, 11); // software serial RX = pin 10 -> connect to Tx of ESP01
          // software serial TX = pin 11 -> connect to resistor network, before going to Rx of ESP01

 void setup() {
   pinMode(8, OUTPUT); // Buzzer
   pinMode(5, OUTPUT); // LED
   pinMode(7, INPUT);  // Button
                       // A0 is Potentiometer

   Serial.begin(9600);
   while (!Serial) {
   }
   Serial.println("Please press button, turn potentiometer or enter AT commands...");
   mySerial.begin(9600);
 }

 void loop() {
   // This part allows you to test the button, buzzer, potentiometer & LED:
   if (digitalRead(7)==HIGH)
     digitalWrite(8, HIGH);
   else
     digitalWrite(8, LOW); 

   int potentiometerValue = analogRead(A0); // 10-bit: 0-1023
   int LEDbrightness = potentiometerValue / 4; // 8-bit: 0-255
   analogWrite(5, LEDbrightness);


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

