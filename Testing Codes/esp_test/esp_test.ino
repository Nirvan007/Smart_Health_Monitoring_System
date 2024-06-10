#include <Wire.h>                    //Wire library for I2C
#include "MAX30100_PulseOximeter.h"  //MAX30100 Sensor library

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"  //Provide the token generation process info.
#include "addons/RTDBHelper.h"   //Provide the RTDB payload printing info and other helper functions.

#include <OneWire.h>            //One wire library for DS18B20 Sensor
#include <DallasTemperature.h>  //DT library for DS18B20

#include <MPU6050_tockn.h>  //MPU6050 library

#define DS18B20 2  //D2 pin  Signal DS18B20
#define MAX_INT 23 //D23 pin INT MAX30102

#define REPORTING_PERIOD_MS1 10000  //20 seconds reporting period for Firebase update and MAX30100 Sensor reading

#define WIFI_SSID "AVANI"  // Insert your network credentials
#define WIFI_PASSWORD "avaninu123"

#define API_KEY "AIzaSyAjFLE4y7rjdVavcMRR1DLqjW4FRNEnauE"  // Insert Firebase project API Key

#define DATABASE_URL "https://semacsdb-default-rtdb.firebaseio.com/"  // Insert RTDB URLefine the RTDB URL

PulseOximeter pox;

FirebaseData fbdo1;  //Define Firebase Data object
FirebaseData fbdo2;
FirebaseData fbdo3;
FirebaseData fbdo7;
FirebaseData fbdo8;

FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

float BPM, SpO2, bodytemperature, temp, humidity;
uint32_t tsLastReport1 = 0;
uint32_t tsLastReport2 = 0;
long timer = 0;
long sleep_timer_start, sleep_timer_end;
float x, y, z;
int activate, interrupt, interrupt_sleep_timer, total_sleep, total_light_sleep, light_sleep, interrupt_timer = 0;
int resolution = 12;
unsigned long lastTempRequest = 0;
int delayInMillis = 0;
float temperature = 0.0;
int idle = 0;

const int analogPin = 4;     // Analog pin for heart rate sensor
const int numReadings = 100;  // Number of readings to average for smoother graph
int readings[numReadings];    // Array to store analog readings
int indexes = 0;                // Index for storing readings
int total = 0;                // Running total of readings
int average = 0;              // Average of readings
long timer1 = 0;

MPU6050 mpu6050(Wire);  //Assigning the wire bus
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
  //Wire.begin(D2, D1);
  Wire.begin(21, 22);

  // Initialize readings array to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }

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

  pinMode(MAX_INT, OUTPUT);

  pox.begin();
}

void loop() {
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

    tsLastReport1 = millis();

    if (Firebase.ready() && signupOK) {
      if (Firebase.RTDB.setInt(&fbdo1, "Body Parameters/Body Temperature", temperature)) {
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo1.dataPath());
        Serial.println("TYPE: " + fbdo1.dataType());
      } else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo1.errorReason());
      }

      if (Firebase.RTDB.setInt(&fbdo7, "sensor/HeartBeat", int(BPM))) {
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
    pox.resume();
  }

  if (millis() - timer1 > 10) {
    // Read analog value from the heart rate sensor
    int sensorValue = analogRead(analogPin);

    // Add the latest reading to the total
    total -= readings[indexes];
    readings[indexes] = sensorValue;
    total += sensorValue;
    indexes = (indexes + 1) % numReadings;

    // Calculate the average reading
    average = total / numReadings;
    /*
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
    */
    Serial.println(average);
    Serial.println(sensorValue);
    timer1 = millis();
  }
  /*
  if (millis() - lastTempRequest >= 1000) {
    temperature = sensors.getTempCByIndex(0);

    Serial.print("Body Temperature: ");
    Serial.println(temperature);

    idle = 0;
    resolution++;
    if (resolution > 12) resolution = 9;
    sensors.setResolution(tempDeviceAddress, resolution);
    sensors.requestTemperatures();
    delayInMillis = 750 / (1 << (12 - resolution));
    delay(1);
    idle++;
  }
  */
}