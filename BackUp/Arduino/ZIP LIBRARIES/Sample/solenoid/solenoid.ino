// solenoid sample code

void setup() {
  pinMode(3, OUTPUT); // assume control signal connected to pin 13
}

void loop() {
  digitalWrite(13, HIGH); // solenoid energized
  delay(5000);
  digitalWrite(13, LOW); // solenoid de-energized
  delay(5000);
}



