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

#define DS18B20 2  //D4 pin

#define REPORTING_PERIOD_MS1 5000  //20 seconds reporting period for Firebase update and MAX30100 Sensor reading

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

  pinMode(16, OUTPUT);

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
    pox.resume();
  }
  
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
    /*
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

    lastTempRequest = millis();
  }
  */
  delay(1);
  idle++;
  /*
  if (millis() - timer > 500) {
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
  */
  }
}