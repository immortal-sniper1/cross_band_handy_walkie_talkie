
/**
   @file test-sdmmc.ino
   @brief testing the initialization of the sd_mmc drive: both 1 bit and 4 bit modes are working
   @author Phil Schatzmann
   @copyright GPLv3
*/

#include "FS.h"
#include "SD_MMC.h"

#define DATA_0 42
#define DATA_1 41
#define DATA_2 1
#define DATA_3 2
#define CMD 43
#define CLK 44
#define CARD_DETECT 40

bool mode1bit;
bool format_on_mount_failed = true;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  SD_MMC.setPins(CLK, CMD, DATA_0, DATA_1, DATA_2, DATA_3);
  mode1bit = false;
  //SD_MMC.setPins(CLK, CMD, DATA_0); 
  //mode1bit = true;
}

void loop() {
  // check SD drive
  if (SD_MMC.begin("/sdcard", mode1bit, format_on_mount_failed)) {
    Serial.println("SD begin was successful");
  } else {
    Serial.println("Card Mount Failed");
  }
  delay(2000);
}