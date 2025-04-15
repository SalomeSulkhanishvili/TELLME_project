/* Author : Salome Sulkhanishvili */

#pragma once

#include "SDCardModule.h"
#include "BMP.h"
#include "OV7670.h"
#include <SPIFFS.h>
#include "SD.h"
#include <FS.h>
#include <FSImpl.h>
#include <vfs_api.h>
#include <EEPROM.h>
#include <esp_task_wdt.h>

#define EEPROM_SIZE 1

void setupCamera();
void takePicture();
String savePicture();