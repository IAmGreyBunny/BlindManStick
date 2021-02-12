// RTC sample code

unsigned int ss, mm, hh, da, mo, ye; // second, minute, hour, day, month, year

void setup() {
  hh = 23; mm = 58; ss = 58; // initial time: 23:58:58 - please change accordingly
  ye = 1999; mo = 12; da = 31;// initial date: 31th Dec 1999 - please change accordingly
  Serial.begin(9600);
  while (!Serial);
}

unsigned long current_millis, previous_millis;

void loop() {
  current_millis = millis();
  if (current_millis - previous_millis >= 1000) { // 1 sec has passed
    previous_millis = current_millis; // do the necessary updates
    current_millis = millis();
    ss++; // increment second
    if (ss >= 60) {
      ss = 0;
      mm++; // increment minute
      if (mm >= 60) {
        mm = 0;
        hh++; // increment hour
        if (hh >= 24) {
          hh = 0;
          da++; // increment day
          if (((da >= 32) && ((mo == 1) || (mo == 3) || (mo == 5) || (mo == 7) || (mo == 8) || (mo == 10) || (mo == 12))) || // 31-day month
              ((da >= 31) && ((mo == 4) || (mo == 6) || (mo == 9) || (mo == 11))) || // 30-day month
              ((da >= 30) && (mo == 2) && ((ye % 4) == 0)) || // leap year
              ((da >= 29) && (mo == 2) && ((ye % 4) != 0))) { // non-leap year
            da = 1;
            mo++; // increment month
            if (mo >= 13) {
              mo = 1;
              ye++; // increment year
            }
          }
        }
      }
    }
    // print Time & Date every sec
    Serial.print("Time = ");
    if (hh < 10)
      Serial.print("0");
    Serial.print(hh);
    if (mm < 10)
      Serial.print(":0");
    else
      Serial.print(":");
    Serial.print(mm);
    if (ss < 10)
      Serial.print(":0");
    else
      Serial.print(":");
    Serial.print(ss);

    Serial.print(", Date = ");
    Serial.print(ye);
    if (mo < 10)
      Serial.print(":0");
    else
      Serial.print(":");
    Serial.print(mo);
    if (da < 10)
      Serial.print(":0");
    else
      Serial.print(":");
    Serial.println(da);
  }
  else {
    // Do other things here

  }
}

