/* Author : Salome Sulkhanishvili */

#include "NextionModule.h"

// total pages
NexPage HomePage = NexPage(0, 0, "page0");
NexPage MessagesPg = NexPage(1, 0, "page1");
NexPage SettingsPg = NexPage(2, 0, "page2");

// buttons on first page (Home Page)
NexButton messagesBtn = NexButton(0, 3, "b00"); 
NexButton settingsBtn = NexButton(0, 4, "b10");
// buttons on second page (Messages Page)
NexButton msgBackBtn = NexButton(1, 3, "b01"); 
NexButton msgNextBtn = NexButton(1, 5, "b11");
NexButton msgPrevBtn = NexButton(1, 6, "b21");
// buttons on third page (Settings Page)
NexButton settBackBtn = NexButton(2, 3, "b02"); 
NexButton cleanHistBtn = NexButton(2, 4, "b12");
NexButton mailBtn = NexButton(2, 5, "b22");
NexButton WiFiBtn = NexButton(2, 6, "b32"); 
NexButton infoBtn = NexButton(2, 7, "b42");

// text areas 
NexText timeText = NexText(0, 2, "t00");
NexText dateText = NexText(0, 5, "t10");


NexText msgText = NexText(1, 4, "t21");
NexText msgTitle = NexText(1, 9, "t01");
NexText msgTimeText = NexText(1, 7, "t31");
NexText msgDateText = NexText(1, 8, "t41");

NexText settingsTitle = NexText(2, 10, "t02");
NexText emailText = NexText(2, 8, "t22");
NexText WiFiText = NexText(2, 9, "t32");

int maxNum = 0;
int minNum = 0;
int currNum = 0;

int timeCounter = 30000;
int timeMaxCounter = 30000;

void setupMsgPage() {
  minNum = 0;
  maxNum = EEPROM.read(0);
  currNum = maxNum;
  showCurrMsg();
}

void showCurrMsg() {
  String currText = "";
  char currChar;

  String path = "/message" + String(currNum) + ".txt";
  File file = SD.open(path, FILE_READ);
  if(!file) {
    Serial.println("Failed to open file for writing");
    Serial.println(currNum);
    if (currNum - 1 >= minNum) {
      currNum = currNum - 1;
      showCurrMsg();
      return;
    }
    else {
      currText = "No Available Message";
    }
  } 
  while(file.available()){
    currChar = file.read();
    currText.concat(currChar);
  } 
  file.close();
  setMessageTexts(currText);  
}

void setMessageTexts(String text) {
  int delimiter1 = text.indexOf("\n-");
  int delimiter2 = text.indexOf("-\n");
  int delimiter3 = text.indexOf("%");
  int lastIndex = text.length();

  String currentMsg = text.substring(0, delimiter1);
  String currentTime = text.substring(delimiter2 + 2, delimiter3);
  String currentDate = text.substring(delimiter3 + 1, lastIndex);

  msgText.setText(currentMsg.c_str());
  msgTimeText.setText(currentTime.c_str());
  msgDateText.setText(currentDate.c_str());
}
// msg with time
// -------------------------------------
// Time: 12:0%Date: May 4, 2023

// Email: ----- \n
// WiFi: ----, ---

void setConfigurationsTexts() {
  String text = "";
  char currChar;

  String path = "/config.txt";
  File file = SD.open(path, FILE_READ);
  if(!file) {
    Serial.println("Failed to open file for writing");
  } 
  while(file.available()){
    currChar = file.read();
    text.concat(currChar);
  } 
  file.close();

  int delimiter1 = text.indexOf("Email: ");
  int delimiter2 = text.indexOf("\n");
  int delimiter3 = text.indexOf("WiFi: ");
  int delimiter4 = text.indexOf(",");
  int lastIndex = text.length();

  String mailValue = text.substring(delimiter1 + 7, delimiter2);
  String WiFiNameValue = text.substring(delimiter3 + 6, delimiter4);
  String WiFiPassValue = text.substring(delimiter4 + 1, lastIndex);
  
  emailText.setText(mailValue.c_str());
  WiFiText.setText(WiFiNameValue.c_str());
}

NexTouch *nex_listen_list[] = 
{ 
    &messagesBtn,
    &settingsBtn,
    &msgBackBtn,
    &msgNextBtn,
    &msgPrevBtn,
    &settBackBtn,
    &cleanHistBtn,
    &mailBtn,
    &WiFiBtn,
    &infoBtn,
    NULL
};

void messagesBtnPopCallback(void *ptr) {
    dbSerialPrintln("messagesBtn PopCallback");
    MessagesPg.show();
    setupMsgPage();

}

void settingsBtnPopCallback(void *ptr) {
    dbSerialPrintln("settingsBtn PopCallback");
    SettingsPg.show();
    setConfigurationsTexts();
}

void msgBackBtnPopCallback(void *ptr) {
    dbSerialPrintln("msgBackBtn PopCallback");
    HomePage.show();
}

void settBackBtnPopCallback(void *ptr) {
  dbSerialPrintln("settBackBtn PopCallback");
  HomePage.show();
}

void msgNextBtnPopCallback(void *ptr) {
  dbSerialPrintln("msgNextBtn PopCallback");
  if (currNum < maxNum) {
    currNum = currNum + 1;
    showCurrMsg();
  }
}

void msgPrevBtnPopCallback(void *ptr) {
  dbSerialPrintln("msgPrevBtn PopCallback");
  if (currNum > minNum) {
    currNum = currNum - 1;
    showCurrMsg();
  }
}

void setDate() {
  if(timeCounter < timeMaxCounter) {
    timeCounter = timeCounter + 1;
  } else {
    timeText.setText(setHomeScreenTime().c_str());
    dateText.setText(setHomeScreenDate().c_str());
    timeCounter = 0;
  }
}

void setupNextion() {
  nexInit();     
  messagesBtn.attachPop(messagesBtnPopCallback);
  settingsBtn.attachPop(settingsBtnPopCallback);
  msgBackBtn.attachPop(msgBackBtnPopCallback);
  settBackBtn.attachPop(settBackBtnPopCallback);
  msgNextBtn.attachPop(msgNextBtnPopCallback);
  msgPrevBtn.attachPop(msgPrevBtnPopCallback);
  dbSerialPrintln("setup done");
}

void observeNextion() {
  nexLoop(nex_listen_list);
}
