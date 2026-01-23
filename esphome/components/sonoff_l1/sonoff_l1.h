#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"
#include "esphome/core/automation.h"

namespace esphome {
namespace sonoff_l1 {

class SonoffL1 : public light::LightOutput, public uart::UARTDevice, public Component {

  public:

      SonoffL1();

      void setup() override;

      void setup_state(light::LightState *state) override;
      void write_state(light::LightState *state) override;
      light::LightTraits get_traits() override;

      void dump_config() override;

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
    void send_update_(const char *payload);
    bool initialized_{false};

    light::LightState *state_ { nullptr };

};

// Action classes
template<typename... Ts> class SetModeColorfulAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_colorful(); }
};

template<typename... Ts> class SetModeColorfulGradientAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_colorful_gradient(); }
};

template<typename... Ts> class SetModeColorfulBreathAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_colorful_breath(); }
};

template<typename... Ts> class SetModeDiyGradientAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_diy_gradient(); }
};

template<typename... Ts> class SetModeDiyPulseAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_diy_pulse(); }
};

template<typename... Ts> class SetModeDiyBreathAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_diy_breath(); }
};

template<typename... Ts> class SetModeDiyStrobeAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_diy_strobe(); }
};

template<typename... Ts> class SetModeRgbGradientAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_rgb_gradient(); }
};

template<typename... Ts> class SetModeRgbPulseAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_rgb_pulse(); }
};

template<typename... Ts> class SetModeRgbBreathAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_rgb_breath(); }
};

template<typename... Ts> class SetModeRgbStrobeAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    void play(Ts... x) override { this->parent_->set_mode_rgb_strobe(); }
};

template<typename... Ts> class SetModeSyncToMusicAction : public Action<Ts...>, public Parented<SonoffL1> {
  public:
    TEMPLATABLE_VALUE(int, sensitive)
    TEMPLATABLE_VALUE(int, speed)
    
    void play(Ts... x) override { 
      this->parent_->set_mode_sync_to_music(this->sensitive_.value(x...), this->speed_.value(x...)); 
    }
};

}  // namespace sonoff_l1
}  // namespace esphome