#include <WiFi.h>
WiFiServer espServer(80);

#include "time.h"

const char* ssid = "VIVOFIBRA-E248";
const char* password = "4C39C6681F";

const int LED_PIN = 13;
int ledState = LOW;

String request;
boolean currentLineIsBlank = true;

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
  pinMode(LED_PIN,OUTPUT);
  
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
          digitalWrite(LED_PIN, HIGH);
        }

        if (request.indexOf("/off") != -1)
        {
          digitalWrite(LED_PIN, LOW);
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
  //client.flush();
  client.stop();
  Serial.println("Client disconnected");
  Serial.print("\n");
}
