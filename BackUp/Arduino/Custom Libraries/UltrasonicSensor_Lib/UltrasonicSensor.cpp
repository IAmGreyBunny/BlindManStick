#include "Arduino.h"
#include "UltrasonicSensor.h"

//Constructor
UltrasonicSensor::UltrasonicSensor(int trigPin,int echoPin)
{
  trig = trigPin;
  echo = echoPin; 
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

//Getter and Setters
int UltrasonicSensor::getTrig()
{
  return trig;
} 
void UltrasonicSensor::setTrig(int pin)
{
  trig = pin;
}
int UltrasonicSensor::getEcho()
{
  return echo;
}
void UltrasonicSensor::setEcho(int pin)
{
  echo = pin;
}

//Functions
int UltrasonicSensor::scanDistance()
{
  //Variable Declaration
  long duration,distance;

  //Trigger a pulse
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);

  //Measure distance with the echo 
  duration = pulseIn(echo,HIGH);
  distance = duration/58;

  return distance;
}
