#include <UltrasonicSensor.h> //Custom Library made for ultrasonic sensors
#include <DCMotor.h>          //Custom Library made for DCMotor
#include <Buzzer.h>           //Custom Library made for Buzzer
#include <Setting.h>          //Custom Library made to store settings and edit

//IO Pins
const int TRIG =8;
const int ECHO =9;
const int DCMOTOR = 4;
const int BUZZER = 5;

//Variable Declaration
int horizontalDistance; //Distance from obstacle on the horizontal axis
int verticalDistance;   //Distance from obstacle on the vertical axis

//Create two UltrasonicSensor Object, one for vertical and one for horizontal
UltrasonicSensor horizontalUltrasonicSensor(TRIG,ECHO);
UltrasonicSensor verticalUltrasonicSensor(TRIG,ECHO);

//Create a DCMotor Object 
DCMotor vibrator(DCMOTOR);

//Create a Buzzer Object;
Buzzer buzzer(BUZZER);

void setup() {
  //Set baud rate to 9600 and start serial connection
  Serial.begin(9600);
  while(!Serial.available())
  {
  }
  Serial.println("Setting Request");
}

void loop() {
  //Gets distance from ultrasonic ranger
  horizontalDistance = horizontalUltrasonicSensor.scanDistance();
  verticalDistance = verticalUltrasonicSensor.scanDistance();
  
  //Concatenate together a string to send through serial comms
  String serialMessage = String(horizontalDistance) + "," + String(verticalDistance);

  //Checks for distance and turn on motor when necessary
  if(horizontalDistance<40){
    vibrator.motorOn();
  }else if(horizontalDistance>=40){
    vibrator.motorOff();
  }

  /*
   * VERTICAL DISTANCE DETECTION
  if(verticalDistance>5)
  {
    buzzer.onVertWarning();
  }else if(verticalDistance<=5)
  {
    buzzer.offVertWarning();
  }
  */
  
  Serial.print(serialMessage);
  Serial.println();
  delay(500);
}
