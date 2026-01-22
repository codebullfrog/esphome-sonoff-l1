#include "esphome/core/log.h"
#include "sonoff_l1.h"

namespace esphome {
namespace sonoff_l1 {

static const char *const TAG = "sonoff_l1";
//constants for different modes (from old custom component)
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

sonoff_l1::sonoff_l1() {

}

void sonoff_l1::setup() {
  // Modern ESPHome: use set_timeout instead of App.schedule_callback
  this->set_timeout(10, [this]() {
    ESP_LOGI(TAG, "Initializing Serial for Sonoff L1 at 19200 baud");
    Serial.begin(19200);
    this->initialized_ = true;
  });
}

void setup_state(light::LightState *state) override;
void write_state(light::LightState *state) {
  if (!this->initialized_) return;

  float red, green, blue;
  state->current_values_as_rgb(&red, &green, &blue);

  int red_value = int(red * 255.0f);
  int green_value = int(green * 255.0f);
  int blue_value = int(blue * 255.0f);

  bool led_state;
  state->current_values_as_binary(&led_state);

  float brightness_percent;
  state->current_values_as_brightness(&brightness_percent);
  int brightness = int(brightness_percent * 100.0f);

  char buffer[180];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"switch\":\"%s\",\"light_type\":1,"
           "\"colorR\":%d,\"colorG\":%d,\"colorB\":%d,\"bright\":%d,\"mode\":%d",
           millis(), millis() % 1000,
           led_state ? "on" : "off",
           red_value, green_value, blue_value,
           brightness,
           MODE_COLORFUL);

  ESP_LOGD(TAG, "Sending state update: %s", buffer);
  send_update_(buffer);
}

light::LightTraits SonoffL1::get_traits() {
  light::LightTraits traits;
  traits.set_supported_color_modes({light::ColorMode::RGB});
  return traits;
}

void sonoff_l1::dump_config() {
}

void sonoff_l1::set_mode_colorful(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_COLORFUL);
  send_update_(buffer);
}
void sonoff_l1::set_mode_colorful_gradient(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_COLORFUL_GRADIENT);
  send_update_(buffer);
}
void sonoff_l1::set_mode_colorful_breath(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_COLORFUL_BREATH);
  send_update_(buffer);
}
void sonoff_l1::set_mode_diy_gradient(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_DIY_GRADIENT);
  send_update_(buffer);
}
void sonoff_l1::set_mode_diy_pulse(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_DIY_PULSE);
  send_update_(buffer);
}
void sonoff_l1::set_mode_diy_breath(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_DIY_BREATH);
  send_update_(buffer);
}
void sonoff_l1::set_mode_diy_strobe(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_DIY_STROBE);
  send_update_(buffer);
}
void sonoff_l1::set_mode_rgb_gradient(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_RGB_GRADIENT);
  send_update_(buffer);
}
void sonoff_l1::set_mode_rgb_pulse(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_RGB_PULSE);
  send_update_(buffer);
}
void sonoff_l1::set_mode_rgb_breath(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_RGB_BREATH);
  send_update_(buffer);
}
void sonoff_l1::set_mode_rgb_strobe(){
  if (!this->initialized_) return;

  char buffer[120];
  snprintf(buffer, sizeof(buffer),"AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d",millis(), millis() % 1000,MODE_RGB_STROBE);
  send_update_(buffer);
}
void sonoff_l1::set_mode_sync_to_music(int sensitive = 10, int speed = 50){
  if (!this->initialized_) return;

  char buffer[160];
  snprintf(buffer, sizeof(buffer),
           "AT+UPDATE=\"sequence\":\"%d%03d\",\"mode\":%d,\"sensitive\":%d,\"speed\":%d",millis(), millis() % 1000,MODE_SYNC_TO_MUSIC,sensitive, speed);
  send_update_(buffer);
}

void sonoff_l1::send_update_(const char *payload) {
  if (!this->initialized_) {
    ESP_LOGW(TAG, "Sonoff L1 not initialized yet, skipping send");
    return;
  }

  Serial.print(payload);
  Serial.write(0x1B);  // Sonoff L1 terminator
  Serial.flush();
}


}  // namespace sonoff_l1
}  // namespace esphome
