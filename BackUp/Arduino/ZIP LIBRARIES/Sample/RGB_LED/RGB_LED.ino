// RGB LED sample code

void setup() {
  pinMode(3, OUTPUT); // assume R connected to pin 3
  pinMode(5, OUTPUT); // assume G connected to pin 5
  pinMode(6, OUTPUT); // assume B connected to pin 6
}

void loop() {
  analogWrite(3, 255);
  analogWrite(5, 0);
  analogWrite(6, 255);
  // R + B = Magenta
  delay(1000);
}


