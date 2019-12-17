#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  if (Serial.available() > 0)
  {
    char input = Serial.read();
    switch (input)
    {
    case 'T':
      Serial.println(dht.readTemperature());
      break;
    case 'H':
      Serial.println(dht.readHumidity());
      break;
    }
  }
  delay(500);
}
