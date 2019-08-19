#include "DHT_11.h"
#include "Buzzer.h"
#include "ESP8266.h"
#include "MQ2.h"

int x = -1, m = 0;
float RO = 0, ratio = 0;
boolean Stop = false, Alarm = false;
dht11 DHT11;
SoftwareSerial mySerialWifi(5, 4); // RX, TX
//SoftwareSerial mySerial(7, 6); // RX, TX

void CUBE4_Init();

void setup()
{
  Serial.begin(9600);
  mySerialWifi.begin(9600);
  CUBE4_Init();
  Buzzer_Init();
  RO = reset_MQ2();
  ESP8266_Init(mySerialWifi);
}

void loop()
{
  ratio = get_ratio(RO);
  if (ratio < 4.5)
  {
  //  Serial.println(ratio);
    Alarm = true;
    Stop = false;
    mySerialWifi.listen();
    warning(mySerialWifi);
    //    Serial.listen();
    for (int i = 8; i <= 11; i++)
      digitalWrite(i, LOW);
    Buzzer_();
  }
  else
  {
    if (Alarm)
    {
 //     Serial.println("Stop");
      Alarm = !Alarm;
      Stop = !Stop;
      Buzzer_stop();
    }
  }
  if (Serial.available())
  {
    x = (int)Serial.read();
    switch (x)
    {
      case 0:
        if (!Alarm)
        {
          for (int i = 8; i <= 11; i++)
            if (!Stop)
              digitalWrite(i, HIGH);
            else
              digitalWrite(i, LOW);
          x = -1;
          Stop = !Stop;
        }
        break;
      case 1:
        for (int i = 8; i <= 11; i++)
          digitalWrite(i, LOW);
        mySerialWifi.listen();
        DHT11_Write(DHT11, mySerialWifi);
        x = -1;
        break;
      case 2:
        for (int i = 8; i <= 11; i++)
          digitalWrite(i, LOW);
        RO = reset_MQ2();
        break;
      default:
        if (!Stop)
          if (x % 2 == 0)
            digitalWrite(x / 2, HIGH);
          else
            digitalWrite((x - 1) / 2, LOW);
    }
  }
}

void CUBE4_Init()
{
  for (int i = 8; i <= 11; i++)
    pinMode(i, OUTPUT);
}

