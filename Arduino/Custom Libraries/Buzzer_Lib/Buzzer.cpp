#include "Arduino.h"
#include "Buzzer.h"

//Constructor
Buzzer::Buzzer(int pin)
{
  buzzerPin = pin;
  pinMode(buzzerPin,OUTPUT);
}

//Getter and setters
int Buzzer::getBuzzerPin()
{
  return buzzerPin;
}
void Buzzer::setBuzzerPin(int pin)
{
  buzzerPin = pin;
}

//Functions to play various sounds
void Buzzer::onVertWarning(int frequency)
{
  tone(buzzerPin,frequency);
}
void Buzzer::offVertWarning()
{
  noTone(buzzerPin);
}
