/**
   @file test-sd.ino
   @brief testing the initialization of the sd drive using SPI

   @author Phil Schatzmann
   @copyright GPLv3
*/
#include "SD.h"
#include "SPI.h"

#define SD_CS 2
#define SD_MISO 42
#define SD_MOSI 43
#define SD_CLK 44

void setup() {
  Serial.begin(115200);
  while (!Serial);

  SPI.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);
}

void loop() {
  // check SD drive
  if (!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
  } else {
    Serial.println("SD begin was successful");
  }
  delay(2000);
}