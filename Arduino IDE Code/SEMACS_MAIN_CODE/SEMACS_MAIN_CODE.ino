#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

#define DHTTYPE DHT11
#define DHTPIN 14 //D5 pin
#define DS18B20 2 //D4 pin
#define REPORTING_PERIOD_MS1 20000

#define FIREBASE_HOST "****"  //Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "***" //Firebase Database Secret goes here

#define WIFI_SSID "****" //WiFi SSID to which you want NodeMCU to connect
#define WIFI_PASSWORD "****"  //Password of your wifi network

FirebaseData firebaseData;

DHT dht(DHTPIN, DHTTYPE);;

PulseOximeter pox;

float temp, humidity, BPM, SpO2, bodytemperature;
uint32_t tsLastReport1 = 0;
uint32_t tsLastReport2 = 0;
long timer = 0;
long sleep_timer_start, sleep_timer_end;
float x, y, z;
int activate, interrupt, interrupt_sleep_timer, total_sleep, total_light_sleep, light_sleep, interrupt_timer = 0;
const int button = 12;
int buttonState = 0;
int help_counter = 0;
int e = 0;
int  resolution = 12;
unsigned long lastTempRequest = 0;
int  delayInMillis = 0;
float temperature = 0.0;
int  idle = 0;

OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;

void setup()
{
  Serial.begin(115200);
  sensors.begin();
  sensors.getAddress(tempDeviceAddress, 0);
  sensors.setResolution(tempDeviceAddress, resolution);

  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  delayInMillis = 750 / (1 << (12 - resolution));
  lastTempRequest = millis();

  Wire.setClock(400000UL);
  pinMode(button, INPUT);
  pinMode(16, OUTPUT);
  dht.begin();
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("SEMACS");
  delay(1000);
  lcd.clear();
  //pox.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //try to connect with wifi
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
  Serial.println(WiFi.localIP()); //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase

  Firebase.reconnectWiFi(true);
  pox.begin();
  mpu6050.begin();
}

void loop()
{
  if (millis() - lastTempRequest >= 1000)
  {
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

  if (millis() - tsLastReport1 > REPORTING_PERIOD_MS1)
  {
    pox.shutdown();
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    
    Serial.print("Heart rate:");
    Serial.print(BPM);
    Serial.print(" SpO2:");
    Serial.print(SpO2);
    Serial.println(" %");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BPM: ");
    lcd.setCursor(10, 0);
    lcd.print(pox.getHeartRate());
    lcd.setCursor(0, 1);
    lcd.print("SpO2:");
    lcd.setCursor(10, 1);
    lcd.print(pox.getSpO2());
    lcd.setCursor(14, 1);
    lcd.print("%");

    tsLastReport1 = millis();
    
    if (help_counter >= 1){
      e = 1;
      Firebase.setInt(firebaseData, "Emergency Call/State", e);
      help_counter = 0;
    }
    else{
      e = 0;
      Firebase.setInt(firebaseData, "Emergency Call/State", e);
    }
    
    Firebase.setFloat(firebaseData, "sensor/HeartBeat", BPM);
    Firebase.setInt(firebaseData, "sensor/SpO2", SpO2);
    Firebase.setFloat(firebaseData, "Body Parameters/Body Temperature", temperature);
    Firebase.setInt(firebaseData, "Peripherals/Room Temperature", temp);
    Firebase.setString(firebaseData, "Peripherals/Room humidity", String(humidity));
    Firebase.setInt(firebaseData, "Gyro/Sleep", sleep_timer_start);
    Firebase.setInt(firebaseData, "Gyro/Interrupt", interrupt);
    Firebase.setInt(firebaseData, "Gyro/Total Sleep", total_light_sleep / 60);
    pox.resume();
  }

  if (millis() - timer > 1000) {
    mpu6050.update();
    x = mpu6050.getGyroX();
    y = mpu6050.getGyroY();
    z = mpu6050.getGyroZ();

    if (activate == 0) { // first sleep confirmation
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

    if (activate == 1) { // sleeping mode
      Serial.print("Sleep Mode Duration: ");
      Serial.print(light_sleep);
      Serial.println(",");
      light_sleep = (millis() / 1000) - sleep_timer_end; //Calculate sleep time

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
          if (light_sleep >= 45) {
            total_light_sleep = total_light_sleep + light_sleep;
            Serial.print("Total sleep: ");
            Serial.print(total_light_sleep / 60);
            Serial.println(",");
          }
          activate = 0;
          interrupt = 0;
          //deep_sleep = 0;
          light_sleep = 0;
          interrupt_sleep_timer = 0;
          //interrupt_for_deep_sleep = 0;
          Serial.println("All Params set to 0");
          Serial.println("_____x_____x_____x_____");
        }
      }
    }
    timer = millis();
  }
}
