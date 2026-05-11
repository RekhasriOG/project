#include <WiFi.h>
#include <Wire.h>
#include <ThingSpeak.h>
#include <Adafruit_BMP085.h>

// WiFi
const char* ssid = "POCO M3";
const char* password = "7418573315vj";

// ThingSpeak
unsigned long channelID = 3370400;
const char* apiKey = "TN8X78WRVG06SIHN";

WiFiClient client;

// BMP180 object
Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);

  // I2C init (ESP32)
  Wire.begin(21, 22);

  // BMP180 start
  if (!bmp.begin()) {
    Serial.println("BMP180 not found!");
    while (1)
      ;
  }

  Serial.println("BMP180 OK");

  // WiFi connect
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

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0;  // hPa
  float altitude = bmp.readAltitude();

  // Serial print
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | ");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa | ");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  // Send to ThingSpeak
  
  ThingSpeak.setField(7, altitude);

  ThingSpeak.writeFields(channelID, apiKey);

  delay(1000);  // ThingSpeak limit
}