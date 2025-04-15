/* Author : Salome Sulkhanishvili */

#include "CameraModule.h"

//GPIO pin for OV7670
const int SIOD = 21; //SDA
const int SIOC = 22; //SCL

const int VSYNC = 34;
const int HREF = 35;

const int XCLK = 32;
const int PCLK = 33;

//data pins
const int D0 = 27;
const int D1 = 26;
const int D2 = 4;   
const int D3 = 25;  
const int D4 = 14;
const int D5 = 13;   
const int D6 = 12;
const int D7 = 15; 

OV7670 *camera;
unsigned char bmpHeader[BMP::headerSize];
int pictureNumber = 0;

void takePicture() {
  int blk_count = 0;
  blk_count = camera->yres/I2SCamera::blockSlice;
  for (int i=0; i<blk_count; i++) {
    if (i == 0) {
      camera->startBlock = 1;
      camera->endBlock = I2SCamera::blockSlice;
      int side = I2SCamera::blockSlice;
      camera->oneFrame();
      camera->startBlock += I2SCamera::blockSlice;
      camera->endBlock   += I2SCamera::blockSlice;
    }
    Serial.println("took Picture!");
  }
}

String savePicture() {
  takePicture();
  delay(1000); 

  pictureNumber = EEPROM.read(0);
  String path = "/picture" + String(pictureNumber) + ".bmp";
  Serial.printf("Picture file name: %s\n", path.c_str());
  int side = I2SCamera::blockSlice;
  File file = SD.open(path, FILE_WRITE);

  if(!file){
    Serial.println("Failed to open file for writing");
    return "";
  }

  for (int i = 0; i <BMP::headerSize; i++) {    
    file.write(bmpHeader[i]);
  }
  for (int i = 0; i <camera->xres * camera->yres * 2; i++) {
    file.write(camera->frame[i]);
  }
  file.close();
  Serial.println("saved Picture!");
  Serial.println("-------------------------\n");

  return path;
}

void setupCamera(){
  Serial.printf("setupCamera");
  int blk_count = 0;
  camera = new OV7670(OV7670::Mode::QQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
  BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
  takePicture();
  blk_count = camera->yres/I2SCamera::blockSlice;//30, 60, 120
  for (int i=0; i<blk_count; i++) {
    if (i == 0) {
      camera->startBlock = 1;
      camera->endBlock = I2SCamera::blockSlice;
      int side = I2SCamera::blockSlice;
      camera->oneFrame();
      delay(5000);

      camera->startBlock += I2SCamera::blockSlice;
      camera->endBlock   += I2SCamera::blockSlice;
    }
    Serial.println("took first Picture!");
  }
  Serial.println("camera setup done.");
}

