#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi
const char* ssid = "POCO M3";
const char* password = "7418573315vj";

// ThingSpeak
unsigned long channelID = 3370400;
const char* apiKey = "TN8X78WRVG06SIHN";

WiFiClient client;

// MQ-5 pin
int gasPin = 15;

// Calibration values (approx)
float RLOAD = 10.0;
float RZERO = 70.0;   // change after calibration

// Methane (CH4) curve approx
float PARA = 1012.7;
float PARB = 2.786;

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

  int adcValue = analogRead(gasPin);

  // ESP32 ADC → voltage
  float voltage = adcValue * (3.3 / 4095.0);

  // Sensor resistance
  float rs = ((3.3 * RLOAD) / voltage) - RLOAD;

  // Methane PPM calculation (approx)
  float ppm = PARA * pow((rs / RZERO), -PARB);

  // Print
  Serial.print("ADC: ");
  Serial.print(adcValue);

  Serial.print(" | Voltage: ");
  Serial.print(voltage);

  Serial.print(" V | Methane: ");
  Serial.print(ppm);
  Serial.println(" ppm");

  // Send to ThingSpeak (Field 1)
  ThingSpeak.setField(4, ppm);
  ThingSpeak.writeFields(channelID, apiKey);

  delay(1000); // ThingSpeak limit
}