#include "sonoff_l1.h"
#include "esphome/core/log.h"

namespace sonoff_l1 {

static const char *TAG = "sonoff_l1";

#define SONOFF_L1_MODE_COLORFUL           1
#define SONOFF_L1_MODE_COLORFUL_GRADIENT  2
#define SONOFF_L1_MODE_COLORFUL_BREATH    3
#define SONOFF_L1_MODE_DIY_GRADIENT       4
#define SONOFF_L1_MODE_DIY_PULSE          5
#define SONOFF_L1_MODE_DIY_BREATH         6
#define SONOFF_L1_MODE_DIY_STROBE         7
#define SONOFF_L1_MODE_RGB_GRADIENT       8
#define SONOFF_L1_MODE_RGB_PULSE          9
#define SONOFF_L1_MODE_RGB_BREATH        10
#define SONOFF_L1_MODE_RGB_STROBE        11
#define SONOFF_L1_MODE_SYNC_TO_MUSIC     12

void SonoffL1::setup() {
  Serial.begin(19200);
}

LightTraits SonoffL1::get_traits() {
  auto traits = LightTraits();
  traits.set_supported_color_modes({light::ColorMode::RGB});
  return traits;
}

void SonoffL1::write_state(LightState *state) {
  float r, g, b;
  state->current_values_as_rgb(&r, &g, &b);

  int red = int(r * 255);
  int green = int(g * 255);
  int blue = int(b * 255);

  bool on;
  state->current_values_as_binary(&on);

  float brightness_f;
  state->current_values_as_brightness(&brightness_f);
  int brightness = int(brightness_f * 100);

  char buffer[140];
  snprintf_P(buffer, sizeof(buffer),
    PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"switch\":\"%s\",\"light_type\":1,"
         "\"colorR\":%d,\"colorG\":%d,\"colorB\":%d,\"bright\":%d,\"mode\":%d"),
    millis(), millis() % 1000,
    on ? "on" : "off",
    red, green, blue,
    brightness,
    SONOFF_L1_MODE_COLORFUL);

  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
}

void SonoffL1::set_mode_gradient() {
  char buffer[80];
  snprintf_P(buffer, sizeof(buffer),
    PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis() % 1000,
    SONOFF_L1_MODE_COLORFUL_GRADIENT);
  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
}

void SonoffL1::set_mode_breath() {
  char buffer[80];
  snprintf_P(buffer, sizeof(buffer),
    PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis() % 1000,
    SONOFF_L1_MODE_COLORFUL_BREATH);
  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
}

void SonoffL1::set_mode_rgb_gradient() {
  char buffer[80];
  snprintf_P(buffer, sizeof(buffer),
    PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis() % 1000,
    SONOFF_L1_MODE_RGB_GRADIENT);
  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
}

void SonoffL1::set_mode_rgb_pulse() {
  char buffer[80];
  snprintf_P(buffer, sizeof(buffer),
    PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis() % 1000,
    SONOFF_L1_MODE_RGB_PULSE);
  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
}

void SonoffL1::set_mode_rgb_breath() {
  char buffer[80];
  snprintf_P(buffer, sizeof(buffer),
    PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis() % 1000,
    SONOFF_L1_MODE_RGB_BREATH);
  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
}

void SonoffL1::set_mode_rgb_strobe() {
  char buffer[80];
  snprintf_P(buffer, sizeof(buffer),
    PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d"),
    millis(), millis() % 1000,
    SONOFF_L1_MODE_RGB_STROBE);
  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
}

void SonoffL1::set_mode_sync(int sensitive, int speed) {
  char buffer[100];
  snprintf_P(buffer, sizeof(buffer),
    PSTR("AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d,\"sensitive\":%d,\"speed\":%d"),
    millis(), millis() % 1000,
    SONOFF_L1_MODE_SYNC_TO_MUSIC,
    sensitive, speed);
  Serial.print(buffer);
  Serial.write(0x1B);
  Serial.flush();
}

}  // namespace sonoff_l1
