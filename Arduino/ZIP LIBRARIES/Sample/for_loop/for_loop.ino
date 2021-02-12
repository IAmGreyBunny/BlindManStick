void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  for (int i = 0; i < 5; i++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);    
  }
  delay(2000);
}


