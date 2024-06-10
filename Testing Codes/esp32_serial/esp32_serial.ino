//double val = 0.00;
const int analogPin = 36;  // Analog pin for heart rate sensor

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // Read analog value from the heart rate sensor
  int sensorValue = analogRead(analogPin);
  char Mymessage[10];
  dtostrf(sensorValue, 4, 0, Mymessage);
  Serial2.write(Mymessage, 5);  //Write the serial data
  delay(100);
}