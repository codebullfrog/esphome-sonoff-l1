#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/core/log.h"
#include "Arduino.h"

namespace esphome {
namespace sonoff_l1 {

class SonoffL1 : public Component, public light::LightOutput {
 public:
  // Mode constants (same as original)
  static const int MODE_COLORFUL = 1;
  static const int MODE_COLORFUL_GRADIENT = 2;
  static const int MODE_COLORFUL_BREATH = 3;
  static const int MODE_DIY_GRADIENT = 4;
  static const int MODE_DIY_PULSE = 5;
  static const int MODE_DIY_BREATH = 6;
  static const int MODE_DIY_STROBE = 7;
  static const int MODE_RGB_GRADIENT = 8;
  static const int MODE_RGB_PULSE = 9;
  static const int MODE_RGB_BREATH = 10;
  static const int MODE_RGB_STROBE = 11;
  static const int MODE_SYNC_TO_MUSIC = 12;

  SonoffL1() = default;

  void setup() override;
  light::LightTraits get_traits() override;
  void write_state(light::LightState *state) override;

  // Effect methods (for use from YAML lambdas)
  void set_mode_gradient();
  void set_mode_breath();
  void set_mode_rgb_gradient();
  void set_mode_rgb_pulse();
  void set_mode_rgb_breath();
  void set_mode_rgb_strobe();
  void set_mode_sync(int sensitive = 10, int speed = 50);

 protected:
  void send_update_(const char *payload);

  bool initialized_{false};
};

}  // namespace sonoff_l1
}  // namespace esphome
