/**
   @file test-sd-audiokit.ino
   @brief Testing the SPI SD functionality of the audiokit
   Using:
- - https://github.com/pschatzmann/arduino-audio-tools
- - https://github.com/pschatzmann/arduino-audiokit 

   @author Phil Schatzmann
   @copyright GPLv3
*/
#include "AudioLibs/AudioKit.h"
#include "AudioTools.h"
#include "SD.h"

AudioKitStream out;

// Arduino Setup
void setup(void) {
  // Open Serial
  Serial.begin(115200);
  while (!Serial)
    ;
  AudioLogger::instance().begin(Serial, AudioLogger::Info);
  // LOGLEVEL_AUDIOKIT = AudioKitDebug;

  auto config = out.defaultConfig();
  // i2c
  config.pins.i2c_sda = 36;
  config.pins.i2c_scl = 35;
  // sd
  config.pins.sd_cs = 2;
  config.pins.sd_miso = 42;
  config.pins.sd_mosi = 43;
  config.pins.sd_clk = 44;
  out.begin(config);
}

// Arduino loop - do nothing
void loop() {
  // check SD drive
  if (SD.begin(out.config().pins.sd_cs)) {
    Serial.println("SD begin was successful");
  } else {
    Serial.println("Card Mount Failed");
  }
  delay(2000);
}