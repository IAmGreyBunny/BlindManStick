#include <UltrasonicSensor.h> //Custom Library made for ultrasonic sensors
#include <DCMotor.h>          //Custom Library made for DCMotor

//Ultrasonic sensor pins
const int TRIG =8;
const int ECHO =9;
const int DCMOTOR = 4;

//Variable Declaration
int horizontalDistance; //Distance from obstacle on the horizontal axis
int verticalDistance;   //Distance from obstacle on the vertical axis

//Create two UltrasonicSensor Object, one for vertical and one for horizontal
UltrasonicSensor horizontalUltrasonicSensor(TRIG,ECHO);
UltrasonicSensor verticalUltrasonicSensor(TRIG,ECHO);

//Create a DCMotor Object 
DCMotor vibrator(DCMOTOR);

void setup() {
  //Set baud rate to 9600 and start serial connection
  Serial.begin(9600);
}

void loop() {
  //Gets distance from ultrasonic ranger
  horizontalDistance = horizontalUltrasonicSensor.scanDistance();

  //Checks for distance and turn on motor when necessary
  if(horizontalDistance<40){
    vibrator.motorOn();
  }else if(horizontalDistance>=40){
    vibrator.motorOff();
  }

  Serial.print(horizontalDistance);
  Serial.println();
  delay(500);
}
