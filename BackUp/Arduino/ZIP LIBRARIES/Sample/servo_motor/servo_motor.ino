// servo motor sample code

#include <Servo.h>
Servo myservo;

void setup() {
  myservo.attach(9); // assume control signal connected to pin 9
}

void loop() {
  myservo.write(0); // 9 o'clock position
  delay(1000);
  myservo.write(90); // 12 o'clock position
  delay(1000);
  myservo.write(180); // 3 o'clock position
  delay(1000);
}


