#include "Buzzer.h"

int pinBuzzer = A1;
int frequency = 350;

void Buzzer_Init()
{
  pinMode(pinBuzzer, OUTPUT);
}

void Buzzer_()
{
  for (int i = 500; i <= 1000; i++) 
  {
    tone(pinBuzzer, i);
    delay(10);
  }
}

void Buzzer_stop()
{
  noTone(pinBuzzer);
}

void warning(SoftwareSerial mySerialWifi)
{
  mySerialWifi.println("AT+CIPSTART=\"TCP\",\"123.207.162.211\",8888"); // AT+CIPSTART="TCP","192.168.1.153",9994
  delay(100);
  mySerialWifi.println("AT+CIPSEND=1");
  delay(50);
  mySerialWifi.print(0);
}

void newtone(int duration)
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  for (long i = 0; i < duration * 1000L; i += period)
  {
    digitalWrite(pinBuzzer, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(pinBuzzer, LOW);
    delayMicroseconds(pulse);
  }
}

