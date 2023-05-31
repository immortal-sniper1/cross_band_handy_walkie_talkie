/**
   @file generator-audiokit.ino
   @brief Tesing I2S output on the cross band handy walkie talkie: autoput to earphones 
   Using:
  - https://github.com/pschatzmann/arduino-audio-tools
  - https://github.com/pschatzmann/arduino-audiokit 

   @author Phil Schatzmann
   @copyright GPLv3
*/

#include "AudioTools.h"
#include "AudioLibs/AudioKit.h"

AudioInfo info(32000, 2, 16);
SineWaveGenerator<int16_t> sineWave(32000);                // subclass of SoundGenerator with max amplitude of 32000
GeneratedSoundStream<int16_t> sound(sineWave);             // Stream generated from sine wave
AudioKitStream out;
StreamCopy copier(out, sound);                             // copies sound into i2s

// Arduino Setup
void setup(void) {
  // Open Serial
  Serial.begin(115200);
  while(!Serial);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);
  //LOGLEVEL_AUDIOKIT = AudioKitDebug;

  // start I2S
  Serial.println("starting I2S...");
  auto config = out.defaultConfig(TX_MODE);
  config.copyFrom(info);
  config.output_device = AUDIO_HAL_DAC_OUTPUT_ALL; // AUDIO_HAL_DAC_OUTPUT_ALL, AUDIO_HAL_DAC_OUTPUT_LINE1, AUDIO_HAL_DAC_OUTPUT_LINE2
  config.sd_active = false;
  config.default_actions_active = false;
  // i2c
  config.pins.i2c_sda = 36;
  config.pins.i2c_scl = 35;
  // i2s
  config.pin_mck = 47;
  config.pin_bck = 21;
  config.pin_ws = 12;
  //config.pin_data = 14;
  //config.pin_data_rx = 11;
  //config.pin_data = 14;
  //config.pin_data_rx = 11;
  out.begin(config);
  out.setVolume(1.0); // max volume
  
  // Setup sine wave
  sineWave.begin(info, N_B4);
  Serial.println("started...");
}

// Arduino loop - copy sound to out
void loop() {
  copier.copy();
}