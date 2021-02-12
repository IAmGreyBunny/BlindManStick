// GPS module sample code

#include <SoftwareSerial.h>
SoftwareSerial GPS_Serial(4, 5); // Rx, Tx

void setup()
{
  Serial.begin(9600);
  GPS_Serial.begin(9600);
}

void loop()
{
  while (GPS_Serial.available() > 0) {
    Serial.write(GPS_Serial.read()); // Output the raw GPS data to the serial monitor
  }
}


