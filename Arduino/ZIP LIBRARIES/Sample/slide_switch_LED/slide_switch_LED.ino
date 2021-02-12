void setup() {
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int val = digitalRead(7);
  digitalWrite(13, val);
  delay(100);  
}


