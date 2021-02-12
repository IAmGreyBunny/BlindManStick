#include "Arduino.h"

class DCMotor
{
  private:
  int motorPin;

  public:
  //Constructor
  DCMotor(int pin);

  //Getter and Setters
  int getMotorPin();
  void setMotorPin(int pin);

  //Functions to turn on and off motors
  void motorOn();
  void motorOff();
};
