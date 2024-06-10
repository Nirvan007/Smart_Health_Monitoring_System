#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

MCUFRIEND_kbv tft;

const int analogPin = A5;     // Analog pin for heart rate sensor
const int numReadings = 100;  // Number of readings to average for smoother graph
int readings[numReadings];    // Array to store analog readings
int index = 0;                // Index for storing readings
int total = 0;                // Running total of readings
int average = 0;              // Average of readings

long timer1 = 0;
long timer2 = 0;

void setup() {
  Serial.begin(9600);
  // Reading TFT ID:
  uint16_t ID = tft.readID();
  Serial.begin(9600);
  Serial.println(ID);
  //Initializing TFT display:
  tft.begin(ID);
  tft.setRotation(1);     // Adjust the screen rotation if necessary
  tft.fillScreen(BLACK);  // Fill the screen with black color

  // Initialize readings array to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
  pinMode(13, OUTPUT);
}

void loop() {

  if (millis() - timer1 > 10) {
    // Read analog value from the heart rate sensor
    int sensorValue = analogRead(analogPin);

    // Add the latest reading to the total
    total -= readings[index];
    readings[index] = sensorValue;
    total += sensorValue;
    index = (index + 1) % numReadings;

    // Calculate the average reading
    average = total / numReadings;

    // Clear the screen
    tft.fillRect(0, 0, 350, 100, BLACK);

    // Draw the graph
    for (int i = 0; i < numReadings - 1; i++) {
      int x1 = map(i, 0, numReadings - 1, 0, 350);
      int x2 = map(i + 1, 0, numReadings - 1, 0, 350);
      int y1 = map(readings[i], 0, 1023, 100, 0);
      int y2 = map(readings[i + 1], 0, 1023, 100, 0);
      tft.drawLine(x1, y1, x2, y2, GREEN);  // Change the color as per your preference
    }

    Serial.println(average);
    Serial.println(sensorValue);
    timer1 = millis();
  }
  /*
  if (millis() - timer2 > 20000) {
    tft.reset();
    tft.fillScreen(BLACK);
    uint16_t ID = tft.readID();
    //Initializing TFT display:
    tft.begin(ID);
    tft.setRotation(1);
    timer2 = millis();
  }
  */
}
/*
void readHeartRate(){
  // Read analog value from the heart rate sensor
  int sensorValue = analogRead(analogPin);
  int newVal = sensorValue/7;
  
  // Add the latest reading to the total
  total -= readings[index];
  readings[index] = sensorValue;
  total += sensorValue;
  index = (index + 1) % numReadings;

  // Calculate the average reading
  average = total / numReadings;

  // Clear the screen
  //tft.fillRect(0, 0, 200, 200, BLACK);
  
  // Draw the graph
  for (int i = 0; i < numReadings - 1; i++) {
    int x1 = map(i, 0, numReadings - 1, 0, tft.width());
    int x2 = map(i + 1, 0, numReadings - 1, 0, tft.width());
    int y1 = map(readings[i], 0, 1023, tft.height(), 0);
    int y2 = map(readings[i + 1], 0, 1023, tft.height(), 0);
    tft.drawLine(x1, y1, x2, y2, GREEN); // Change the color as per your preference
  }

  // Display the average reading
  tft.setCursor(10, 10);
  tft.print("Heart Rate: ");
  tft.print(average);

  Serial.println(average);
  Serial.println(sensorValue);

  delay(10); // Adjust the delay as per your requirement
} */