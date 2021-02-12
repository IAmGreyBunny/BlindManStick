// tilt switch sample code

void setup() {
  pinMode(1, INPUT);
  // assume sensor output connected to pin 1
}

void loop() {
  if (digitalRead(1) == HIGH){
    // terminals shorted, do the necessary...
  }
  delay(100);
}


