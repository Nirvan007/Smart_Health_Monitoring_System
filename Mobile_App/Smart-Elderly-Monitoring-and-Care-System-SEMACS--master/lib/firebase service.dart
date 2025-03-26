import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';

DateTime now = DateTime.now();
var heartRate;
var bodyTemperature;
var bloodOxygen;
var roomTemperature;
var roomHumidity;
var totalSleep;
var emergencyNotif;

var timeHr;
var timestamp;
var timeMin;
var timeDay;
var timeMonth;
var timeYear;

void readData() {
  DatabaseReference heartRateObj =
      FirebaseDatabase.instance.ref('sensor/HeartBeat');
  heartRateObj.onValue.listen(
    (DatabaseEvent event) {
      heartRate = event.snapshot.value;
      timeHr = now.hour.toString();
      timeMin = now.minute.toString();
      timeDay = now.day.toString();
      timeMonth = now.month.toString();
      timeYear = now.year.toString();
      print("Heart Rate Value Received: $heartRate");
      print('Timestamp: $timeHr:$timeMin');
    },
  );

  DatabaseReference bodyTemperatureObj =
      FirebaseDatabase.instance.ref('Body Parameters/Body Temperature');
  bodyTemperatureObj.onValue.listen(
    (DatabaseEvent event) {
      bodyTemperature = event.snapshot.value;
      timeHr = now.hour.toString();
      timeMin = now.minute.toString();
      timeDay = now.day.toString();
      timeMonth = now.month.toString();
      timeYear = now.year.toString();
      print("Body Temperature Value Received: $bodyTemperature");
    },
  );

  DatabaseReference bloodOxygenObj =
      FirebaseDatabase.instance.ref('sensor/SpO2');
  bloodOxygenObj.onValue.listen(
    (DatabaseEvent event) {
      bloodOxygen = event.snapshot.value;
      timeHr = now.hour.toString();
      timeMin = now.minute.toString();
      timeDay = now.day.toString();
      timeMonth = now.month.toString();
      timeYear = now.year.toString();
      print("Blood Oxygen Value Received: $bloodOxygen");
    },
  );

  DatabaseReference roomTemperatureObj =
      FirebaseDatabase.instance.ref('Peripherals/Room Temperature');
  roomTemperatureObj.onValue.listen(
    (DatabaseEvent event) {
      roomTemperature = event.snapshot.value;
      timeHr = now.hour.toString();
      timeMin = now.minute.toString();
      timeDay = now.day.toString();
      timeMonth = now.month.toString();
      timeYear = now.year.toString();
      print("Room Temperature Value Received: $roomTemperature");
    },
  );

  DatabaseReference roomHumidityObj =
      FirebaseDatabase.instance.ref('Peripherals/Room humidity');
  roomHumidityObj.onValue.listen(
    (DatabaseEvent event) {
      roomHumidity = event.snapshot.value;
      timeHr = now.hour.toString();
      timeMin = now.minute.toString();
      timeDay = now.day.toString();
      timeMonth = now.month.toString();
      timeYear = now.year.toString();
      print("Room Humidity Value Received: $roomHumidity");
    },
  );

  DatabaseReference totalSleepObj =
      FirebaseDatabase.instance.ref('Gyro/Total Sleep');
  totalSleepObj.onValue.listen(
    (DatabaseEvent event) {
      totalSleep = event.snapshot.value;
      timeHr = now.hour.toString();
      timeMin = now.minute.toString();
      timeDay = now.day.toString();
      timeMonth = now.month.toString();
      timeYear = now.year.toString();
      print("Total Sleep Value Received: $totalSleep");
    },
  );
}
