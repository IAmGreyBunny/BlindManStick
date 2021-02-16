// HC05 (Bluetooth module) sample code (AT command mode)

#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Enter AT command & click Send...");
  mySerial.begin(9600);

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH); // EN = HIGH to enter "AT command mode"
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}


