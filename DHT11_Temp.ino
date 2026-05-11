#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

char SSID[] = "POCO M3";
char PASS[] = "7418573315vj";
char API[]  = "TN8X78WRVG06SIHN";
unsigned long ChannelID = 3370400;

WiFiClient client;   

DHT dht(4, DHT11);


void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  delay(5000);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi is not connected");
    Serial.println(WiFi.status());
    delay(500);
  }
  Serial.println("WiFi is Connected");
  Serial.println(WiFi.status());

  ThingSpeak.begin(client);
}

void loop() {
  float temp = dht.readTemperature();

  Serial.println("Temperature : ");
  Serial.println(temp);
 
  ThingSpeak.writeField(ChannelID,1,temp, API);
}