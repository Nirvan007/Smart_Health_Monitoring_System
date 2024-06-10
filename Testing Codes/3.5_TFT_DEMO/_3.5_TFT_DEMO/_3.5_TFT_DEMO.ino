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

void setup() {
  // Reading TFT ID:
  uint16_t ID = tft.readID();
  Serial.begin(9600);
  Serial.println(ID);
  //Initializing TFT display:
  tft.begin(ID);
}

void loop() {
  // Fill TFT Screen with a color:
  tft.fillScreen(BLACK);
  delay(500);

  // Fill a rectangle:
  tft.fillRect(11, 11, 298, 48, RED);
  delay(500);

  //Draw a rectangle:
  tft.drawRect(10, 10, 300, 50, YELLOW);
  delay(500);

  //Set cursor:
  tft.setCursor(80, 25);

  //Set text color:
  tft.setTextColor(WHITE);

  //Set text size:
  tft.setTextSize(2);

  //Print text to TFT display:
  tft.println("EEWORLDONLINE");
  delay(2000);

  //Draw Lines
  for (int i = 65; i < 480; i += 7) {
    tft.drawLine(0, 240, 100, i, CYAN);
    delay(100);
  }

  //Draw Circles
  for (int i = 60; i > 5; i -= 5) {
    tft.drawCircle(210, 140, i, GREEN);
    delay(30);
  }

  //Draw rectangles
  for (int i = 100; i > 30; i -= 10) {
    tft.drawRect(150, 220, i, i, YELLOW);
    delay(30);
  }

  //Draw Triangles
  for (int i = 10; i < 50; i += 5) {
    tft.drawTriangle(
      200, 360 + i,
      150 + i, 460 - i,
      250 - i, 460 - i,
      RED);
  }
  delay(2000);

  tft.fillScreen(WHITE);
  tft.fillRect(10, 10, 300, 60, YELLOW);
  tft.setCursor(40, 30);
  tft.setTextSize(2);
  tft.setTextColor(MAGENTA);
  tft.println("Thanks for watching !");

  tft.fillRect(7, 100, 300, 70, YELLOW);
  tft.setCursor(10, 100);
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.println("Stay connected with us");
  tft.println(" @ EngineersGarage.com");
  delay(5000);
}