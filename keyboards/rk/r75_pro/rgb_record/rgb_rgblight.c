// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_rgblight.h"

/* 0.从左往右流光
   1.从右往左流光
   2.从中间往两边流动的流光
   3.静态停止流动的常亮流光
   4.霓虹：红绿蓝黄青紫白顺序循环呼吸
   5.红色常亮
   6.橙色常亮
   7.黄色常亮
   8.绿色常亮
   9.青色常亮
   10.蓝色常亮
   11.紫色常亮
   12.白色常亮
   13.熄灭
*/
#define RGBLED_START_INDEX (RGB_MATRIX_LED_COUNT - RGBLED_NUM)
#define RGBLED_END_INDEX   RGB_MATRIX_LED_COUNT
#define SIDE_LIGHT_MODE_VAI    4

// 亮度档位（0%, 25%, 50%, 75%, 100%）
static const uint8_t brightness_levels[SIDE_LIGHT_MODE_VAI] = {
    // 1,
    (RGBLIGHT_LIMIT_VAL * 25) / 100,
    (RGBLIGHT_LIMIT_VAL * 50) / 100,
    (RGBLIGHT_LIMIT_VAL * 75) / 100,
    RGBLIGHT_LIMIT_VAL
};

static const uint8_t colorful_brightness_levels[SIDE_LIGHT_MODE_VAI] = {
    // 5,
    20,
    32,
    45,
    60
};

static const uint8_t breathe_brightness_levels[SIDE_LIGHT_MODE_VAI] = {
    // 30,
    50,
    80,
    120,
    150
};

static const uint8_t two_color_brightness_levels[SIDE_LIGHT_MODE_VAI] = {
    // 1,
    3,
    5,
    8,
    10
};

static const uint8_t white_brightness_levels[SIDE_LIGHT_MODE_VAI] = {
    // 1,
    3,
    5,
    7,
    9
};

void rgb_light_color_set(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = RGBLED_START_INDEX; i < RGBLED_END_INDEX; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }
}

static uint8_t neon_color_index = 0;
static bool initialized = false;
static uint8_t last_mode = 0xff;
void hs_rgblight_increase(uint8_t rgblight_mode, uint8_t brightness_level) {
    // 限制亮度档位范围
    if (brightness_level > (SIDE_LIGHT_MODE_VAI -1) ) brightness_level = SIDE_LIGHT_MODE_VAI - 1;
    uint8_t rgblight_val = brightness_levels[brightness_level];
    uint8_t colorful_rgblight_val = colorful_brightness_levels[brightness_level];
    uint8_t two_color_rgblight_val = two_color_brightness_levels[brightness_level];
    // if (rgblight_val == 0 || colorful_rgblight_val == 0 || two_color_rgblight_val == 0) {
    //     rgb_light_color_set(0, 0, 0);
    //     return; // 亮度为 0 就直接熄灭
    // }

    if (last_mode != rgblight_mode) {
        last_mode = rgblight_mode;
        initialized = false;
    }

    switch (rgblight_mode) {
        case 0: { // 右→左流光
            static uint16_t rainbow_counter = 0;
            static uint32_t last_update = 0;
            uint32_t interval = 20;

            if (timer_elapsed32(last_update) >= interval) {
                last_update = timer_read32();
                rainbow_counter += 3;
            }

            for (uint8_t i = RGBLED_START_INDEX; i < RGBLED_END_INDEX; i++) {
                uint8_t hue = (rainbow_counter + (RGBLED_NUM - 1 - i) * 8) % 255;
                HSV hsv = { .h = hue, .s = 255, .v = colorful_rgblight_val };
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        } break;

        case 1: { // 左→右流光
            static uint16_t rainbow_counter = 0;
            static uint32_t last_update = 0;
            uint32_t interval = 20;

            if (timer_elapsed32(last_update) >= interval) {
                last_update = timer_read32();
                rainbow_counter += 3;
            }

            for (uint8_t i = RGBLED_START_INDEX; i < RGBLED_END_INDEX; i++) {
                uint8_t hue = (rainbow_counter + i * 8) % 255;
                HSV hsv = { .h = hue, .s = 255, .v = colorful_rgblight_val };
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        } break;

        case 2: { // 中间→两边扩散流光
            static uint16_t rainbow_counter = 0;
            static uint32_t last_update = 0;
            uint32_t interval = 20;
            neon_color_index = 0;

            if (timer_elapsed32(last_update) >= interval) {
                last_update = timer_read32();
                rainbow_counter += 3;
            }

            uint8_t center = RGBLED_NUM / 2;
            for (uint8_t i = 0; i < (RGBLED_END_INDEX - RGBLED_START_INDEX); i++) {
                uint8_t distance = (i > center) ? (i - center) : (center - i);

                int16_t temp = (int16_t)rainbow_counter - (int16_t)(distance * 12);
                if (temp < 0) temp += 255;
                uint8_t hue = temp % 255;

                HSV hsv = { .h = hue, .s = 255, .v = colorful_rgblight_val };
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(i + RGBLED_START_INDEX, rgb.r, rgb.g, rgb.b);
            }
        } break;

        case 3: { // 随机静止流光
            static uint16_t rainbow_counter = 0;
            if (!initialized) {
                initialized = true;

                // 用一个简单的随机扰动生成不同的起始偏移
                static uint32_t random_seed = 12345;
                random_seed ^= (timer_read32() + random_seed * 31);
                rainbow_counter = random_seed % 255;  // 随机起点
            }

            // 和流光一样的色彩分布，只是不动
            for (uint8_t i = RGBLED_START_INDEX; i < RGBLED_END_INDEX; i++) {
                uint8_t hue = (rainbow_counter + (RGBLED_NUM - 1 - i) * 8) % 255;
                HSV hsv = { .h = hue, .s = 255, .v = colorful_rgblight_val };
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        } break;

        case 4: { // 霓虹效果
            static const RGB neon_colors[] = {
                {RGBLIGHT_LIMIT_VAL, 0, 0},                        // 红
                {RGBLIGHT_LIMIT_VAL, RGBLIGHT_LIMIT_VAL / 4, 0},   // 橙
                {RGBLIGHT_LIMIT_VAL, RGBLIGHT_LIMIT_VAL, 0},       // 黄
                {0, RGBLIGHT_LIMIT_VAL, 0},                        // 绿
                {0, RGBLIGHT_LIMIT_VAL, RGBLIGHT_LIMIT_VAL},       // 青
                {0, 0, RGBLIGHT_LIMIT_VAL},                        // 蓝
                {RGBLIGHT_LIMIT_VAL, 0, RGBLIGHT_LIMIT_VAL},       // 紫
                {RGBLIGHT_LIMIT_VAL, RGBLIGHT_LIMIT_VAL, RGBLIGHT_LIMIT_VAL} // 白
            };

            static uint8_t neon_brightness = 0;
            static bool neon_increasing = true;
            static uint32_t last_update = 0;

            // 根据全局亮度动态调整呼吸速度（亮度越低，速度越慢）
            // 例如：rgblight_val = 255 → interval = 15ms，rgblight_val = 64 → interval ≈ 60ms
            uint8_t breathe_rgblight_val = breathe_brightness_levels[brightness_level];
            uint32_t interval = 15;
            uint32_t breathe_step = 3;

            switch (brightness_level)
            {
                // case 0: interval = 6; breathe_step = 1; break;
                case 0: interval = 20; breathe_step = 2; break;
                case 1: interval = 15; breathe_step = 2; break;
                case 2: interval = 10; breathe_step = 3; break;
                case 3: interval = 7; breathe_step = 3; break;
                default:interval = 7; breathe_step = 3; break;
            }

            if (timer_elapsed32(last_update) >= interval) {
                last_update = timer_read32();

                uint8_t max_val = breathe_rgblight_val;   // 呼吸的最大亮度受全局控制
                if (neon_increasing) {
                    if (neon_brightness < max_val) neon_brightness += breathe_step;
                    else neon_increasing = false;
                } else {
                    if (neon_brightness > breathe_step) neon_brightness -= breathe_step;
                    else {
                        neon_increasing = true;
                        neon_color_index = (neon_color_index + 1) % (ARRAY_SIZE(neon_colors));
                    }
                }
            }

            RGB current_color = neon_colors[neon_color_index];
            for (uint8_t i = RGBLED_START_INDEX; i < RGBLED_END_INDEX; i++) {
                rgb_matrix_set_color(
                    i,
                    (current_color.g * neon_brightness) / 255,
                    (current_color.r * neon_brightness) / 255,
                    (current_color.b * neon_brightness) / 255
                );
            }
        } break;

        case 5: rgb_light_color_set(rgblight_val, 0, 0); break;             // 红
        case 6: rgb_light_color_set(rgblight_val, rgblight_val/4, 0); break;// 橙
        case 7: rgb_light_color_set(two_color_rgblight_val, two_color_rgblight_val, 0); break;  // 黄
        case 8: rgb_light_color_set(0, rgblight_val, 0); break;             // 绿
        case 9: rgb_light_color_set(0, two_color_rgblight_val, two_color_rgblight_val); break;  // 青
        case 10: rgb_light_color_set(0, 0, rgblight_val); break;             // 蓝
        case 11: rgb_light_color_set(two_color_rgblight_val, 0, two_color_rgblight_val); break; // 紫
        case 12: {
            uint8_t white_rgblight_val = white_brightness_levels[brightness_level];
            rgb_light_color_set(white_rgblight_val, white_rgblight_val, white_rgblight_val); break; // 白
        }
        case 13: rgb_light_color_set(0, 0, 0); break; // 熄灭

        default:
            rgblight_mode = 0;
            break;
    }
}
