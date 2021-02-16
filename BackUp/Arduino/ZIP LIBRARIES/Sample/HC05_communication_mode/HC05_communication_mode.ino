// HC05 (Bluetooth module) sample code (communication mode)

#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("HC05 in \"communication mode\"...");
  mySerial.begin(9600);

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW); // EN = LOW to enter "communication mode"
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}



