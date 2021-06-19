#include <Wire.h>
#include <math.h>
#include "rgb_lcd.h"

#define LED 2
#define BUZZER 7
#define EOL '\n'
#define MAX_DISPLAY_COLUMN 15
#define BAUD 9600
#define SEPARATOR ':'
rgb_lcd lcd;

const int B = 4275; // B value of the thermistor
const int R0 = 100000; // R0 = 100k
const int pinTempSensor = A0; // Grove - Temperature Sensor connect to A0
int lcdBackgroundColor[] = {255, 255, 0};

void setup()
{
  lcd.begin(16, 2);
  pinMode(LED, OUTPUT);

  Serial.begin(BAUD);
  lcd.setCursor(0, 0);
  lcd.cursor();
  lcd.blink();
  lcd.setRGB(lcdBackgroundColor[0],
             lcdBackgroundColor[1],
             lcdBackgroundColor[2]);
  lcd.print("Hi!");
  delay(1500);
}

void blinkLed()
{
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}

void beepBuzzer(int wait)
{
  digitalWrite(BUZZER, HIGH);
  delay(wait);
  digitalWrite(BUZZER, LOW);
}

void setupBacklightColor(int red, int green, int blue)
{
  lcd.setRGB(red, green, blue);
}

float getTemperature()
{
  int a = analogRead(pinTempSensor);
  float R = 1023.0 / a - 1.0;
  R = R0 * R;
  return (1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15);
}

void loop()
{
  delay(500);

  if (Serial.available() > 0)
  {
    char input = Serial.read();
    switch (input)
    {
      case 'T':
        Serial.println(getTemperature());
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print((String)getTemperature() + " :)");
        break;
      case 'B':
        blinkLed();
        beepBuzzer(35);
        break;
      case '#':
        lcd.clear();
        input = Serial.read();

        for (int i = 0; input != EOL; i++)
        {
          if (i == MAX_DISPLAY_COLUMN)
          {
            lcd.print('-');
            lcd.setCursor(0, 1);
          }
          lcd.print(input);
          delay(35);
          beepBuzzer(35);

          input = Serial.read();
        }
        break;
      case 'C':
        int currentSeparator = 0;
        String value = "";
        while (input != EOL)
        {
          input = Serial.read();
          value += input;

          if (input == SEPARATOR)
          {
            lcdBackgroundColor[currentSeparator] = (int)value.toInt();
            value = "";
            currentSeparator++;
          }
        }
        lcdBackgroundColor[2] = (int)value.toInt();
        setupBacklightColor(lcdBackgroundColor[0],
                            lcdBackgroundColor[1],
                            lcdBackgroundColor[2]);
        break;
    }
  }
}
