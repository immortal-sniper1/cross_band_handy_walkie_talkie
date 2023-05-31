/**
 * @file generator-i2s.ino
 * @brief Using the audiotools together with the esp8388 library
   Using:
   - https://github.com/pschatzmann/arduino-audio-tools
   - https://github.com/thaaraak/es8388 
 * @author Andreas Spiess
 * @copyright GPLv3
 */

#include "AudioTools.h"
#include "es8388.h"

AudioInfo info(22000, 2, 16);
SineWaveGenerator<int16_t> sineWave(10000);  // amplitude 1000
GeneratedSoundStream<int16_t> sound(sineWave);   // Stream generated from sine wave
I2SStream out;
StreamCopy copier(out, sound);  // copies sound into i2s

// Arduino Setup
void setup(void) {
  // Open Serial
  Serial.begin(115200);
  while (!Serial);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // Input/Output Modes
  es_dac_output_t output = (es_dac_output_t)(DAC_OUTPUT_LOUT1 | DAC_OUTPUT_LOUT2 
                                          | DAC_OUTPUT_ROUT1 | DAC_OUTPUT_ROUT2);
  es_adc_input_t input = ADC_INPUT_LINPUT2_RINPUT2;
  //  es_adc_input_t input = ADC_INPUT_LINPUT1_RINPUT1;

  TwoWire wire(0);
  wire.setPins(36, 35);

  es8388 codec;
  codec.begin(&wire);
  codec.config(info.bits_per_sample, output, input, 90);

  // start I2S
  Serial.println("starting I2S...");
  auto config = out.defaultConfig(TX_MODE);
  config.copyFrom(info);
  config.pin_mck = 47;
  config.pin_bck = 21;
  config.pin_ws = 12;
  config.pin_data = 14;
  config.pin_data_rx = 11;
  out.begin(config);

  // Setup sine wave
  sineWave.begin(info, N_B4);
  Serial.println("started...");
}

// Arduino loop - copy sound to out
void loop() { copier.copy(); }
