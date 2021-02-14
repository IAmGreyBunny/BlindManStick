#include <UltrasonicSensor.h> //Custom Library made for ultrasonic sensors
#include <DCMotor.h>          //Custom Library made for DCMotor
#include <Buzzer.h>           //Custom Library made for Buzzer

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

//Settings
struct DisabledAxis
{
  int horizontal=0;
  int vertical=1;
};
int verticalWarningRange=5;
int horizontalWarningRange=40;
int vibrationStrength=100;
struct DisabledAxis disabledAxis;
String command;

void setup() {
  //Set baud rate to 115200 and start serial connection
  Serial.begin(115200);
  
}

void loop() {
  //Gets distance from ultrasonic ranger
  horizontalDistance = horizontalUltrasonicSensor.scanDistance();
  verticalDistance = verticalUltrasonicSensor.scanDistance();
  
  //Concatenate together a string to send through serial comms
  String serialMessage = "Data,"+String(horizontalDistance) + "," + String(verticalDistance);
  Serial.flush();
  if(Serial.available()>0)
  {
    command = Serial.readStringUntil('\n');
    command.trim();
    if(command=="Setting,0,0,40,5,100")
    {
      buzzer.onVertWarning();
    }
  }
  
  
  //Horizontal distance detection
  if(disabledAxis.horizontal!=1)
  {
    //Checks for distance and turn on motor when necessary
    if(horizontalDistance<40){
      vibrator.motorOn();
    }else if(horizontalDistance>=40){
      vibrator.motorOff();
    }
  }
  
  //Vertical distance detection
  if(disabledAxis.vertical!=1)
  {
    //Checks for distance and on buzzer when necessary
    if(verticalDistance>5)
    {
      buzzer.onVertWarning();
    }  else if(verticalDistance<=5)
    {
      buzzer.offVertWarning();
    }
  }
  

  Serial.println(serialMessage);
  Serial.flush();
  delay(500);
}
