#include "DHT_11.h"
#include <dht11.h>
double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

double Kelvin(double celsius)
{
  return celsius + 273.15;
}

double dewPoint(double celsius, double humidity)
{
  double A0 = 373.15 / (273.15 + celsius);
  double SUM = -7.90298 * (A0 - 1);
  SUM += 5.02808 * log10(A0);
  SUM += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / A0))) - 1) ;
  SUM += 8.1328e-3 * (pow(10, (-3.49149 * (A0 - 1))) - 1) ;
  SUM += log10(1013.246);
  double VP = pow(10, SUM - 3) * humidity;
  double T = log(VP / 0.61078); // temp var
  return (241.88 * T) / (17.558 - T);
}

double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100);
  double Td = (b * temp) / (a - temp);
  return Td;
}
void Work(String s1, double d, SoftwareSerial mySerial)
{
  String s = "", ss = "";
  int x = 0;
  int xx = (double)d;
  s = s1 + (String)xx;
  x = s.length() + 3;
  ss = "AT+CIPSEND=" + (String)x;
//  Serial.println(s);
  mySerial.println(ss);
  delay(50);
  mySerial.print(s1);
  mySerial.println(d, 2);
  delay(750);
}

void DHT11_Write(dht11 DHT11, SoftwareSerial mySerial)
{
  int chk = DHT11.read(DHT11PIN);
  mySerial.println("AT+CIPSTART=\"TCP\",\"123.207.162.211\",8888"); // AT+CIPSTART="TCP","192.168.1.153",9994
  delay(100);
  Work("Humidity (%): ", (float)DHT11.humidity, mySerial);
  Work("Temperature (oC): ", (double)DHT11.temperature, mySerial);
  Work("Temperature (oF): ", Fahrenheit(DHT11.temperature), mySerial);
  Work("Temperature (K): ", Kelvin(DHT11.temperature), mySerial);
  Work("Dew Point (oC): ", dewPoint(DHT11.temperature, DHT11.humidity), mySerial);
  Work("Dew PointFast (oC): ", dewPointFast(DHT11.temperature, DHT11.humidity), mySerial);
}

