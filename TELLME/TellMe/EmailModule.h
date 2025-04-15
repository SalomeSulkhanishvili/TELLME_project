/* Author : Salome Sulkhanishvili */

#include <Arduino.h>
#include <SPIFFS.h>
#include <ESP_Mail_Client.h>
#include "BLEModule.h"


/* The sign in credentials */
#define AUTHOR_EMAIL "ESP32.TELLME@gmail.com"
#define AUTHOR_PASSWORD "arrd jych qvaj xqnx"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465


/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);
void setupWiFi();
void sendEmail(String msg, String filePathName);
void deinitWiFi();
void changeSettings(CommandOption cmd, String newValue);
void changePassword(String newValuep);

