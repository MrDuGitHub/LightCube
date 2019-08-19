#include"ESP8266.h"

void ESP8266_Init(SoftwareSerial mySerial)
{ 
  int m=0;
  pinMode(6,OUTPUT);
  analogWrite(6,175);
  String getData;
  mySerial.println("AT+RST");
  delay(2000);
  while (m < 3)
  {
    if (mySerial.available())
    {
      getData = "";
      while (mySerial.available() > 0)
      {
        getData += char(mySerial.read());
        delay(10);
      }
      Serial.println(getData);
    }
    else
    {
      switch (m)
      {
        case 2:
          m++;
          mySerial.println("AT+CIPSTART=\"TCP\",\"123.207.162.211\",8888"); // AT+CIPSTART="TCP","192.168.1.153",9994
          break;
        case 1:
          m++;
           mySerial.println("AT+CWSAP=\"Arduino\",\"12345678\",1,3"); 
   //      mySerial.println("AT+CWSAP=\"GayHub 2.4G\",\"233___233\",1,3");  // //AT+CWSAP="GayHub 2.4G","233___233",1,3
          break;
        case 0:
          m++;
          mySerial.println("AT+CWMODE=3");
          break;
      }
      delay(2000);
    }
  }
 // Serial.println("123");
}
