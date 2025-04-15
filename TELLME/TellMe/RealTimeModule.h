/* Author : Salome Sulkhanishvili */

#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>

void setupRTC();
void printWholeDate();
String setHomeScreenDate();
String setHomeScreenTime();
String getCurrDateforMsg();