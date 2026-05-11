#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi
const char* ssid = "POCO M3";
const char* password = "7418573315vj";

// ThingSpeak
unsigned long channelID = 3370400;
const char* apiKey = "TN8X78WRVG06SIHN";

WiFiClient client;

// Turbidity sensor
int turbidityPin = 26;

void setup() {
  Serial.begin(9600);

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

  int adcValue = analogRead(turbidityPin);

  // Convert to voltage (NodeMCU = 3.3V)
  float voltage = adcValue * (3.3 / 1023.0);

  // Convert voltage → NTU (approx formula)
  float turbidity = -1120.4 * sq(voltage) + 5742.3 * voltage - 4352.9;

  // Limit value
  if (turbidity < 0) turbidity = 0;

  Serial.print("ADC: ");
  Serial.print(adcValue);

  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);

  Serial.print(" V | Turbidity: ");
  Serial.print(turbidity);
  Serial.println(" NTU");

  // Send to ThingSpeak
  ThingSpeak.writeField(channelID, 2, turbidity, apiKey);

  delay(1000); // ThingSpeak limit
}
