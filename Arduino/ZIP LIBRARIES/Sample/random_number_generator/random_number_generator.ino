// randome number generator sample code

void setup() {
  randomSeed(analogRead(0)); // unconnected A0 gives a "random starting point"
}

void loop() {
  int rand_no = random(10, 20); // random number from 10 to 19
  if (rand_no == 13) {
    // do something
  }
  delay(100);
}


