#include "sonoff_l1.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sonoff_l1 {

static const char *const TAG = "sonoff_l1";

void SonoffL1::write_state(light::LightState *state) {
  // ...
}

light::LightTraits SonoffL1::get_traits() {
  light::LightTraits traits;
  traits.set_supported_color_modes({light::ColorMode::RGB});
  return traits;
}

void SonoffL1::set_mode_gradient() { ESP_LOGD(TAG, "gradient"); }
void SonoffL1::set_mode_breath() { ESP_LOGD(TAG, "breath"); }
void SonoffL1::set_mode_rgb_gradient() { ESP_LOGD(TAG, "rgb_gradient"); }
void SonoffL1::set_mode_rgb_pulse() { ESP_LOGD(TAG, "rgb_pulse"); }
void SonoffL1::set_mode_rgb_breath() { ESP_LOGD(TAG, "rgb_breath"); }
void SonoffL1::set_mode_rgb_strobe() { ESP_LOGD(TAG, "rgb_strobe"); }
void SonoffL1::set_mode_sync() { ESP_LOGD(TAG, "sync"); }

}  // namespace sonoff_l1
}  // namespace esphome
