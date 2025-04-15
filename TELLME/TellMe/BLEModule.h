/* Author : Salome Sulkhanishvili */

#pragma once
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "SD.h"
#include <FS.h>
#include <EEPROM.h>
#include "RealTimeModule.h"

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

enum CommandOption {
  changeMail,
  changeWiFi, 
  none,
};


bool observeBlt();
String getRecievedMsg();
void setupBLE();
void bleDeInit();
void saveMessage();
bool checkMailCommand(String value);
bool checkWiFiCommand(String value);
CommandOption getCommand();