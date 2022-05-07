#include "DHT.h"
#include <WiFi.h>
#define DHT11PIN 2

const char* ssid = "VIVOFIBRA-E248";
const char* password =  "4C39C6681F";

DHT dht(DHT11PIN, DHT11);
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
  server.begin();
  dht.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    float humidity;
    float temperature;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:application/json");
            client.println();
            client.print("{ \"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + " }");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /t")) {
          humidity = dht.readHumidity();
          temperature = dht.readTemperature();
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
