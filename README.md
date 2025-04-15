# TELLME - A Smart Message Device for Homeowners

TELLME is a compact and smart device I developed to enhance the way strangers can leave messages for homeowners when they’re not at home. Instead of the traditional method of writing a note and leaving it on the door, TELLME allows secure, private, and real-time communication via **Bluetooth Low Energy (BLE)** and **WiFi**. It also captures the sender’s image and emails both the text and photo directly to the homeowner.

---

## 📌 _Introduction_

In today's world, where smartphones are central to our communication, I saw a gap in how strangers communicate with homeowners who are unavailable. The typical paper note is neither secure nor reliable. So, I developed **TELLME**, a device that allows people to leave a message through their phone using BLE.

This message is then:
- Saved securely on an SD card,
- Displayed on a **Nextion LCD touchscreen** inside the house,
- And sent via email to the homeowner (if WiFi is available), along with a **photo of the sender** captured by the device’s camera.

---

## 🧠 _Key Features_

- **Bluetooth Low Energy (BLE)** support for Android and iOS
- **Real-time message delivery via email**
- **Photo capture of the sender for identification**
- **Touchscreen interface for viewing messages**
- **Secure offline message storage on SD card**
- **WiFi configuration and email setup via BLE**
- **Real-Time Clock (RTC)** for timestamping messages
- **3D-printed enclosure with integrated camera and display**

---

## 🧰 _Component Design_

### ⚙️ **ESP32 (WiFi + BLE)**
I used the **ESP32 D-Wroom** microcontroller, which acts as the heart of the system. It handles BLE communication, WiFi connectivity, email transmission, image capturing, and interaction with other modules.

<img width="196" alt="Screenshot 2025-04-15 at 13 16 27" src="https://github.com/user-attachments/assets/98c5aa26-8ce8-4114-be0b-f69c134cb0a2" />

### 📡 **Bluetooth Low Energy (BLE)**
BLE enables secure, energy-efficient message transmission from any smartphone. After each message is received, BLE is temporarily disabled to allow WiFi communication for sending the email. Once the email is sent, BLE is re-enabled.

**WiFi & Email Configuration via BLE**:
- To change WiFi:  
  `WiFi:NAME:{your_WiFi_name},PASS:{your_WiFi_password}`
- To change Email:  
  `EMAIL:youremail@example.com`

### 🌐 **WiFi Module**
The ESP32’s integrated WiFi module is used to send emails using the **ESP-Mail-Client** library over **SMTP**. WiFi credentials are stored on the SD card for persistence.

---

## 💻 _Touchscreen Interface_

### 🖥️ **Nextion 4.3” HMI LCD Display**
I used the **NX4827T043** resistive touchscreen for ease of use even with gloves. It connects via UART to the ESP32 and displays:
- Home screen
- Message logs
- Settings page

<img width="210" alt="Screenshot 2025-04-15 at 13 17 01" src="https://github.com/user-attachments/assets/6c216e80-2b2e-409d-93a7-575f75ec5ef4" />

I designed the interface using **Nextion Editor**, allowing smooth page transitions and clear layout.

<img width="393" alt="Screenshot 2025-04-15 at 13 17 51" src="https://github.com/user-attachments/assets/cd6f682a-50ca-4a2f-8d58-7a5621d73262" />

---

## 🧠 _Storage & Real-Time Clock_

### 💾 **MicroSD Card Module**
All messages, captured images, and configuration data (WiFi & Email) are stored on the SD card. This ensures data isn’t lost during power outages.

### ⏱️ **RTC Module**
A Real-Time Clock (RTC) module keeps track of the exact timestamp for every message, even if the device is powered off. The timestamp is shown next to each message and included in the email.

<img width="202" alt="Screenshot 2025-04-15 at 13 18 25" src="https://github.com/user-attachments/assets/6fb76b84-d3b8-49e5-a2cf-a9f1564f38b0" />

---

## 📷 _Camera Module_

### 🧿 **OV7670 Camera**
The **OV7670 VGA CMOS Camera** captures a photo of the sender when a message is left. It uses **I2C** communication, and I added external pull-up resistors for reliable operation.

Captured images are:
- Stored on the SD card
- Sent to the homeowner via email

<img width="239" alt="Screenshot 2025-04-15 at 13 21 42" src="https://github.com/user-attachments/assets/3f26d846-c300-4e05-8419-7a6c92b9d99f" />


### Picture taken using OV7670:
<img width="128" alt="Screenshot 2025-04-15 at 13 22 58" src="https://github.com/user-attachments/assets/97356be6-cf14-4a61-9861-3dc92c63b52a" />


---

## 📧 _Received messages from TELLME device_
<img width="475" alt="Screenshot 2025-04-15 at 13 19 41" src="https://github.com/user-attachments/assets/fd1791d3-20d7-4db7-8ae1-75ac48a289e1" />

---

## 🧩 _Circuit and PCB Design_

My friend assisted me in designing and printing a custom **PCB** using **EasyEDA**, which integrates all components into a compact and efficient layout.

- **ESP32** handles all communication
- **Nextion LCD** connected via UART
- **Camera & RTC** via I2C (with shared pull-up resistors)
- **SD Card** via SPI
- All components powered via 3.3V or 5V rails from the ESP32

The final PCB layout includes headers for programming and debugging, making it easier to test and iterate on the design.

<img width="611" alt="Screenshot 2025-04-15 at 13 24 05" src="https://github.com/user-attachments/assets/0f017505-60b4-418a-9a7c-404ca4f178dc" />

<img width="465" alt="Screenshot 2025-04-15 at 13 24 31" src="https://github.com/user-attachments/assets/5b1d3ace-d7ce-43f7-b6b4-d65153a6dd8b" />

<img width="466" alt="Screenshot 2025-04-15 at 13 24 50" src="https://github.com/user-attachments/assets/ddfcdc14-1ae7-4267-b0bd-90a58d34ac44" />

## 🧱 _Device Enclosure & Mounting_

I created a **3D-printed box** that:
- Houses all the components and the PCB
- Has an external viewable touchscreen
- Includes a small peephole for the camera
- Can be mounted on the inside of a door
- Requires only a power connection to function

I also designed a **sticker** indicating the presence of the TELLME device to inform visitors.

<img width="251" alt="Screenshot 2025-04-15 at 13 25 08" src="https://github.com/user-attachments/assets/d1165411-12e3-4bdd-8033-62d9fe0f171d" />
<br>

<img width="400" alt="Screenshot 2025-04-15 at 13 25 34" src="https://github.com/user-attachments/assets/36c2944f-a297-4ff5-9770-8b8e13607e37" />

<img width="400" alt="Screenshot 2025-04-15 at 13 25 50" src="https://github.com/user-attachments/assets/3250f5f7-fbcc-41b4-8478-3bd520a7b323" />

---

## ✅ _Conclusion_

TELLME is my attempt at modernizing anonymous message communication between strangers and homeowners. By combining BLE, WiFi, and a camera module, I created a device that ensures:
- Confidentiality
- Security
- Real-time delivery
- Easy installation and usage
