#include <WiFi.h>
#include <FastLED.h>
WiFiServer espServer(80);

#include "time.h"

const char* ssid = "VIVOFIBRA-E248";
const char* password = "4C39C6681F";

String request;
boolean currentLineIsBlank = true;

#define LED_PIN     13
#define NUM_LEDS    23
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB


CRGB leds[NUM_LEDS];
#define DATA_PIN 13


void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup()
{
  Serial.begin(115200);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected. IP=");
  Serial.println(WiFi.localIP());

  espServer.begin(); /* Start the HTTP web Server */

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop()
{
  delay(1000);

  WiFiClient client = espServer.available(); /* Check if a client is available */

  if (!client)
  {
    return;
  }

  while (client.connected())
  {
    if (client.available())
    {
      char c = client.read();
      request += c;
      Serial.write(c);
      if (c == '\n' && currentLineIsBlank)
      {
        if (request.indexOf("/on") != -1)
        {
          turnOnByColor(CRGB::White);
        }

        if (request.indexOf("/off") != -1)
        {
          turnOnByColor(CRGB::Black);
        }

        if (request.indexOf("/b") != -1)
        {
          animateByColor(CRGB::Red);
        }

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println(); //  IMPORTANT
        break;
      }

      if (c == '\n')
      {
        currentLineIsBlank = true;
      }
      else if (c != '\r')
      {
        currentLineIsBlank = false;
      }
    }
  }

  delay(500);
  request = "";
  client.stop();
  Serial.println("Client disconnected");
  Serial.print("\n");
}

void animateByColor(struct CRGB color)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
    FastLED.show();
    delay(25);

    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void turnOnByColor(struct CRGB color)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
  }

  FastLED.show();
}
