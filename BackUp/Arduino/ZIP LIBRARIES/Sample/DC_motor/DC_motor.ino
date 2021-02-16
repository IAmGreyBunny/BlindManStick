// DC motor sample code

void setup() {
  pinMode(11, OUTPUT); // assume control signal connected to pin 11
}

void loop() {
  analogWrite(11, 250); // motor turns at high speed
  delay(1000);
  analogWrite(11, 150); // motor turns at medium speed
  delay(1000);
  analogWrite(11,  50); // motor turns at low speed
  delay(1000);
}


