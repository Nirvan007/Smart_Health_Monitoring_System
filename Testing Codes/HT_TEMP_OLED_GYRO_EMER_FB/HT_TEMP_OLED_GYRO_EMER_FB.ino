#include <Wire.h>                      //Wire library for I2C
#include "MAX30100_PulseOximeter.h"    //MAX30100 Sensor library
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
#include "DHT.h"                       //DHT11 Sensor library
#include <OneWire.h>                   //One wire library for DS18B20 Sensor
#include <DallasTemperature.h>         //DT library for DS18B20
#include <MPU6050_tockn.h>             //MPU6050 library
#include <SPI.h>                       //SPI interface library
#include <Adafruit_GFX.h>              //SSD1306 OLED Display library
#include <Adafruit_SSD1306.h>          //SSD1306 OLED Display library
#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
#include <Fonts/FreeMono9pt7b.h>       // Add a custom font

MPU6050 mpu6050(Wire);  //Assigning the wire bus

#define DHTTYPE DHT11               //Assigning the sensor as DHT11 type as there is DHT22 type as well
#define DHTPIN 14                   //D5 pin
#define DS18B20 2                   //D4 pin
#define REPORTING_PERIOD_MS1 20000  //20 seconds reporting period for Firebase update and MAX30100 Sensor reading

#define WIFI_SSID "AVANI"           //Wifi SSID
#define WIFI_PASSWORD "avaninu123"  //Wifi Password

#define API_KEY "AIzaSyAjFLE4y7rjdVavcMRR1DLqjW4FRNEnauE"  // Insert Firebase project API Key
#define DATABASE_URL "https://semacsdb-default-rtdb.firebaseio.com/"  // Insert RTDB URLefine the RTDB URL

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1  //Reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

PulseOximeter pox;

FirebaseData fbdo1;  //Define Firebase Data object
FirebaseData fbdo2;
FirebaseData fbdo3;
FirebaseData fbdo7;
FirebaseData fbdo8;

FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

float temp, humidity, BPM, SpO2, bodytemperature;
uint32_t tsLastReport1 = 0;
uint32_t tsLastReport2 = 0;
long timer = 0;
long sleep_timer_start, sleep_timer_end;
float x, y, z;
int activate, interrupt, interrupt_sleep_timer, total_sleep, total_light_sleep, light_sleep, interrupt_timer = 0;
const int button = 12;
int buttonState = 0;
const int button2 = 13;
int buttonState2 = 0;
int help_counter = 0;
int OLED_counter = 0;
int emergency_notif = 0;
int resolution = 12;
unsigned long lastTempRequest = 0;
int delayInMillis = 0;
float temperature = 0.0;
int idle = 0;

OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;

void setup() {
  Serial.begin(115200);
  sensors.begin();
  sensors.getAddress(tempDeviceAddress, 0);
  sensors.setResolution(tempDeviceAddress, resolution);

  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  delayInMillis = 750 / (1 << (12 - resolution));
  lastTempRequest = millis();

  Wire.setClock(400000UL);
  pinMode(16, OUTPUT);
  pinMode(button, INPUT);
  pinMode(button2, INPUT);
  dht.begin();
  Wire.begin(D2, D1);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.print("SEMACS");
  display.display();
  delay(1000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());  //print local IP address

  config.api_key = API_KEY;  // Assign the api key (required)

  config.database_url = DATABASE_URL;  // Assign the RTDB URL (required)

  if (Firebase.signUp(&config, &auth, "", "")) {  // Sign up
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  pox.begin();
  mpu6050.begin();
}

void loop() {
  if (millis() - lastTempRequest >= 1000) {
    temperature = sensors.getTempCByIndex(0);
    temp = dht.readTemperature();
    humidity = dht.readHumidity();

    Serial.print("Body Temperature: ");
    Serial.println(temperature);
    Serial.print("Room Temperature: ");
    Serial.print(temp);
    Serial.println("°C");
    Serial.print("Room Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    Serial.println(" ");

    buttonState = digitalRead(button);
    if (buttonState == HIGH) {
      help_counter++;
    }

    buttonState2 = digitalRead(button2);
    if (buttonState2 == HIGH) {
      OLED_counter++;
    }

    idle = 0;
    resolution++;
    if (resolution > 12) resolution = 9;
    sensors.setResolution(tempDeviceAddress, resolution);
    sensors.requestTemperatures();
    delayInMillis = 750 / (1 << (12 - resolution));
    lastTempRequest = millis();
  }
  delay(1);
  idle++;

  pox.update();

  if (millis() - tsLastReport1 > REPORTING_PERIOD_MS1) {
    pox.shutdown();
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();

    Serial.print("Heart rate:");
    Serial.print(BPM);
    Serial.print(" SpO2:");
    Serial.print(SpO2);
    Serial.println(" %");

    buttonState = digitalRead(button);
    Serial.print("Button1 State: ");
    Serial.println(buttonState);

    buttonState2 = digitalRead(button2);
    Serial.print("Button2 State: ");
    Serial.println(buttonState2);

    if (OLED_counter >= 1) {
      display.clearDisplay();
      display.setTextSize(2);       // The fontsize
      display.setTextColor(WHITE);  // Draw white text
      display.setCursor(5, 5);      // Start at top-left corner
      display.print("RTemp: ");     //the text
      display.print(int(temp));     //the text
      display.display();            //call to display

      display.setTextSize(2);        // The fontsize
      display.setTextColor(WHITE);   // Draw white text
      display.setCursor(5, 25);      // Start at top-left corner
      display.print("RHum: ");       //the text
      display.print(int(humidity));  //the text
      display.display();             //call to display

      display.setTextSize(2);           // The fontsize
      display.setTextColor(WHITE);      // Draw white text
      display.setCursor(5, 45);         // Start at top-left corner
      display.print("BTemp: ");         //the text
      display.print(int(temperature));  //the text
      display.display();                //call to display

      OLED_counter = 0;
    } else {
      display.clearDisplay();
      display.setTextSize(2);       // The fontsize
      display.setTextColor(WHITE);  // Draw white text
      display.setCursor(5, 5);      // Start at top-left corner
      display.print("SPO2: ");      //the text
      display.print(int(SpO2));     //the text
      display.print("%");           //the text
      display.display();            //call to display

      display.setTextSize(2);       // The fontsize
      display.setTextColor(WHITE);  // Draw white text
      display.setCursor(5, 35);     // Start at top-left corner
      display.print("BPM: ");       //the text
      display.print(int(BPM));      //the text
      display.display();            //call to display
    }

    if (Firebase.ready() && signupOK) {
      if (Firebase.RTDB.setInt(&fbdo1, "Body Parameters/Body Temperature", temperature)) {
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo1.dataPath());
        Serial.println("TYPE: " + fbdo1.dataType());
      } else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo1.errorReason());
      }

      if (Firebase.RTDB.setInt(&fbdo7, "sensor/HeartBeat", BPM)) {
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo7.dataPath());
        Serial.println("TYPE: " + fbdo7.dataType());
      } else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo7.errorReason());
      }

      if (Firebase.RTDB.setInt(&fbdo8, "sensor/SpO2", SpO2)) {
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo8.dataPath());
        Serial.println("TYPE: " + fbdo8.dataType());
      } else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo8.errorReason());
      }
    }

    tsLastReport1 = millis();

    if (help_counter >= 1) {
      emergency_notif = 1;
      Serial.print("Emergency: ");
      Serial.println(emergency_notif);
      help_counter = 0;
    } else {
      emergency_notif = 0;
      Serial.print("Emergency: ");
      Serial.println(emergency_notif);
    }

    tsLastReport1 = millis();

    pox.resume();
  }

  if (millis() - timer > 1000) {
    mpu6050.update();
    x = mpu6050.getGyroX();
    y = mpu6050.getGyroY();
    z = mpu6050.getGyroZ();

    if (activate == 0) {  // first sleep confirmation
      if ((x <= 20 || x >= -20) && (y <= 20 || y >= -20) && (z <= 20 || z >= -20)) {
        sleep_timer_start = millis() / 1000 - sleep_timer_end;
        Serial.print("sleep_timer_start: ");
        Serial.print(sleep_timer_start);
        Serial.println(",");
        if (sleep_timer_start == 30) {
          activate = 1;
        }
      }
      if ((x >= 20 || x <= -20) || (y >= 20 || y <= -20) || (z >= 20 || z <= -20)) {
        sleep_timer_end = (millis() / 1000);
        Serial.print("sleep_timer_end: ");
        Serial.print(sleep_timer_end);
        Serial.println(",");
      }
    }

    if (activate == 1) {  // sleeping mode
      Serial.print("Sleep Mode Duration: ");
      Serial.print(light_sleep);
      Serial.println(",");
      light_sleep = (millis() / 1000) - sleep_timer_end;

      if ((x >= 20 || x <= -20) || (y >= 20 || y <= -20) || (z >= 20 || z <= -20)) {
        interrupt_sleep_timer = (millis() / 1000) - sleep_timer_end;
        interrupt = interrupt + 1;
        Serial.print("Interrupt Counter: ");
        Serial.println(interrupt);
      }

      if ((millis() / 1000) - sleep_timer_end - interrupt_sleep_timer > 90) {
        interrupt = 0;
      }

      if ((millis() / 1000) - sleep_timer_end - interrupt_sleep_timer <= 90) {
        if (interrupt >= 5) {
          sleep_timer_end = (millis() / 1000);
          if (light_sleep >= 45) {  // second sleep confirmation
            total_light_sleep = total_light_sleep + light_sleep;
            Serial.print("Total sleep: ");
            Serial.print(total_light_sleep / 60);
            Serial.println(",");
          }
          activate = 0;
          interrupt = 0;
          light_sleep = 0;
          interrupt_sleep_timer = 0;
          Serial.println("All Params set to 0");
          Serial.println("_____x_____x_____x_____");
        }
      }
    }
    timer = millis();
  }
}
