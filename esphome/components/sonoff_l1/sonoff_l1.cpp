#include "sonoff_l1.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sonoff_l1 {

static const char *const TAG = "sonoff_l1";

void SonoffL1::setup() {
  // Delay UART usage until WiFi + API are fully initialized
  App.schedule_callback([this]() {
    ESP_LOGI(TAG, "Sonoff L1 UART initialized");
    this->initialized_ = true;
  });
}

light::LightTraits SonoffL1::get_traits() {
  light::LightTraits traits;
  traits.set_supported_color_modes({light::ColorMode::RGB});
  return traits;
}

void SonoffL1::send_update(const char *payload) {
  if (!this->initialized_) {
    ESP_LOGW(TAG, "UART not ready, skipping send");
    return;
  }

  this->write_str(payload);
  this->write_byte(0x1B);  // Sonoff L1 terminator
}

void SonoffL1::write_state(light::LightState *state) {
  if (!this->initialized_) return;

  float r, g, b;
  state->current_values_as_rgb(&r, &g, &b);

  int ri = int(r * 255);
  int gi = int(g * 255);
  int bi = int(b * 255);

  bool on;
  state->current_values_as_binary(&on);

  float br;
  state->current_values_as_brightness(&br);
  int brightness = int(br * 100);

  char buffer[180];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"switch\":\"%s\",\"light_type\":1,"
           "\"colorR\":%d,\"colorG\":%d,\"colorB\":%d,\"bright\":%d,\"mode\":%d",
           millis(), millis() % 1000,
           on ? "on" : "off",
           ri, gi, bi,
           brightness,
           MODE_COLORFUL);

  ESP_LOGD(TAG, "Sending update: %s", buffer);
  send_update(buffer);
}

void SonoffL1::set_mode_gradient() {
  if (!this->initialized_) return;

  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_COLORFUL_GRADIENT);
  send_update(buffer);
}

void SonoffL1::set_mode_breath() {
  if (!this->initialized_) return;

  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_COLORFUL_BREATH);
  send_update(buffer);
}

void SonoffL1::set_mode_rgb_gradient() {
  if (!this->initialized_) return;

  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_RGB_GRADIENT);
  send_update(buffer);
}

void SonoffL1::set_mode_rgb_pulse() {
  if (!this->initialized_) return;

  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_RGB_PULSE);
  send_update(buffer);
}

void SonoffL1::set_mode_rgb_breath() {
  if (!this->initialized_) return;

  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_RGB_BREATH);
  send_update(buffer);
}

void SonoffL1::set_mode_rgb_strobe() {
  if (!this->initialized_) return;

  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_RGB_STROBE);
  send_update(buffer);
}

void SonoffL1::set_mode_sync(int sensitive, int speed) {
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d,\"sensitive\":%d,\"speed\":%d",
           millis(), millis() % 1000,
           MODE_SYNC_TO_MUSIC,
           sensitive, speed);
  send_update(buffer);
}

}  // namespace sonoff_l1
}  // namespace esphome
