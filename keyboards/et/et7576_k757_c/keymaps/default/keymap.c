// Copyright 2024 sdk66 (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _DEFA, 
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT( /* win Base */
        KC_ESC,   HS_MUTE,  KC_F1,    KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
        KC_GRV,   KC_1,     KC_2,     KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME, 
        KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_END,
        KC_CAPS,  KC_A,     KC_S,     KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_ENT,   KC_PGUP,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_PGDN,
        KC_LCTL,  KC_LGUI,  KC_LALT,                              KC_SPC,                    KC_RALT,  MO(_FL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),  

    [_FL] = LAYOUT( /* win FN */
        EE_CLR,   HS_FILP,  KC_BRID, KC_BRIU,  HS_W_AT, HS_W_MU,  HS_W_DC, KC_WSCH, KC_MPRV, KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  HS_BATQ,   
        _______,  KC_BT1,   KC_BT2,   KC_BT3,  KC_2G4,  _______,  _______, _______, _______, _______,  _______,  RL_MOD,   RL_SPI,   RP_END,   RL_HUI,
        _______,  _______,  _______,  _______, _______, _______,  _______, _______, _______, KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_INS,   _______,  _______,
        KC_TEST,  _______,  _______,  _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,  _______,  RGB_HUI,
        _______,  _______,  _______,  _______, _______, _______,  NK_TOGG, _______, _______, _______,  _______,  _______,  MO(_DEFA),RGB_VAI,  RGB_MOD,
        _______,  GU_TOGG,  _______,                              _______,                   _______,  _______,  _______,  RGB_SPD,  RGB_VAD,  RGB_SPI
    ),

    [_MBL] = LAYOUT(
        KC_ESC,   HS_MUTE,  KC_BRID, KC_BRIU,  HS_M_AT, HS_M_SI,  KC_F11,  HS_M_SO, KC_MPRV, KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,
        KC_GRV,   KC_1,     KC_2,     KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME, 
        KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_END,
        KC_CAPS,  KC_A,     KC_S,     KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_ENT,   KC_PGUP,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_PGDN,
        KC_LCTL,  KC_LALT,  KC_LGUI,                              KC_SPC,                    KC_RGUI,  MO(_MFL), KC_RALT,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_MFL] = LAYOUT(
        EE_CLR,   HS_FILP,  KC_F1,    KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   HS_BATQ,   
        _______,  KC_BT1,   KC_BT2,   KC_BT3,  KC_2G4,  _______,  _______, _______, _______, _______,  _______,  RL_MOD,   RL_SPI,   RP_END,   RL_HUI,
        _______,  _______,  _______,  _______, _______, _______,  _______, _______, _______, KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_INS,   _______,  _______,
        KC_TEST,  _______,  _______,  _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,  _______,  RGB_HUI,
        _______,  _______,  _______,  _______, _______, _______,  NK_TOGG, _______, _______, _______,  _______,  _______,  MO(_DEFA),RGB_VAI,  RGB_MOD,
        _______,  _______,  _______,                              _______,                   _______,  _______,  _______,  RGB_SPD,  RGB_VAD,  RGB_SPI
    ),

    [_DEFA] = LAYOUT(
        QK_BOOT,  _______,  _______,  _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______, 
        _______,  _______,  BT_TEST,  _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______, 
        _______,  _______,  _______,  _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,                              _______,                   _______,  _______,  _______,  _______,  _______,  _______
    ),
};

const uint16_t PROGMEM rgbrec_default_effects[RGBREC_CHANNEL_NUM][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, HS_GREEN,  ________,
        ________, ________,   ________,                                 ________,                     ________, ________,   ________, HS_GREEN, HS_GREEN,  HS_GREEN),

    [1] = LAYOUT(
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, HS_GREEN,  ________,
        ________, ________,   ________,                                 ________,                     ________, ________,   ________, HS_GREEN, HS_GREEN,  HS_GREEN),

    [2] = LAYOUT(
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, HS_GREEN,  ________,
        ________, ________,   ________,                                 ________,                     ________, ________,   ________, HS_GREEN, HS_GREEN,  HS_GREEN),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(HS_VOLU, HS_VOLD)},
    [1] = {ENCODER_CCW_CW(HS_VOLU, HS_VOLD)},
    [2] = {ENCODER_CCW_CW(HS_VOLU, HS_VOLD)},
    [3] = {ENCODER_CCW_CW(HS_VOLU, HS_VOLD)},
    [4] = {ENCODER_CCW_CW(HS_VOLU, HS_VOLD)}
};
#endif

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, SW2_CS18,  SW2_CS17,  SW2_CS16  },  // 0  Esc
    {0, SW4_CS18,  SW4_CS17,  SW4_CS16  },  // 1  F1
    {0, SW5_CS18,  SW5_CS17,  SW5_CS16  },  // 2  F2
    {0, SW6_CS18,  SW6_CS17,  SW6_CS16  },  // 3  F3
    {0, SW7_CS18,  SW7_CS17,  SW7_CS16  },  // 4  F4
    {0, SW8_CS18,  SW8_CS17,  SW8_CS16  },  // 5  F5
    {0, SW9_CS18,  SW9_CS17,  SW9_CS16  },  // 6  F6
    {1, SW1_CS18,  SW1_CS17,  SW1_CS16  },  // 7  F7
    {1, SW2_CS18,  SW2_CS17,  SW2_CS16  },  // 8  F8
    {1, SW3_CS18,  SW3_CS17,  SW3_CS16  },  // 9  F9
    {1, SW4_CS18,  SW4_CS17,  SW4_CS16  },  // 10 F10
    {1, SW5_CS18,  SW5_CS17,  SW5_CS16  },  // 11 F11
    {1, SW6_CS18,  SW6_CS17,  SW6_CS16  },  // 12 F12
    {1, SW8_CS18,  SW8_CS17,  SW8_CS16  },  // 13 DEL

    {0, SW2_CS15,  SW2_CS14,  SW2_CS13  },  // 14 `~
    {0, SW3_CS15,  SW3_CS14,  SW3_CS13  },  // 15 1!
    {0, SW4_CS15,  SW4_CS14,  SW4_CS13  },  // 16 2@
    {0, SW5_CS15,  SW5_CS14,  SW5_CS13  },  // 17 3#
    {0, SW6_CS15,  SW6_CS14,  SW6_CS13  },  // 18 4$
    {0, SW7_CS15,  SW7_CS14,  SW7_CS13  },  // 19 5%
    {0, SW8_CS15,  SW8_CS14,  SW8_CS13  },  // 20 6^
    {0, SW9_CS15,  SW9_CS14,  SW9_CS13  },  // 21 7&
    {1, SW1_CS15,  SW1_CS14,  SW1_CS13  },  // 22 8*
    {1, SW2_CS15,  SW2_CS14,  SW2_CS13  },  // 23 9(
    {1, SW3_CS15,  SW3_CS14,  SW3_CS13  },  // 24 0)
    {1, SW4_CS15,  SW4_CS14,  SW4_CS13  },  // 25 -_
    {1, SW5_CS15,  SW5_CS14,  SW5_CS13  },  // 26 =+
    {1, SW6_CS15,  SW6_CS14,  SW6_CS13  },  // 27 Backspace
    {1, SW8_CS15,  SW8_CS14,  SW8_CS13  },  // 28 HOME

    {0, SW2_CS12,  SW2_CS11,  SW2_CS10  },  // 29 Tab
    {0, SW3_CS12,  SW3_CS11,  SW3_CS10  },  // 30 Q
    {0, SW4_CS12,  SW4_CS11,  SW4_CS10  },  // 31 W
    {0, SW5_CS12,  SW5_CS11,  SW5_CS10  },  // 32 E
    {0, SW6_CS12,  SW6_CS11,  SW6_CS10  },  // 33 R
    {0, SW7_CS12,  SW7_CS11,  SW7_CS10  },  // 34 T
    {0, SW8_CS12,  SW8_CS11,  SW8_CS10  },  // 35 Y
    {0, SW9_CS12,  SW9_CS11,  SW9_CS10  },  // 36 U
    {1, SW1_CS12,  SW1_CS11,  SW1_CS10  },  // 37 I
    {1, SW2_CS12,  SW2_CS11,  SW2_CS10  },  // 38 O
    {1, SW3_CS12,  SW3_CS11,  SW3_CS10  },  // 39 P
    {1, SW4_CS12,  SW4_CS11,  SW4_CS10  },  // 40 [
    {1, SW5_CS12,  SW5_CS11,  SW5_CS10  },  // 41 ]
    {1, SW6_CS12,  SW6_CS11,  SW6_CS10  },  // 42 \|
    {1, SW8_CS12,  SW8_CS11,  SW8_CS10  },  // 43 END

    {0, SW2_CS1,   SW2_CS2,   SW2_CS3   },  // 44 S
    {0, SW3_CS1,   SW3_CS2,   SW3_CS3   },  // 45 D
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3   },  // 46 F
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3   },  // 47 G
    {0, SW6_CS1,   SW6_CS2,   SW6_CS3   },  // 48 H
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3   },  // 49 J
    {0, SW8_CS1,   SW8_CS2,   SW8_CS3   },  // 50 H
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3   },  // 51 J
    {1, SW1_CS1,   SW1_CS2,   SW1_CS3   },  // 52 K
    {1, SW2_CS1,   SW2_CS2,   SW2_CS3   },  // 53 L
    {1, SW3_CS1,   SW3_CS2,   SW3_CS3   },  // 54 ;
    {1, SW4_CS1,   SW4_CS2,   SW4_CS3   },  // 55 '
    {1, SW5_CS1,   SW5_CS2,   SW5_CS3  },  // 56 \|
    {1, SW6_CS1,   SW6_CS2,   SW6_CS3   },  // 57 ENTER
    {1, SW8_CS1,   SW8_CS2,   SW8_CS3   },  // 58 PgUp

    {0, SW2_CS4,   SW2_CS5,   SW2_CS6  },  // 59 SHIFT_L
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6  },  // 60 \| NUBS
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6  },  // 61 Z
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6  },  // 62 X
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6  },  // 63 C
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6  },  // 64 V
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6  },  // 65 B
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6  },  // 66 N
    {1, SW1_CS4,   SW1_CS5,   SW1_CS6   },  // 67 M
    {1, SW2_CS4,   SW2_CS5,   SW2_CS6   },  // 68 <
    {1, SW3_CS4,   SW3_CS5,   SW3_CS6   },  // 69 >
    {1, SW4_CS4,   SW4_CS5,   SW4_CS6   },  // 70 ?
    {1, SW5_CS4,   SW5_CS5,   SW5_CS6   },  // 71 SHIFT_R
    {1, SW7_CS4,   SW7_CS5,   SW7_CS6   },  // 72上
    {1, SW8_CS4,   SW8_CS5,   SW8_CS6   },  // 73 UP

    {0, SW2_CS7,   SW2_CS8,   SW2_CS9   },  // 74 CTRL_L
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9   },  // 75 WIN_L
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9   },  // 76 ALT_L
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9   },  // 77 SPACE
    {1, SW3_CS7,   SW3_CS8,   SW3_CS9   },  // 78 CTRL_R
    {1, SW4_CS7,   SW4_CS8,   SW4_CS9   },  // 79 LEFT
    {1, SW5_CS7,   SW5_CS8,   SW5_CS9   },  // 80 DOWN
    {1, SW6_CS7,   SW6_CS8,   SW6_CS9   },  // 81 RIGHT 
    {1, SW7_CS7,   SW7_CS8,   SW7_CS9   },  // 82 RIGHT 
    {1, SW8_CS7,   SW8_CS8,   SW8_CS9   },  // 83 DOWN
    {1, SW1_CS7,   SW1_CS8,   SW1_CS9   },  // 84 ALT_R
    {1, SW2_CS7,   SW2_CS8,   SW2_CS9   },  // 85 FN

    {1, SW7_CS12,   SW7_CS11,   SW7_CS10  },  // 86 MLED 模式指示灯
    {1, SW7_CS1,    SW7_CS2,    SW7_CS3   },  // 87 BLED 电量指示灯

    /* side light*/
    // {0, SW1_CS18,  SW1_CS17,  SW1_CS16  },  // 88 LG0
    // {0, SW1_CS12,  SW1_CS11,  SW1_CS10  },  // 89 LG2
    // {0, SW1_CS1,   SW1_CS2,   SW1_CS3   },  // 90 LG3
    // {0, SW1_CS7,   SW1_CS8,   SW1_CS9   },  // 91 LG4

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9   },  // 91 LG4
    {0, SW1_CS1,   SW1_CS2,   SW1_CS3   },  // 90 LG3
    {0, SW1_CS12,  SW1_CS11,  SW1_CS10  },  // 89 LG2
    {0, SW1_CS18,  SW1_CS17,  SW1_CS16  },  // 88 LG0

    {1, SW9_CS18,  SW9_CS17,  SW9_CS16 },  // 92 LG5
    {1, SW9_CS12,  SW9_CS11,  SW9_CS10 },  // 93 LG6
    {1, SW9_CS1,   SW9_CS2,   SW9_CS3  },  // 94 LG7
    {1, SW9_CS7,   SW9_CS8,   SW9_CS9   },  // 95 RIGHT 

    // {1, SW12_CS1,  SW12_CS2,  SW12_CS3  },  // 88 LG8
    // {1, SW12_CS4,  SW12_CS5,  SW12_CS6  },  // 89 LG9
    // {1, SW12_CS1,  SW12_CS2,  SW12_CS3  },  // 90 LG10
    // {1, SW12_CS4,  SW12_CS5,  SW12_CS6  },  // 91 LG11
    // {1, SW12_CS1,  SW12_CS2,  SW12_CS3  },  // 92 LG12
    // {1, SW12_CS4,  SW12_CS5,  SW12_CS6  },  // 93 LG13
    // {1, SW12_CS1,  SW12_CS2,  SW12_CS3  },  // 94 LG14
    // {1, SW12_CS4,  SW12_CS5,  SW12_CS6  }   // 95 LG15
};

// clang-format on
