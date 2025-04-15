/* Author : Salome Sulkhanishvili */

#include "BLEModule.h"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
BLEService *pService = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

String msgA;
bool recieved = false;
CommandOption command = none;
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        msgA = "";
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++) {
          msgA += value[i];
          Serial.print(value[i]);
        }
        recieved = true;
        Serial.println();
        Serial.println("*********");
      }
    }
};


void bleDeInit() {
  BLEDevice::deinit(false);
  Serial.println("deinit BLE");
}

void setupBLE() {
  Serial.println("BLE is getting ready. See the magic =)");

  BLEDevice::init("ESP32 - TELLME");
  pServer = BLEDevice::createServer();

  pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hi");
  pService->start();

  BLEAdvertising * pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

bool observeBlt() {
  if (recieved) {
    command = none;
    Serial.println("enter in observeBlt");
    if (!checkMailCommand(getRecievedMsg()) && !checkWiFiCommand(getRecievedMsg())) {
      saveMessage();
    }

    recieved = false;
    return true;
  }
  return false;
}

CommandOption getCommand() {
  return command;
}

// Mail command format: EMAIL: sulkhanishvili767@gmail.com
bool checkMailCommand(String value) {
  String tmpVal = value;
  tmpVal.replace(" ", "");
  tmpVal.toLowerCase();
  Serial.println("the new email should be: ");
  Serial.println(tmpVal);
  Serial.print("index of email function: ");
  Serial.println(tmpVal.indexOf("email:"));
  if (tmpVal.indexOf("email:") >= 0) {
    tmpVal.replace("email:", "");
    
    Serial.println("the new email without email: ");
    Serial.println(tmpVal);
    msgA = tmpVal;
    command = changeMail;
    return true;
  }
  return false;
}
// WiFi command format: WiFi:NAME:TEST-WIFI,PASS:TEST-PASSWORD
bool checkWiFiCommand(String value) {
  String tmpVal = value;

  if (tmpVal.indexOf("WiFi:") >= 0) {
    tmpVal.replace("WiFi:", "");

    Serial.print("the WiFi: ");
    Serial.println(tmpVal);

    msgA = tmpVal;
    command = changeWiFi;
    return true;
  }
  return false;
}

void saveMessage() {
  int messageNumber = EEPROM.read(0) + 1;
  String path = "/message" + String(messageNumber) + ".txt";
  Serial.printf("Message file name: %s\n", path.c_str());
  File file = SD.open(path, FILE_WRITE);

  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  String newMessage = getRecievedMsg() + "\n-------------------------------------\n" + getCurrDateforMsg();
  if(file.print(newMessage)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }

  file.close();
  Serial.println("saved message!");
  Serial.println("-------------------------\n");

  EEPROM.write(0, messageNumber);
  EEPROM.commit();

}

String getRecievedMsg() {
  return msgA;
}
