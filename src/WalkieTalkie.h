// dummy header file: w/o this the example are not showing up
#pragma once
#include "AudioLibs/AudioKit.h"
#include "AudioTools.h"

/**
 * @brief Some additonal functionality using the custom pins which is not
 * convered by the AudioKit.
 * @author Phil Schatzmann
 * @copyright GPLv3
 */

class WalkieTalkie {
 public:
  WalkieTalkie() {
    pinMode(5, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(6, OUTPUT);
  }

  // @brief setup amplifier and gain pins
  // GPIO 5 and 7 can be used to switch the Amp on/off with a digitalWrite()
  // (low is off, high is on) GPIO 15 and 6 can be used to regulate the volume
  // with the help of an anlogWrite() on analog pins. To get max volume I could
  // also do a digitalWrite(HIGH)
  void setupAmplifier(bool leftOn = true, bool rightOn = true,
                      bool leftGain = true, bool rightGain = true) {
    //  switch left amp on
    digitalWrite(5, leftOn);
    //  switch right amp on
    digitalWrite(7, rightOn);
    // set left gain
    digitalWrite(15, leftGain);
    // set right gain
    digitalWrite(6, rightGain);
  }

  /**
   * @brief Setup pins if you use the AudioKitStream class
   */
  void setupPins(AudioKitStreamConfig &config) {
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
    // sd
    config.pins.sd_cs = 2;
    config.pins.sd_miso = 42;
    config.pins.sd_mosi = 43;
    config.pins.sd_clk = 44;
  }
};