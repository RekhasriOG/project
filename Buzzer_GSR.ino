int buzzerPin = D3;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

  // Buzzer ON
  digitalWrite(buzzerPin, HIGH);
  delay(1000);

  // Buzzer OFF
  digitalWrite(buzzerPin, LOW);
  delay(1000);
}