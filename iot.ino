#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>
#define LED 2 //connect LED to digital pin2
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0
rgb_lcd lcd;

const int colorR = 150;
const int colorG = 250;
const int colorB = 0;

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    pinMode(LED, OUTPUT);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("#FORABOLSONARO");
    delay(1500);
}

void loop() 
{
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
    delay(150);

    int a = analogRead(pinTempSensor);
   float R = 1023.0/a-1.0;
    R = R0*R;

    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(temperature);
    delay(500);
}
