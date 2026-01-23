#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/light/light_effect.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"

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

// Effect classes
class ColorfulEffect : public light::LightEffect {
 public:
  explicit ColorfulEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_colorful();
  }
};

class ColorfulGradientEffect : public light::LightEffect {
 public:
  explicit ColorfulGradientEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_colorful_gradient();
  }
};

class ColorfulBreathEffect : public light::LightEffect {
 public:
  explicit ColorfulBreathEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_colorful_breath();
  }
};

class DiyGradientEffect : public light::LightEffect {
 public:
  explicit DiyGradientEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_diy_gradient();
  }
};

class DiyPulseEffect : public light::LightEffect {
 public:
  explicit DiyPulseEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_diy_pulse();
  }
};

class DiyBreathEffect : public light::LightEffect {
 public:
  explicit DiyBreathEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_diy_breath();
  }
};

class DiyStrobeEffect : public light::LightEffect {
 public:
  explicit DiyStrobeEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_diy_strobe();
  }
};

class RgbGradientEffect : public light::LightEffect {
 public:
  explicit RgbGradientEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_rgb_gradient();
  }
};

class RgbPulseEffect : public light::LightEffect {
 public:
  explicit RgbPulseEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_rgb_pulse();
  }
};

class RgbBreathEffect : public light::LightEffect {
 public:
  explicit RgbBreathEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_rgb_breath();
  }
};

class RgbStrobeEffect : public light::LightEffect {
 public:
  explicit RgbStrobeEffect(const std::string &name) : LightEffect(name) {}
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_rgb_strobe();
  }
};

class SyncToMusicEffect : public light::LightEffect {
 public:
  explicit SyncToMusicEffect(const std::string &name) : LightEffect(name) {}
  
  void set_sensitive(int sensitive) { this->sensitive_ = sensitive; }
  void set_speed(int speed) { this->speed_ = speed; }
  
  void apply() override {
    auto *sonoff = static_cast<SonoffL1 *>(this->state_->get_output());
    sonoff->set_mode_sync_to_music(this->sensitive_, this->speed_);
  }
  
 protected:
  int sensitive_{10};
  int speed_{50};
};

}  // namespace sonoff_l1
}  // namespace esphome