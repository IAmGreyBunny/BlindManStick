#include <UltrasonicSensor.h> //Custom Library made for ultrasonic sensors
#include <DCMotor.h>          //Custom Library made for DCMotor
#include <Buzzer.h>           //Custom Library made for Buzzer
#include <WiFiEsp.h>
#include <ThingSpeak.h>
#include <CuteBuzzerSounds.h>

//IO Pins
#define  TRIG 8
#define  ECHO 9
#define  DCMOTOR  4
#define  BUZZER  5
#define   BUTTON  6
int buttonState = 0;

//Network Connection Info
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif
char ssid[] = "kshotspot";            //USE THIS DURING DEMO BECOS MORE STABLE,idk why too
char pass[] = "Pass1234";  
//char ssid[] = "AirTies4920_FYRY";            // your network SSID (name)
//char pass[] = "8cDF777934";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiEspClient client;

//ThingSpeak Info
unsigned long myChannelNumber = 1243750;
const char * myWriteAPIKey = "4UJ6VYPFY8NLSA4D";
const char * myReadAPIKey = "5AUO5PHME5UIQKRV";
int statusCode; //For debugging errors
int field[8] = {1,2,3,4,5,6,7,8};
String thingSpeakInput;

//Variable Declaration
byte horizontalDistance; //Distance from obstacle on the horizontal axis
byte verticalDistance;   //Distance from obstacle on the vertical axis

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

//Settings
struct DisabledAxis
{
  byte horizontal=0;
  byte vertical=1;
};
byte verticalWarningRange=5;
byte horizontalWarningRange=40;
byte vibrationStrength=100; //For Demo Purposes This Does Not Work Due To Pin Connection Not Being PWM
int buzzerFrequency=500;
struct DisabledAxis disabledAxis;
String command;
char bufferArray[50];

void setup() {
  cute.init(BUZZER);
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

  //Initialise Thingspeak
  ThingSpeak.begin(client); 

  //Get Initial Setting From Thing Speak
  thingSpeakInput = ThingSpeak.readStringField(myChannelNumber, 3);
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println(F("Connection Successful"));

    //Manipulation of String in Char Array
    Serial.print(F("ThingSpeak Input:"));
    Serial.println(thingSpeakInput);
    thingSpeakInput.toCharArray(bufferArray, 35);
    Serial.print(F("BufferArray:"));
    Serial.println(bufferArray);
    
    //Set Initial Settings
    initialSet(bufferArray); 
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  
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
  
  //Gets distance from ultrasonic ranger
  horizontalDistance = horizontalUltrasonicSensor.scanDistance();
  verticalDistance = verticalUltrasonicSensor.scanDistance();
  
  //Horizontal distance detection
  if(disabledAxis.horizontal!=1&&horizontalDistance<horizontalWarningRange)
  {
      vibrator.motorOn(vibrationStrength);
      xObstacleCount++;
      Serial.println(F("HORIZONTAL WARNING"));
  }else{
    vibrator.motorOff();
  }
  
  
  //Vertical distance detection
  if(disabledAxis.vertical!=1&&verticalDistance>verticalWarningRange)
  {
    buzzer.onVertWarning(buzzerFrequency);
    yObstacleCount++;
    Serial.println(F("VERTICAL WARNING"));
  }else
  {
    buzzer.offVertWarning();
  }
  

  if(buttonState==1||loopCount==600||statusCode!=200)
  {
    //Write ThingSpeak
    ThingSpeak.setField(1, xObstacleCount);
    ThingSpeak.setField(2, yObstacleCount);

    thingSpeakInput = ThingSpeak.readStringField(myChannelNumber, 3);
    statusCode = ThingSpeak.getLastReadStatus();
    if(statusCode == 200){
      Serial.println("200");
      //Manipulation of String in Char Array
      Serial.print(F("ThingSpeak Input:"));
      Serial.println(thingSpeakInput);
      thingSpeakInput.toCharArray(bufferArray, 35);
      Serial.print(F("BufferArray:"));
      Serial.println(bufferArray);

      //Check for new settings if any, and set to it
      checkForNewSetting(bufferArray);
      Serial.println(command+","+String(disabledAxis.horizontal)+","+String(disabledAxis.vertical)+","+String(vibrationStrength)+","+String(buzzerFrequency)+","+String(horizontalWarningRange)+","+String(verticalWarningRange));
    }
    else{
      Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
    }

    //Send new setting back to thingspeak and accompany it with an acknowledgement
    ThingSpeak.setField(3,command+","+String(disabledAxis.horizontal)+","+String(disabledAxis.vertical)+","+String(vibrationStrength)+","+String(buzzerFrequency)+","+String(horizontalWarningRange)+","+String(verticalWarningRange));
   
    
    
    statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(statusCode == 200){
      Serial.println(F("Channel update successful."));
      xObstacleCount=0;
      yObstacleCount=0;
      loopCount=0;
      cute.play(S_CONNECTION);
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(statusCode));
      loopCount=0;
      cute.play(S_SAD);
      }
    
  }


  loopCount+=1;
  delay(500);
  
}

//Check for new setting andd set if any
void checkForNewSetting(char input[])
{
  char * pch;
  pch = strtok (input,"\",.-");
  command = pch;
  for(int i = 0;pch!=NULL;i++)
  {
    if(command == "done")
    {
      Serial.println(F("No New Command"));
      break;
    }
    pch = strtok (NULL, " ,.-");
    switch(i)
    {
      case 0:
        disabledAxis.horizontal = atoi(pch);
        break;
      case 1:
        disabledAxis.vertical = atoi(pch);
        break;
      case 2:
        vibrationStrength = atoi(pch);
        break;
      case 3:
        buzzerFrequency = atoi(pch);
        break;
      case 4:
        horizontalWarningRange = atoi(pch);
        break;
      case 5:
        verticalWarningRange = atoi(pch);
        break;
    }
  }
  command = "done";
}

//Initial Settings
void initialSet(char input[])
{
  char * pch;
  pch = strtok (input,"\",.-");
  command = pch;
  for(int i = 0;pch!=NULL;i++)
  {
    pch = strtok (NULL, " ,.-");
    switch(i)
    {
      case 0:
        disabledAxis.horizontal = atoi(pch);
        break;
      case 1:
        disabledAxis.vertical = atoi(pch);
        break;
      case 2:
        vibrationStrength = atoi(pch);
        break;
      case 3:
        buzzerFrequency = atoi(pch);
        break;
      case 4:
        horizontalWarningRange = atoi(pch);
        break;
      case 5:
        verticalWarningRange = atoi(pch);
        break;
    }
  }
  command = "done";
}
