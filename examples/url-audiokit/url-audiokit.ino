/**
 * @file url_mp3-audiokit.ino
 * @author Phil Schatzmann
 * @brief decode MP3 stream from url and output it on I2S on audiokit
 * @version 0.1
 * Using:
  - https://github.com/pschatzmann/arduino-audio-tools
  - https://github.com/pschatzmann/arduino-audiokit 
  - https://github.com/pschatzmann/arduino-libhelix.git

   @copyright GPLv3
 */

#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"
#include "AudioLibs/AudioKit.h"  


URLStream url("ssid","password");  // or replace with ICYStream to get metadata
AudioKitStream i2s; // final output of decoded stream
EncodedAudioStream dec(&i2s, new MP3DecoderHelix()); // Decoding stream
StreamCopy copier(dec, url); // copy url to decoder


void setup(){
  Serial.begin(115200);
  while(!Serial);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);  

  // setup i2s
  auto config = i2s.defaultConfig(TX_MODE);
  config.sd_active = false;
  config.default_actions_active = false;
  // i2c
  config.pins.i2c_sda = 36;
  config.pins.i2c_scl = 35;
  // i2s
  config.pin_mck = 47;
  config.pin_bck = 21;
  config.pin_ws = 12;
  config.pin_data = 14;
  config.pin_data_rx = 11;
  i2s.begin(config);
  i2s.setVolume(1.0); // max volume

  // setup I2S based on sampling rate provided by decoder
  dec.begin();

  // mp3 radio
  url.begin("http://stream.srg-ssr.ch/m/rsj/mp3_128","audio/mp3");

}

void loop(){
  copier.copy();
}