/* Author : Salome Sulkhanishvili */

#include "EmailModule.h"

/* The SMTP Session object used for Email sending */
SMTPSession smtp;

/* Recipient's email*/
String RECIPIENT_EMAIL = "sulkhanishvili767@gmail.com";

/* The WiFi credentials */
char WIFI_SSID[50] = "TEST_WIFI"; 
char WIFI_PASSWORD[50] = "TEST_PASSWORD";


void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  if (!SPIFFS.begin()) {
    Serial.println("An error has occurred while mounting the filesystem");
  }
  else{
    Serial.println("Filesystem mounted successfully");
  }
}

void deinitWiFi() {
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF); 
}

void sendEmail(String msg, String filePathName) { 
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED)
  {
    setupWiFi();
    WiFi.mode(WIFI_STA);
    delay(1000);
  }
  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;

  /* Enable the chunked data transfer with pipelining for large message if server supported */
  message.enable.chunking = true;

  /* Set the message headers */
  message.sender.name = "TELLME";
  message.sender.email = AUTHOR_EMAIL;

  message.subject = "TELLME - New Message";
  message.addRecipient("User", RECIPIENT_EMAIL);

  message.html.content = msg.c_str();
  message.html.charSet = "utf-8";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_qp;

  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_normal;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  /* The attachment data item */
  SMTP_Attachment att;

  /* Set the attachment info */
  att.descr.filename = filePathName;
  att.descr.mime = filePathName; //  + "/bmp";
  att.file.path = filePathName;
  att.file.storage_type = esp_mail_file_storage_type_sd;
  att.descr.transfer_encoding = Content_Transfer_Encoding::enc_base64;

  /* Add attachment to the message */
  message.addAttachment(att);

  /* Reset attachment to the message */
  message.resetAttachItem(att);

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending the Email and close the session */
  if (!MailClient.sendMail(&smtp, &message, true))
    Serial.println("Error sending Email, " + smtp.errorReason());
}

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++){
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
    }
    Serial.println("----------------\n");
  }
}

void changeSettings(CommandOption cmd, String newValue) {
  if (cmd == changeMail) {
    Serial.print(newValue);
    RECIPIENT_EMAIL = newValue;
    Serial.println("changed Email");
  }
  else if (cmd == changeWiFi) {
    changePassword(newValue);
  }
}

void changePassword(String newValue) {
  int delimiter = newValue.indexOf(",");
  int lastIndex = newValue.length();

  String name = newValue.substring(0, delimiter);
  String pass = newValue.substring(delimiter + 1, lastIndex);

  if (name.indexOf("NAME:") >= 0) {
    name.replace("NAME:", "");

    Serial.print("NAME: ");
    Serial.println(name);
    name.toCharArray(WIFI_SSID, name.length() + 1);
  }

    if (pass.indexOf("PASS:") >= 0) {
    pass.replace("PASS:", "");

    Serial.print("PASS: ");
    Serial.println(pass);
    pass.toCharArray(WIFI_PASSWORD, pass.length() + 1);
  }
  Serial.println("changed WiFi");
}
