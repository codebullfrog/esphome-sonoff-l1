#include "sonoff_l1.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sonoff_l1 {

static const char *const TAG = "sonoff_l1";

// ------------------------------------------------------
// LightOutput: write_state()
// ------------------------------------------------------
void SonoffL1::write_state(light::LightState *state) {
  float r, g, b;
  state->current_values_as_rgb(&r, &g, &b);

  // Convert to 0–255
  int ri = int(r * 255.0f);
  int gi = int(g * 255.0f);
  int bi = int(b * 255.0f);

  // Send your existing AT command to set color
  ESP_LOGD(TAG, "Setting RGB: %d %d %d", ri, gi, bi);

  // Example:
  // this->send_at_command("AT+COLOR=%02X%02X%02X", ri, gi, bi);
}

// ------------------------------------------------------
// Effect registration (Option A)
// ------------------------------------------------------
void SonoffL1::add_effect(const std::string &name, const std::string &id) {
  auto *effect = new light::LambdaLightEffect(
      name.c_str(),
      [this, id](light::LightState *state) {
        ESP_LOGD(TAG, "Effect triggered: %s", id.c_str());

        if (id == "gradient")
          this->set_mode_gradient();
        else if (id == "breath")
          this->set_mode_breath();
        else if (id == "rgb_gradient")
          this->set_mode_rgb_gradient();
        else if (id == "rgb_pulse")
          this->set_mode_rgb_pulse();
        else if (id == "rgb_breath")
          this->set_mode_rgb_breath();
        else if (id == "rgb_strobe")
          this->set_mode_rgb_strobe();
        else if (id == "sync")
          this->set_mode_sync();
      });

  this->effects_.push_back(effect);
}

// ------------------------------------------------------
// Your existing serial control methods
// ------------------------------------------------------
void SonoffL1::set_mode_gradient() {
  ESP_LOGD(TAG, "Setting mode: gradient");
  // send_at_command("AT+MODE=GRADIENT");
}

void SonoffL1::set_mode_breath() {
  ESP_LOGD(TAG, "Setting mode: breath");
  // send_at_command("AT+MODE=BREATH");
}

void SonoffL1::set_mode_rgb_gradient() {
  ESP_LOGD(TAG, "Setting mode: rgb_gradient");
  // send_at_command("AT+MODE=RGB_GRADIENT");
}

void SonoffL1::set_mode_rgb_pulse() {
  ESP_LOGD(TAG, "Setting mode: rgb_pulse");
  // send_at_command("AT+MODE=RGB_PULSE");
}

void SonoffL1::set_mode_rgb_breath() {
  ESP_LOGD(TAG, "Setting mode: rgb_breath");
  // send_at_command("AT+MODE=RGB_BREATH");
}

void SonoffL1::set_mode_rgb_strobe() {
  ESP_LOGD(TAG, "Setting mode: rgb_strobe");
  // send_at_command("AT+MODE=RGB_STROBE");
}

void SonoffL1::set_mode_sync() {
  ESP_LOGD(TAG, "Setting mode: sync");
  // send_at_command("AT+MODE=SYNC");
}

}  // namespace sonoff_l1
}  // namespace esphome
