#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/light/light_effect.h"

namespace esphome {
namespace sonoff_l1 {

class SonoffL1 : public Component, public light::LightOutput {
 public:
  // Core LightOutput API
  void write_state(light::LightState *state) override;

  // Effect registration (Option A)
  void add_effect(const std::string &name, const std::string &id);

  // Serial control helpers (your existing methods)
  void set_mode_gradient();
  void set_mode_breath();
  void set_mode_rgb_gradient();
  void set_mode_rgb_pulse();
  void set_mode_rgb_breath();
  void set_mode_rgb_strobe();
  void set_mode_sync();

 protected:
  std::vector<light::LightEffect *> effects_;
};

}  // namespace sonoff_l1
}  // namespace esphome
