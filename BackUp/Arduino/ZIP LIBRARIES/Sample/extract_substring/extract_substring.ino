// This sample code shows how you can extract information from a long string of characters e.g. those from a GPS module, or an RFID reader.

// For instance, the GPS module connected to the UNO's soft serial will keep sending these:
// $GPRMC, ....
// $GPVTG, ....
// $GPGGA, ...
// $GPGSA, ...
// $GPGSV,4,1, ...
// $GPGSV,4,2, ...
// $GPGSV,4,3, ...
// $GPGSV,4,4...
// $GPGLL,0118.62850,N,10346.69356,E,...
// and we are interested in the latitude 0118.62850, and longitude 10346.69356

// You will need to know these few string functions:
// substring: see https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/substring/
// length: see https://www.arduino.cc/en/Tutorial/StringLength

// Let's try these out. Let's say the string of characters below has been sent from a GPS module to the UNO's soft serial port, and the UNO has stored it into myString.
// This sample code shows how the numbers 0118.62850 and 10346.69356 can be extracted (& printed onto the Serial Monitor
String myString = "$GPRMC, .... \n$GPVTG, .... \n$GPGGA, ... \n$GPGSA, ... \n$GPGSV,4,1, ... \n$GPGSV,4,2, ... \n$GPGSV,4,3, ... \n$GPGSV,4,4...\n"
                  "$GPGLL,0118.62850,N,10346.69356,E,...";
String lat, lon; // string variables to store the latitude & longitude

void setup() {
  Serial.begin(9600);
  while (!Serial);
  // ... other lines of code, related to GPS module, are not shown
}

void loop() {
  // ... other lines of code, related to GPS module, are not shown
  int n1, n2, n3, n4; // starting & ending indices for latitude & longitude
  int myStrLen = myString.length(); // - get the length of the string
  
  Serial.println("myString is: ");
  Serial.println(myString);
  Serial.println("--------------------------------------");
  Serial.print("The number of characters in the string is: ");
  Serial.println(myStrLen);

  int i = 0;
  while ((i < myStrLen)) {
    if (myString.substring(i, i + 6) == "GPGLL,") { // GPGLL, is 6 characters
      Serial.print("Substring (GPGLL) is found at string index :");
      Serial.println(i);
      n1 = i + 6; // starting index for latitude
    }
    if (myString.substring(i, i + 3) == ",N,") { // ,N, is 3 characters
      Serial.print("Substring (,N,) is found at string index :");
      Serial.println(i);
      n2 = i - 1; // ending index for latitude
      n3 = i + 3; // starting index for longitude
    }
    if (myString.substring(i, i + 3) == ",E,") { // ,E, is 3 characters
      Serial.print("Substring (,E,) is found at string index :");
      Serial.println(i);
      n4 = i - 1; // ending index for longitude
      break; // exit from the while loop
    }
    i++;
  }
  lat = myString.substring(n1, n2+1); // extract the latitude info
  lon = myString.substring(n3, n4+1); // extract the longitude info
  Serial.print("Latitude is: ");
  Serial.println(lat);
  Serial.print("Longitude is: ");
  Serial.println(lon);
  while (1); // stop here. Otherwise, the same answers will be printed over & over. When connected to a GPS module, the answers will change, so this line can be removed.
}
