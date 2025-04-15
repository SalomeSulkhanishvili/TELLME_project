/* Author : Salome Sulkhanishvili */

#include "CameraModule.h"
#include "BLEModule.h"
#include "EmailModule.h"
#include "NextionModule.h"
#include "RealTimeModule.h"

String newMsg;
String filePath;
bool recievedMsg = false;

void setup() {
  Serial.begin(9600);
  // setup Real Time Clock
  setupRTC();

  EEPROM.begin(EEPROM_SIZE); // set up EEPROM
  // // clear eeprom
  // for (int i = 0; i < 512; i++) {
  //   EEPROM.write(i, 0);
  // }
  EEPROM.commit();
  delay(500);
 
  // set up SPIFFS
  SPIFFS.begin();
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // set up SD card CS pin
  Serial.print("Initializing SD card...");
  if (!SD.begin(5)) {
    Serial.println("initialization failed!");
  }

  // set up components
  setupCamera();
  setupBLE();
  setupNextion();

  Serial.println("initialization done.");
}

void loop(){
  // observe BLE and take picture if new message is available
  if (observeBlt()) {
    newMsg = getRecievedMsg();
    if (getCommand() != none) {
      
      changeSettings(getCommand(), newMsg);
    }
    else {
      bleDeInit(); // deinit BEL
      delay(1000);
      setupWiFi(); // init WIFI

      filePath = savePicture(); // took and save picture 
      recievedMsg = true;
    }
  }

  // send email if received message and took picutre
  if (recievedMsg) {
    sendEmail(newMsg, filePath); // send mail to given gmail
    recievedMsg = false;

    deinitWiFi(); // Deinint WIFI
    delay(1000);
    setupBLE();  // init BLE
  }
  observeNextion();
  setDate();
}