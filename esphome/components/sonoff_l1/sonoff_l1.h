#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace sonoff_l1 {

class SonoffL1 : public Component, public light::LightOutput, public uart::UARTDevice {
 public:
  // Mode constants
  static const int MODE_COLORFUL = 1;
  static const int MODE_COLORFUL_GRADIENT = 2;
  static const int MODE_COLORFUL_BREATH = 3;
  static const int MODE_DIY_GRADIENT = 4;
  static const int MODE_DIY_PULSE = 5;
  static const int MODE_DIY_BREATH = 6;
  static const int MODE_DIY_STROBE = 7;
  static const int MODE_RGB_GRADIENT = 8;
  static const int MODE_RGB_PULSE = 9;
  static const int MODE_RGB_BREATH = 10;
  static const int MODE_RGB_STROBE = 11;
  static const int MODE_SYNC_TO_MUSIC = 12;

  void setup() override {
    // UART is already initialized by ESPHome
  }

  light::LightTraits get_traits() override {
    light::LightTraits traits;
    traits.set_supported_color_modes({light::ColorMode::RGB});
    return traits;
  }

  void write_state(light::LightState *state) override {
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

    char buffer[140];
    snprintf(buffer, sizeof(buffer),
             "AT+UPDATE=\"sequence\":\"%d%03d\",\"switch\":\"%s\",\"light_type\":1,"
             "\"colorR\":%d,\"colorG\":%d,\"colorB\":%d,\"bright\":%d,\"mode\":%d",
             millis(), millis() % 1000,
             on ? "on" : "off",
             ri, gi, bi,
             brightness,
             MODE_COLORFUL);

    this->write_str(buffer);
    this->write_byte(0x1B);
  }

  // Effect methods
  void set_mode(int mode) {
    char buffer[140];
    snprintf(buffer, sizeof(buffer),
             "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",
             millis(), millis() % 1000,
             mode);

    this->write_str(buffer);
    this->write_byte(0x1B);
  }

  void setModeGradient() { set_mode(MODE_COLORFUL_GRADIENT); }
  void setModeBreath() { set_mode(MODE_COLORFUL_BREATH); }
  void setModeRGBGradient() { set_mode(MODE_RGB_GRADIENT); }
  void setModeRGBPulse() { set_mode(MODE_RGB_PULSE); }
  void setModeRGBBreath() { set_mode(MODE_RGB_BREATH); }
  void setModeRGBStrobe() { set_mode(MODE_RGB_STROBE); }
  void setModeSync(int sensitive = 10, int speed = 50) {
    char buffer[140];
    snprintf(buffer, sizeof(buffer),
             "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d,\"sensitive\":%d,\"speed\":%d",
             millis(), millis() % 1000,
             MODE_SYNC_TO_MUSIC,
             sensitive, speed);

    this->write_str(buffer);
    this->write_byte(0x1B);
  }
};

}  // namespace sonoff_l1
}  // namespace esphome
