#include "sonoff_l1.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sonoff_l1 {

static const char *const TAG = "sonoff_l1";

void SonoffL1::send_update(const char *payload) {
  this->write_str(payload);
  this->write_byte(0x1B);  // Sonoff L1 terminator
}

light::LightTraits SonoffL1::get_traits() {
  light::LightTraits traits;
  traits.set_supported_color_modes({light::ColorMode::RGB});
  return traits;
}

void SonoffL1::write_state(light::LightState *state) {
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
  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_COLORFUL_GRADIENT);
  send_update(buffer);
}

void SonoffL1::set_mode_breath() {
  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_COLORFUL_BREATH);
  send_update(buffer);
}

void SonoffL1::set_mode_rgb_gradient() {
  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_RGB_GRADIENT);
  send_update(buffer);
}

void SonoffL1::set_mode_rgb_pulse() {
  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_RGB_PULSE);
  send_update(buffer);
}

void SonoffL1::set_mode_rgb_breath() {
  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_RGB_BREATH);
  send_update(buffer);
}

void SonoffL1::set_mode_rgb_strobe() {
  char buffer[80];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
           millis(), millis() % 1000,
           MODE_RGB_STROBE);
  send_update(buffer);
}

void SonoffL1::set_mode_sync(int sensitive, int speed) {
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
