#pragma once
#include "esphome.h"

namespace sonoff_l1 {

class SonoffL1 : public Component, public LightOutput {
 public:
  void setup() override;
  LightTraits get_traits() override;
  void write_state(LightState *state) override;

  // Effect methods
  void set_mode_gradient();
  void set_mode_breath();
  void set_mode_rgb_gradient();
  void set_mode_rgb_pulse();
  void set_mode_rgb_breath();
  void set_mode_rgb_strobe();
  void set_mode_sync(int sensitive = 10, int speed = 50);
};

}  // namespace sonoff_l1
