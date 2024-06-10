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

const int analogPin = A5;     // Analog pin for heart rate sensor
const int numReadings = 100;  // Number of readings to average for smoother graph
int readings[numReadings];    // Array to store analog readings
int index = 0;                // Index for storing readings
int total = 0;                // Running total of readings
int average = 0;              // Average of readings

void setup() {
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
  tft.drawFastHLine(0, 418, 80, WHITE);

  tft.drawFastVLine(319, 0, 350, WHITE);
  tft.drawFastVLine(0, 0, 350, WHITE);
  tft.drawFastVLine(319, 350, 130, WHITE);
  tft.drawFastVLine(240, 350, 130, WHITE);  //Bottom line (TEMP)
  tft.drawFastVLine(159, 0, 480, WHITE);    //Top line (TEMP)
  tft.drawFastVLine(80, 350, 130, WHITE);   //Top line (sleep)
  tft.drawFastVLine(0, 350, 130, WHITE);    //bottom line (sleep)

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

  tft.setTextColor(GREEN);
  showmsgXY(352, 260, 0.5, &FreeSans12pt7b, "RT");
  tft.setTextColor(BLUE);
  showmsgXY(418, 260, 0.5, &FreeSans12pt7b, "RH");
  tft.setTextColor(GREEN);
  showmsgXY(350, 320, 0.5, &FreeSevenSegNumFont, "30");
  tft.setTextColor(BLUE);
  showmsgXY(415, 320, 0.5, &FreeSevenSegNumFont, "70");
}

void loop() {

  // Clear the screen
  tft.fillRect(0, 0, 350, 159, BLACK);

  // Draw the graph
  for (int i = 0; i < numReadings - 1; i++) {
    int x1 = map(i, 0, numReadings - 1, 0, 350);
    int x2 = map(i + 1, 0, numReadings - 1, 0, 350);
    int y1 = map(readings[i], 0, 1023, 159, 0);
    int y2 = map(readings[i + 1], 0, 1023, 159, 0);
    tft.drawLine(x1, y1, x2, y2, GREEN);  // Change the color as per your preference
  }
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