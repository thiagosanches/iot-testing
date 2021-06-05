#include <Wire.h>
#include <math.h>
#include "rgb_lcd.h"

#define LED 2
#define BUZZER 7
#define EOL '\q' // \n on Windows or \r on Linux
#define BAUD 9600
rgb_lcd lcd;

const int B = 4275; // B value of the thermistor
const int R0 = 100000; // R0 = 100k
const int pinTempSensor = A0; // Grove - Temperature Sensor connect to A0
const int colorR = 150;
const int colorG = 250;
const int colorB = 0;

void setup()
{
  lcd.begin(16, 2);
  pinMode(LED, OUTPUT);
  lcd.setRGB(colorR, colorG, colorB);

  Serial.begin(BAUD);
  lcd.print("#FORABOLSONARO");
  delay(1500);
}

void blinkLed()
{
  digitalWrite(LED, HIGH);
  delay(150);
  digitalWrite(LED, LOW);
  delay(150);
}

void beepBuzzer()
{
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
}

void loop()
{
  int a = analogRead(pinTempSensor);
  float R = 1023.0 / a - 1.0;
  R = R0 * R;
  float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;
  delay(500);

  if (Serial.available() > 0)
  {
    char input = Serial.read();
    switch (input)
    {
      case 'T': //temperature
        Serial.println(temperature);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print((String)temperature + " Celsius");
        break;
      case 'B': //blink
        blinkLed();
        beepBuzzer();
        break;
      case '#':
        String message = "";
        input = Serial.read();
        while (input != EOL)
        {
          message += input;
          input = Serial.read();
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(message);
        break;
    }
  }
}
