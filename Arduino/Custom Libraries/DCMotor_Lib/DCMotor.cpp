#include "Arduino.h"
#include "DCMotor.h"

//Constructor
DCMotor::DCMotor(int pin)
{
    motorPin =pin;
    motorOff();
    pinMode(motorPin,OUTPUT);
}

//Getter and Setter
int DCMotor::getMotorPin()
{
    return motorPin;
}
void DCMotor::setMotorPin(int pin)
{
    motorPin = pin;
}

//Function to turn motor on and off
void DCMotor::motorOn(int percentage)
{
  int pwm;
  pwm = (percentage/100)*255;
  analogWrite(motorPin,pwm);
}
void DCMotor::motorOff()
{
  analogWrite(motorPin,0);
}
