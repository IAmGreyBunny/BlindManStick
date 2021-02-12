#include "Arduino.h"

class UltrasonicSensor
{
  public:
  //Constructor
  UltrasonicSensor(int trigPin,int echoPin);
  
  //Getter and setters
  int getTrig();
  void setTrig(int pin);
  int getEcho();
  void setEcho(int pin);
  
  //Functions
  int scanDistance(); //Ultrasonic sensor ranges to find out the distance between obstacle and itself

  private:
  //Pins
  int trig;
  int echo;
}; 
