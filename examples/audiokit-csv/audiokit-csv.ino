/**
 * @file streams-audiokit-audiokit.ino
 * @brief Copies the audio form the input (microphone) to the serial output
   Using:
- - https://github.com/pschatzmann/arduino-audio-tools
- - https://github.com/pschatzmann/arduino-audiokit 
 * @author Phil Schatzmann
 * @copyright GPLv3
 */

#include "AudioTools.h"
#include "AudioLibs/AudioKit.h"

AudioInfo info(8000, 2, 16);
AudioKitStream kit;           // Access I2S as stream
CsvStream<int16_t> out(Serial, 2);
StreamCopy copier(out, kit);  // copy kit to kit

// Arduino Setup
void setup(void) {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  auto config = kit.defaultConfig(RXTX_MODE);
  config.copyFrom(info);
  config.input_device = AUDIO_HAL_ADC_INPUT_LINE1;
  config.sd_active = false;
  config.default_actions_active = false;
  // i2c
  config.pins.i2c_sda = 36;
  config.pins.i2c_scl = 35;
  //  i2s
  config.pin_mck = 47;
  config.pin_bck = 21;
  config.pin_ws = 12;
  config.pin_data = 14;
  config.pin_data_rx = 11;
  kit.begin(config);
  kit.setVolume(1.0); // max volume

}

// Arduino loop - copy data
void loop() { copier.copy(); }