/**
   @file streams-generator-audiokit.ino
   @brief Tesing I2S output on audiokit
   @author Phil Schatzmann
   @copyright GPLv3
*/

#include "AudioTools.h"
#include "AudioLibs/AudioKit.h"

uint16_t sample_rate = 16000;
uint8_t channels = 2;                                      // The stream will have 2 channels
SineWaveGenerator<int16_t> sineWave(32000);                // subclass of SoundGenerator with max amplitude of 32000
GeneratedSoundStream<int16_t> sound(sineWave);             // Stream generated from sine wave
AudioKitStream out;
StreamCopy copier(out, sound);                             // copies sound into i2s
int vol=0;
int i=0;
// Arduino Setup
void setup(void) {
  LOGLEVEL_AUDIOKIT = AudioKitError;
  // Open Serial
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // start I2S
  Serial.println("starting I2S...");
  auto config = out.defaultConfig(TX_MODE);
  config.sample_rate = sample_rate;
  config.channels = channels;
  config.bits_per_sample = 16;
  out.begin(config);

  // Setup sine wave
  sineWave.begin(channels, sample_rate, 10000);
  Serial.println("started...");
}

// Arduino loop - copy sound to out
void loop() {
  copier.copy();
  i++;
  if (i > 10) {
    vol++;
    bool hi=out.setVolume(vol);
    i = 0;
    Serial.println(vol);
  }
}