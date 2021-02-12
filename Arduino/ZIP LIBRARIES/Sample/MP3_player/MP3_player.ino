// MP3 player sample code

#include <SoftwareSerial.h>

#define Soft_Rx 5 // connect to TX of the Serial MP3 Player module
#define Soft_Tx 6 // connect to RX of the module

SoftwareSerial mySerial(Soft_Rx, Soft_Tx);

void setup()
{
  mySerial.begin(9600);
  delay(500); // give time for chip initialization
  sendCommand(0X09, 0X02); // select the SD card
  delay(500);
}

void loop()
{
  sendCommand(0x03, 1); // play the song with index 1
  delay(10000);  
  while(1); // stop here...  
}

static int8_t Send_buf[8] = {0} ;
// The module undestands commands in an 8-int string: 
//       0X7E FF 06 command 00 b1 b2 EF; <- b1 & b2 are optional parameters
// e.g.  0X7E FF 06      03 00 00 01 EF; <- command is 03, b2 is 01, so play song with index 1
// For the list of commands, refer to: http://geekmatic.in.ua/pdf/Catalex_MP3_board.pdf

void sendCommand(int8_t command, int16_t dat) // pass in optional parameters b2 & b1 as 16-bit dat
{
  delay(20);
  Send_buf[0] = 0x7e;               // starting byte
  Send_buf[1] = 0xff;               // version
  Send_buf[2] = 0x06;               // number of bytes of the command excluding starting & ending bytes
  Send_buf[3] = command;            //
  Send_buf[4] = 0x00;               // 0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8); // data high -- construct b1 from 16-bit dat
  Send_buf[6] = (int8_t)(dat);      // data low -- construct b2 from 16-bit dat
  Send_buf[7] = 0xef;               // ending byte
  for (uint8_t i = 0; i < 8; i++)
  {
    mySerial.write(Send_buf[i]) ;   // send a byte to the module
  }
}
