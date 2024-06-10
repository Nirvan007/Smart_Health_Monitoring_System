#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <Fonts/FreeSans12pt7b.h>
#include <FreeDefaultFonts.h>

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

MCUFRIEND_kbv tft;

//long timer1 = 0;
char Mymessage1[10];  //Initialized variable to store recieved data

/*
const int numReadings = 100;  // Number of readings to average for smoother graph
int readings[numReadings];    // Array to store analog readings
int indexes = 0;              // Index for storing readings
int total = 0;                // Running total of readings
int average = 0;              // Average of readings
*/

void setup() {
  Serial.begin(9600);

  // Reading TFT ID:
  uint16_t ID = tft.readID();
  Serial.begin(9600);
  Serial.println(ID);
  //Initializing TFT display:
  tft.begin(ID);
  // Fill TFT Screen with a color:
  tft.fillScreen(BLACK);
  //delay(500);

  //tft.fillRect(10, 10, 200, 200, YELLOW);
  tft.drawFastHLine(0, 350, 320, WHITE);
  tft.drawFastHLine(0, 0, 320, WHITE);

  tft.drawFastVLine(319, 0, 350, WHITE);
  tft.drawFastVLine(0, 0, 350, WHITE);
  tft.drawFastVLine(319, 350, 130, WHITE);
  tft.drawFastVLine(240, 350, 130, WHITE);  //Top line (TEMP)
  tft.drawFastVLine(160, 350, 130, WHITE);  //bottom line (TEMP)
  tft.drawFastVLine(80, 350, 130, WHITE);   //Top line (sleep)
  tft.drawFastVLine(0, 350, 130, WHITE);    //bottom line (sleep)
  /*
  tft.setRotation(1);
  tft.setTextColor(RED);
  showmsgXY(352, 20, 0.5, &FreeSans12pt7b, "BPM");
  tft.setTextColor(RED);
  showmsgXY(360, 80, 0.1, &FreeSevenSegNumFont, "123");

  tft.setTextColor(CYAN);
  showmsgXY(352, 100, 0.5, &FreeSans12pt7b, "SpO2");
  tft.setTextColor(CYAN);
  showmsgXY(350, 160, 1, &FreeSevenSegNumFont, "100");
  tft.setTextColor(CYAN);
  showmsgXY(450, 155, 1, &FreeSans12pt7b, "%");

  tft.setTextColor(GREEN);
  showmsgXY(352, 180, 0.5, &FreeSans12pt7b, "TEMP");
  tft.setTextColor(GREEN);
  showmsgXY(360, 240, 1, &FreeSevenSegNumFont, "98");
  tft.setTextColor(GREEN);
  showmsgXY(420, 235, 3, &FreeSans12pt7b, ".");
  tft.setTextColor(GREEN);
  showmsgXY(435, 240, 1, &FreeSevenSegNumFont, "6");
  tft.setTextColor(GREEN);
  showmsgXY(465, 235, 1, &FreeSans12pt7b, "F");
  
  // Initialize readings array to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
  */
}

void loop() {
  if (Serial.available()) {
    Serial.readBytes(Mymessage1, 5);  //Read the serial data and store in var
    Serial.println(Mymessage1);       //Print data on Serial Monitor
    delay(500);
  }
  String msg(Mymessage1);
  int BPM = msg.toInt();
  Serial.print("Heart rate: ");
  Serial.println(BPM);
  
  /*
  // Add the latest reading to the total
  total -= readings[indexes];
  readings[indexes] = sensorValue;
  total += sensorValue;
  indexes = (indexes + 1) % numReadings;

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
  */
}

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg) {
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextSize(sz);
  tft.print(msg);
  delay(1000);
}
