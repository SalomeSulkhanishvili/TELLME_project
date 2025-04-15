/* Author : Salome Sulkhanishvili */

#include "RealTimeModule.h"

RTClib myRTC;
String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void setupRTC() {
  Wire.begin();
}

String getCurrDateforMsg() {
  DateTime now = myRTC.now();
  String month = months[now.month() - 1];
  String date = "Time: " + String(now.hour(), DEC) + ":" + String(now.minute(), DEC) + "%" + "Date: " + month + " " + String(now.day(), DEC) + ", " + String(now.year(), DEC);
  return date;
}

String setHomeScreenTime() {
  DateTime now = myRTC.now();
  return String(now.hour(), DEC) + ":" + String(now.minute(), DEC);
}

String setHomeScreenDate() {
  DateTime now = myRTC.now();
  String month = months[now.month() - 1];
  return month + " " + String(now.day(), DEC) + ", " + String(now.year(), DEC);
}

void printWholeDate() {
  DateTime now = myRTC.now();
  Serial.println(now.month());
  Serial.println(now.day());

}