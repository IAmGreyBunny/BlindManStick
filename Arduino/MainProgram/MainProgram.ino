#include <UltrasonicSensor.h> //Custom Library made for ultrasonic sensors
#include <DCMotor.h>          //Custom Library made for DCMotor
#include <Buzzer.h>           //Custom Library made for Buzzer
#include <WiFiEsp.h>
#include <ThingSpeak.h>
#include <Metro.h>

//IO Pins
const int TRIG =8;
const int ECHO =9;
const int DCMOTOR = 4;
const int BUZZER = 5;
const int BUTTON = 6;
int buttonState = 0;


//Network Connection Info
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif
char ssid[] = "AirTies4920_FYRY";            // your network SSID (name)
char pass[] = "8cDF777934";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiEspClient client;

//ThingSpeak Info
unsigned long myChannelNumber = 1243750;
const char * myWriteAPIKey = "4UJ6VYPFY8NLSA4D";

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

//Other Variables
int loopCount =0;
int xObstacleCount=0;
int yObstacleCount=0;

//Metro
boolean mainLoopState = false;
boolean thingSpeakLoopState = false;
Metro mainLoopMetro = Metro(500);
Metro thingSpeakMetro = Metro(60000);

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
  //Initialise Pins
  pinMode(6,INPUT);
  //Set baud rate to 115200 and start serial connection
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  ThingSpeak.begin(client);
  
}

void loop() {

  //Connect or reconnect to wifi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
        Serial.print(".");   
      } 
      Serial.println("\nConnected.");
    }

  //Button Press
  buttonState = digitalRead(BUTTON);
  
  if(mainLoopMetro.check())
  {
    mainLoopState = !mainLoopState;
    //Gets distance from ultrasonic ranger
    horizontalDistance = horizontalUltrasonicSensor.scanDistance();
    verticalDistance = verticalUltrasonicSensor.scanDistance();
  
    //Horizontal distance detection
    if(disabledAxis.horizontal!=1)
    {
      //Checks for distance and turn on motor when necessary
      if(horizontalDistance<40){
        vibrator.motorOn();
        xObstacleCount++;
        Serial.println("HORIZONTAL WARNING");
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
        yObstacleCount++;
        Serial.println("VERTICAL WARNING");
      }else if(verticalDistance<=5)
        {
         buzzer.offVertWarning();
        }
    }
  }

  if(thingSpeakMetro.check()||(buttonState!=0))
  {
    thingSpeakLoopState = !thingSpeakLoopState; 
    //Write ThingSpeak
    //x is error code
    ThingSpeak.setField(1, xObstacleCount);
    ThingSpeak.setField(2, yObstacleCount);
    ThingSpeak.setField(3, "Test");
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      if(x == 200){
        Serial.println("Channel update successful.");
        xObstacleCount=0;
        yObstacleCount=0;
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
  }
}
