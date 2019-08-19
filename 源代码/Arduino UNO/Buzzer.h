#ifndef BUZZER_H_INCLUDED
#define BUZZER_H_INCLUDED
#include <Arduino.h>
#include <SoftwareSerial.h>

void Buzzer_Init();
void Buzzer_();
void newtone(int duration);
void Buzzer_stop();
void warning(SoftwareSerial mySerialWifi);
#endif // BUZZER_H_INCLUDED

