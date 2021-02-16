#include <SoftwareSerial.h>

#define DEBUG true

// LED at D13 
int ledPin = 13;

// UNO's D10 connected to ESP's TX
// UNO's D11 connected to ESP's RX via resistor network
SoftwareSerial ESP01(10, 11); // RX, TX

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
  while (!Serial){
  }
  Serial.println("Starting...");
  ESP01.begin(9600);
}

void loop() {
  // Reset ESP8266, put it into mode 1 i.e. STA only, make it join hotspot / AP, establish single connection
  Serial.println("--- Reset ESP8266 ---");
  sendData("AT+RST\r\n",2000,DEBUG);
  Serial.println("--- Put it into mode 1 i.e. STA only ---");
  sendData("AT+CWMODE=1\r\n",2000,DEBUG);
  Serial.println("--- Make it join hotspot / AP ---");
  sendData("AT+CWJAP=\"AndroidAP\",\"sp470819\"\r\n",4000,DEBUG); // Change these!!!
  Serial.println("--- Establish single connection ---");
  sendData("AT+CIPMUX=0\r\n",2000,DEBUG);

  // Blink LED on board
  digitalWrite(ledPin, HIGH);
  delay(200);               
  digitalWrite(ledPin, LOW);

  // Make TCP connection
  Serial.println("--- Make TCP connection ---");
  String cmd = "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n"; // 184.106.153.149 = Thingspeak.com's IP address
  sendData(cmd,2000,DEBUG);

  // Prepare GET string
  String getStr = "GET /channels/659016/fields/1/last.csv\r\n";
  
  // Send data length & GET string
  Serial.println("--- Send data length & GET string ---");
  ESP01.print("AT+CIPSEND=");
  ESP01.println (getStr.length());
  Serial.print("AT+CIPSEND=");
  Serial.println (getStr.length());  
  delay(500);
  if( ESP01.find( ">" ) )
  { 
    Serial.print(">");
    String reply = sendData(getStr,2000,DEBUG);
    char num = reply.length();
    Serial.println("--- Actuator value from Thingspeak: ---");
    Serial.println(reply[num-10]);
    if(reply[num-10]=='0') {
       Serial.println("--- 0 => Turning off ---");
       digitalWrite(ledPin, LOW);
    }
    else {
       Serial.println("--- 1 => Turning on ---");
       digitalWrite(ledPin, HIGH);
    }
  }

/* expected to see the following response:
AT+CIPSEND=40
> 
Recv 40 bytes

SEND OK

+IPD,52:created_at,entry_id,field1
2019-11-01T06:32:48Z,9,0 ------------- the 0 (or 1) at the end can be used to turn off (or on) an LED, for example.
CLOSED
*/

  // Close connection, wait a while before repeating...
  Serial.println("--- Close connection, wait a while before repeating... ---");
  sendData("AT+CIPCLOSE",16000,DEBUG); // thingspeak needs 15 sec delay between updates
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    ESP01.print(command);
    long int time = millis();

    while( (time+timeout) > millis())
    {
      while(ESP01.available())
      {
        // "Construct" response from ESP01 as follows 
         // - this is to be displayed on Serial Monitor. 
        char c = ESP01.read(); // read the next character.
        response+=c;
      }  
    }

    if(debug)
    {
      Serial.print(response);
    }
    
    return (response);
}
