#include "Arduino.h"

class Buzzer
{
  private:
  int buzzerPin;
  
  public:
  //Constructor
  Buzzer(int pin);

  //Getters And Setters
  int getBuzzerPin();
  void setBuzzerPin(int pin);

  //Functions
  void onVertWarning(int frequency);
  void offVertWarning();
};
