#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/core/log.h"
#include "Arduino.h"

# Namespace definition
namespace esphome {
namespace sonoff_l1 {

class sonoff_l1 : public Component, public light::LightOutput, public uart::UARTDevice {
//class sonoff_l1 : public Component {

  public:

      // Constructor -- SonoffL1() = default;
      sonoff_l1();

      void setup() override;

      void setup_state(light::LightState *state) override;
      void write_state(light::LightState *state) override;
      light::LightTraits get_traits() override;

      void dump_config() override;

      // Effect methods (for use from YAML lambdas)
      void set_mode_colorful();
      void set_mode_colorful_gradient();
      void set_mode_colorful_breath();
      void set_mode_diy_gradient();
      void set_mode_diy_pulse();
      void set_mode_diy_breath();
      void set_mode_diy_strobe();
      void set_mode_rgb_gradient();
      void set_mode_rgb_pulse();
      void set_mode_rgb_breath();
      void set_mode_rgb_strobe();
      void set_mode_sync_to_music(int sensitive = 10, int speed = 50);

  protected:
    # Internal fields definition
    void send_update_(const char *payload);
    bool initialized_{false};

    light::LightState *state_ { nullptr };

};

}  //namespace sphome-sonoff-l1
}  //namespace esphome
