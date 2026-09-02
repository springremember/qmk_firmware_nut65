// Copyright 2024 sdk66 (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _DEFA, 
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,   KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,   KC_F9,     KC_F10,   KC_F11,   KC_F12,   KC_MUTE,   KC_PSCR,  KC_SCRL,  KC_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,     KC_8,    KC_9,      KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,    KC_O,      KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,     KC_H,     KC_J,     KC_K,    KC_L,      KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,     KC_N,     KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,            KC_RSFT,             KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                               KC_SPC,                                 KC_RALT,  MO(_FL),  KC_APP,   KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_FL] = LAYOUT( /* Base */
        _______,  KC_MSEL,  KC_VOLD,  KC_VOLU, KC_MUTE,  KC_MSTP,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MAIL,  KC_WHOM,  KC_CALC,  KC_WSCH,  _______,   _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_SPI,  RGB_TOG,   _______,  _______,  LEO_MOD,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,  KC_2G4,   _______,  _______,  _______,  _______,  _______,  _______,  RGB_SAD,  RGB_SAI,  RGB_MOD,   _______,  _______,  LEO_HUI,
        _______,  TO(_BL),  TO(_MBL), _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            MO(_DEFA),           RGB_VAI,
        _______,  GU_TOGG,  _______,                               EE_CLR,                                 _______,  _______,  _______,  _______,   RGB_HUD,  RGB_VAD,  RGB_HUI),

    [_MBL] = LAYOUT(  /* Base */
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_TS,   KC_DESK,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MUTE,   KC_PSCR,  KC_SCRL,  KC_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,             KC_UP,
        KC_LCTL,  KC_LALT,  KC_LGUI,                               KC_SPC,                                 KC_RGUI,  MO(_MFL),  KC_APP,  KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_MFL] = LAYOUT(  /* FN */
        _______,  KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,  KC_MUTE,   KC_PSCR,  KC_SCRL,  KC_PAUSE,
        _______,  _______,  _______,  _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  RGB_SPD,   RGB_SPI, RGB_TOG,   _______,  _______,  LEO_MOD,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,  KC_2G4,  _______,   _______,  _______,  _______,  _______,  _______,  RGB_SAD,   RGB_SAI, RGB_MOD,   _______,  _______,  LEO_HUI,
        _______,  TO(_BL),  TO(_MBL), _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______, _______,
        _______,  _______,  _______,  _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,            MO(_DEFA),           RGB_VAI,
        _______,  _______,  _______,                               EE_CLR,                                 _______,  _______,   _______, _______,   RGB_HUD,  RGB_VAD,  RGB_HUI),
    [_DEFA] = LAYOUT(  /* FN */
        QK_BOOT,  _______,  _______,  _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______, _______,   _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______, _______,   _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______, _______,   _______,  _______,  _______,
        _______,  _______,  _______,  _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______, _______,
        _______,  _______,  _______,  _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,             _______,
        _______,  _______,  _______,                               _______,                                _______,  _______,   _______, _______,   _______,  _______,  _______),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______)}
};
#endif
// clang-format on
