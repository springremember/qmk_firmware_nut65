#include "rgblight.h"

#define RGBLIGHT_RAINBOW_SWIRL_RANGE 255

extern rgblight_config_t rgblight_config;
extern rgb_led_t led[RGBLIGHT_LED_COUNT];

const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {25, 20, 15, 10, 5};
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {15, 10, 7, 5, 3};
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {15, 10, 7, 5, 3};
extern void sethsv(uint8_t hue, uint8_t sat, uint8_t val, rgb_led_t *led1);
