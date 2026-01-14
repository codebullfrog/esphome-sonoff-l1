#include "sonoff_l1.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sonoff_l1 {

static const char *const TAG = "sonoff_l1";

void SonoffL1::write_state(light::LightState *state) {
  float r, g, b;
  state->current_values_as_rgb(&r, &g, &b);

  int ri = int(r * 255.0f);
  int gi = int(g * 255.0f);
  int bi = int(b * 255.0f);

  ESP_LOGD(TAG, "Setting RGB: %d %d %d", ri, gi, bi);

  // Example:
  // this->send_at_command("AT+COLOR=%02X%02X%02X", ri, gi, bi);
}

// Keep your mode functions if you want them later
void SonoffL1::set_mode_gradient() { ESP_LOGD(TAG, "gradient"); }
void SonoffL1::set_mode_breath() { ESP_LOGD(TAG, "breath"); }
void SonoffL1::set_mode_rgb_gradient() { ESP_LOGD(TAG, "rgb_gradient"); }
void SonoffL1::set_mode_rgb_pulse() { ESP_LOGD(TAG, "rgb_pulse"); }
void SonoffL1::set_mode_rgb_breath() { ESP_LOGD(TAG, "rgb_breath"); }
void SonoffL1::set_mode_rgb_strobe() { ESP_LOGD(TAG, "rgb_strobe"); }
void SonoffL1::set_mode_sync() { ESP_LOGD(TAG, "sync"); }

}  // namespace sonoff_l1
}  // namespace esphome
