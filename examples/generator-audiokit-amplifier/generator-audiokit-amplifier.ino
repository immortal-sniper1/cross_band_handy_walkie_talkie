/**
   @file streams-generator-audiokit.ino
   @brief Tesing I2S output on the cross band handy walkie talkie: autoput to amplifier 
   Using:
- - https://github.com/pschatzmann/arduino-audio-tools
- - https://github.com/pschatzmann/arduino-audiokit 

   @author Phil Schatzmann
   @copyright GPLv3
*/

#include "AudioTools.h"
#include "AudioLibs/AudioKit.h"
#include "WalkieTalkie.h"

AudioInfo info(32000, 2, 16);
SineWaveGenerator<int16_t> sineWave(32000);                // subclass of SoundGenerator with max amplitude of 32000
GeneratedSoundStream<int16_t> sound(sineWave);             // Stream generated from sine wave
AudioKitStream out;
StreamCopy copier(out, sound);                             // copies sound into i2s
WalkieTalkie walkietalkie;  

// Arduino Setup
void setup(void) {
  // Open Serial
  Serial.begin(115200);
  while(!Serial);
  // setup logger
  AudioLogger::instance().begin(Serial, AudioLogger::Info);
  //LOGLEVEL_AUDIOKIT = AudioKitDebug;

  // start I2S
  Serial.println("starting I2S...");
  auto config = out.defaultConfig(TX_MODE);
  config.copyFrom(info);
  config.sd_active = false;
  config.default_actions_active = false;
  // shortcut to define the relevant pins
  walkietalkie.setupPins(config);
  out.begin(config);
  out.setVolume(1.0); // max volume

  // activate amplifiers
  walkietalkie.setupAmplifier(true,true, true, true);

  // Setup sine wave
  sineWave.begin(info, N_B4);
  Serial.println("started...");
}

// Arduino loop - copy sound to out
void loop() {
  copier.copy();
}