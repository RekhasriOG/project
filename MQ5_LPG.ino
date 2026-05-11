#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi
const char* ssid = "POCO M3";
const char* password = "7418573315vj";

// ThingSpeak
unsigned long channelID =3370400;
const char* apiKey = "TN8X78WRVG06SIHN";

WiFiClient client;

// MQ-5 pin
int gasPin = 15;

// Calibration values
float RLOAD = 10.0;
float RZERO = 65.0;   // MUST calibrate

// LPG curve (approx)
float PARA = 574.25;
float PARB = 2.222;

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

  // Convert ADC → Voltage
  float voltage = adcValue * (3.3 / 4095.0);

  // Sensor resistance
  float rs = ((3.3 * RLOAD) / voltage) - RLOAD;

  // LPG PPM calculation
  float ppm = PARA * pow((rs / RZERO), -PARB);

  // Serial output
  Serial.print("ADC: ");
  Serial.print(adcValue);

  Serial.print(" | Voltage: ");
  Serial.print(voltage);

  Serial.print(" V | LPG: ");
  Serial.print(ppm);
  Serial.println(" ppm");

  // Send to ThingSpeak (Field 1)
  ThingSpeak.setField(3, ppm);
  ThingSpeak.writeFields(channelID,apiKey);

  delay(1000); // ThingSpeak limit
}