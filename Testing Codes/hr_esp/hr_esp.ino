const int analogPin = 4;  // Analog pin for heart rate sensor
long timer1 = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read analog value from the heart rate sensor
  double sensorValue = analogRead(analogPin);
  char txString[8];
  dtostrf(sensorValue, 4, 1, txString);
  Serial.write(txString);  //Write the serial data
  delay(100);
}