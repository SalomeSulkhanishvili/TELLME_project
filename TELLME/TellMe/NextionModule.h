/* Author : Salome Sulkhanishvili */

#pragma once

#include <EEPROM.h>
#include "Nextion.h"
#include "SDCardModule.h"
#include "RealTimeModule.h"
#include "SD.h"


void messagesBtnPopCallback(void *ptr);
void settingsBtnPopCallback(void *ptr);
void msgBackBtnPopCallback(void *ptr);
void settBackBtnPopCallback(void *ptr);
void msgNextBtnPopCallback(void *ptr);
void msgPrevBtnPopCallback(void *ptr);
void setupNextion();
void observeNextion();
void showCurrMsg();
void setupMsgPage();
void setDate();
void setMessageTexts(String text);
void setConfigurationsTexts();