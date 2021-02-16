void setup() {
  pinMode(11, OUTPUT);
}

void loop() {
  analogWrite(11, 250);
  delay(1000);
  analogWrite(11, 150);
  delay(1000);
  analogWrite(11, 50);
  delay(1000);  
}


