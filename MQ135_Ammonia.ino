#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi
const char* ssid = "POCO M3";
const char* password = "7418573315vj";

// ThingSpeak
unsigned long channelID = 3370400;
const char* apiKey = "TN8X78WRVG06SIHN";

WiFiClient client;

// MQ-135 pin
int gasPin = 34;

void setup() {
  Serial.begin(9600);
  Serial.println("MQ-135 Ammonia Sensor");

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  ThingSpeak.begin(client);
}

void loop() {

  int value = analogRead(gasPin);

  Serial.print("Ammonia Value: ");
  Serial.println(value);

  // Send to ThingSpeak
  ThingSpeak.setField(6, value);
  ThingSpeak.writeFields(channelID, apiKey);

  delay(1000);
}