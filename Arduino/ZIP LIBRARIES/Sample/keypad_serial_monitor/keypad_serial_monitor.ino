// keypad sample code

#include <Keypad.h>

const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns
char keys[ROWS][COLS] = { // keypad labels
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to keypad pins (from left) 1, 2, 3, 4 i.e. row pinouts
byte colPins[COLS] = {9, 8, 7}; // connect to keypad pins 5, 6, 7 i.e. column pinouts

// for hard keypad, change the previous 2 lines to these:
// byte rowPins[ROWS] = {12, 7, 8, 10};
// byte colPins[COLS] = {11, 13, 9};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Serial.println("press any key...");
}
  
void loop(){
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
  }
}
