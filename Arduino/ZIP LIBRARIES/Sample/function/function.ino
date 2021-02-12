void setup() {
  pinMode(13, OUTPUT);
}

void blink(int count){
  for (int i = 0; i < count; i++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}

void loop() {
  blink(3);
  delay(2000);
}


