#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"

namespace esphome {
namespace sonoff_l1 {

class SonoffL1 : public Component, public light::LightOutput {
 public:
  void write_state(light::LightState *state) override;

  // REQUIRED to make the class non-abstract
  light::LightTraits get_traits() override;

  // Optional mode helpers
  void set_mode_gradient();
  void set_mode_breath();
  void set_mode_rgb_gradient();
  void set_mode_rgb_pulse();
  void set_mode_rgb_breath();
  void set_mode_rgb_strobe();
  void set_mode_sync();
};

}  // namespace sonoff_l1
}  // namespace esphome
