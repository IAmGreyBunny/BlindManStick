void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int val = analogRead(A3); // read brightnes sensor
  if (val > 700) { // very bright, off both LEDs
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else if (val >= 300) { // medium brightness, on one LED
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  else{ // very dim, on both LED
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);    
  }
  delay(100);
}


