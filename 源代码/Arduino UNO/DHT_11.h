#ifndef DHT_11_H_INCLUDED
#define DHT_11_H_INCLUDED
#include <SoftwareSerial.h>
#include <dht11.h>

#define DHT11PIN A0

double Fahrenheit(double celsius);
double Kelvin(double celsius);
double dewPoint(double celsius, double humidity);
double dewPointFast(double celsius, double humidity);
void DHT11_Write(dht11 DHT11,SoftwareSerial mySerial);
void Work(String s,double d,SoftwareSerial mySerial);

#endif // DHT_11_H_INCLUDED
