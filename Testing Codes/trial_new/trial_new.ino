#include <TFT_eSPI.h>   // include the TFT_eSPI library

#define TFT_CS 10  // define the chip select pin for the TFT display
#define TFT_DC 9   // define the data/command pin for the TFT display

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

TFT_eSPI tft = TFT_eSPI();  // create a TFT_eSPI object

float currentSpeed = 0;  // variable to store current speed
float gForce = 0;        // variable to store g-force

void setup() {
  Serial.begin(9600);  // start serial communication
  tft.init();          // initialize the TFT display
  tft.setRotation(3);  // set the display rotation
  tft.fillScreen(TFT_CYAN);
  tft.setTextColor(TFT_RED);  // clear the screen
  tft.setTextSize(2);                       // move to the next line
}

void loop() {
      currentSpeed = 100;  // get the current speed in km/h
      tft.fillRect(5, 37, 310, 30, WHITE);
      tft.setCursor(10, 45);
      tft.print("Speed: ");
      tft.setCursor(180, 45);
      tft.print(currentSpeed);
      tft.setCursor(220, 45);
      tft.print(" km/h");
  }