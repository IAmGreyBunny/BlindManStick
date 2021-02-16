void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  int i = 0;
  while (i < 5){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    i++;
  }
  delay(2000);
}


