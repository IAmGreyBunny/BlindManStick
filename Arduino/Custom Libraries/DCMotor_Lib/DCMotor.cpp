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
void DCMotor::motorOn()
{
    digitalWrite(motorPin,HIGH);
}
void DCMotor::motorOff()
{
    digitalWrite(motorPin,LOW);
}
