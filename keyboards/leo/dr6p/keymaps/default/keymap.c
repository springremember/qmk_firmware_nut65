// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL, 
    _FFL,
    _FMBL,
    _FMFL,
    _DEFA
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT( 
                                                                                                                                                           KC_P7,    KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSLS,   KC_BSPC,  KC_P4,  KC_P8,   KC_P9,   KC_PPLS,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,                       KC_P1,  KC_P5,   KC_P6,   KC_PENT,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,  KC_BSLS,             KC_ENT,   
        KC_LSFT,  KC_NUBS,    KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,             MO(_FL),  
        KC_LCTL,  KC_LCMD,    KC_LALT,                                  KC_SPC,                                             MO(_FL),  KC_RCMD,             KC_RCTL,  KC_P0,  KC_P2,   KC_P3,   KC_PDOT),  

    [_FL] = LAYOUT( 
                                                                                                                                                           _______,  _______,_______, _______, _______,
        EE_CLR,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   RGB_MOD,   RGB_TOG,  _______,_______, _______, _______,
        _______,  KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  MO(_DEFA),_______,    RGB_VAD,  RGB_VAI,                       _______,_______, _______, _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  MO(_DEFA),RGB_SPD,    RGB_SPI,  RGB_MOD,             _______,  
        _______,  RGB_MOD,    _______,    _______,  _______,  _______,  _______,  _______,  SYS_TOG,  _______,  _______,    RGB_HUI,  MO(_DEFA),           _______,  
        KC_FTOG,  GU_TOGG,    _______,                                  HS_BATQ,                                            _______,  _______,             _______,  _______,_______, _______, _______),

    [_MBL] = LAYOUT( 
                                                                                                                                                           KC_P7,    KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSLS,   KC_BSPC,  KC_P4,  KC_P8,   KC_P9,   KC_PPLS,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,                       KC_P1,  KC_P5,   KC_P6,   KC_PENT,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,  KC_BSLS,             KC_ENT,   
        KC_LSFT,  KC_NUBS,    KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,             MO(_MFL), 
        KC_LCTL,  KC_LALT,    KC_LCMD,                                  KC_SPC,                                             MO(_MFL), KC_RCMD,             KC_RCTL,  KC_P0,  KC_P2,   KC_P3,   KC_PDOT),   

    [_MFL] = LAYOUT(  
                                                                                                                                                           _______,  _______,_______, _______, _______,
        EE_CLR,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   RGB_MOD,   RGB_TOG,  _______,_______, _______, _______,
        _______,  KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  MO(_DEFA),_______,    RGB_VAD,  RGB_VAI,                       _______,_______, _______, _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  MO(_DEFA),RGB_SPD,    RGB_SPI,  RGB_MOD,             _______,  
        _______,  RGB_MOD,    _______,    _______,  _______,  _______,  _______,  _______,  SYS_TOG,  _______,  _______,    RGB_HUI,  MO(_DEFA),           _______, 
        KC_FTOG,  _______,    _______,                                  HS_BATQ,                                            _______,  _______,             _______,  _______,_______, _______, _______),

    [_FBL] = LAYOUT( 
                                                                                                                                                           KC_P7,    KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_ESC,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   KC_BSLS,   KC_BSPC,  KC_P4,  KC_P8,   KC_P9,   KC_PPLS,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,                       KC_P1,  KC_P5,   KC_P6,   KC_PENT,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,  KC_BSLS,             KC_ENT,   
        KC_LSFT,  KC_NUBS,    KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,             MO(_FFL), 
        KC_LCTL,  KC_LCMD,    KC_LALT,                                  KC_SPC,                                             MO(_FFL), KC_RCMD,             KC_RCTL,  KC_P0,  KC_P2,   KC_P3,   KC_PDOT),   

    [_FFL] = LAYOUT( 
                                                                                                                                                           _______,  _______,_______, _______, _______,
        EE_CLR,   KC_MYCM,    KC_WHOM,    KC_MAIL,  KC_CALC,  KC_MSEL,  KC_MSTP,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,  RGB_MOD,   RGB_TOG,  _______,_______, _______, _______,
        _______,  KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  MO(_DEFA),_______,    RGB_VAD,  RGB_VAI,                       _______,_______, _______, _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  MO(_DEFA),RGB_SPD,    RGB_SPI,  RGB_MOD,             _______,  
        _______,  RGB_MOD,    _______,    _______,  _______,  _______,  _______,  _______,  SYS_TOG,  _______,  _______,    RGB_HUI,  MO(_DEFA),           _______,  
        KC_FTOG,  GU_TOGG,    _______,                                  HS_BATQ,                                            _______,  _______,             _______,  _______,_______, _______, _______),

    [_FMBL] = LAYOUT(  
                                                                                                                                                           KC_P7,    KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_ESC,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   KC_BSLS,   KC_BSPC,  KC_P4,  KC_P8,   KC_P9,   KC_PPLS,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,                       KC_P1,  KC_P5,   KC_P6,   KC_PENT,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,  KC_BSLS,             KC_ENT,   
        KC_LSFT,  KC_NUBS,    KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,             MO(_FMFL), 
        KC_LCTL,  KC_LALT,    KC_LCMD,                                  KC_SPC,                                             MO(_FMFL),KC_RCMD,             KC_RCTL,  KC_P0,  KC_P2,   KC_P3,   KC_PDOT),  

    [_FMFL] = LAYOUT( 
                                                                                                                                                           _______,  _______,_______, _______, _______,
        EE_CLR,   KC_BRID,    KC_BRIU,    KC_F3,    KC_F4,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,  RGB_MOD,   RGB_TOG,  _______,_______, _______, _______,
        _______,  KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  MO(_DEFA),_______,    RGB_VAD,  RGB_VAI,                       _______,_______, _______, _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  MO(_DEFA),RGB_SPD,    RGB_SPI,  RGB_MOD,             _______,  
        _______,  RGB_MOD,    _______,    _______,  _______,  _______,  _______,  _______,  SYS_TOG,  _______,  _______,    RGB_HUI,  MO(_DEFA),           _______,  
        KC_FTOG,  _______,    _______,                                  HS_BATQ,                                            _______,  _______,             _______,  _______,_______, _______, _______),

    [_DEFA] = LAYOUT(  
                                                                                                                                                           _______,  _______,_______, _______, _______,
        QK_BOOT,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,   _______,  _______,_______, _______, _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  KC_TEST,  _______,    _______,  _______,                       _______,_______, _______, _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  KC_TEST,  _______,    _______,  _______,             _______,  
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,             _______,  
        _______,  _______,    _______,                                  _______,                                            _______,  _______,             _______,  _______,_______, _______, _______),

};
 
const uint16_t PROGMEM rgbrec_default_effects[RGBREC_CHANNEL_NUM][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(    
                                                                                                                                                           ________, ________, ________, ________, ________,
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, ________, ________, ________, ________, 
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________,                      ________, ________, ________, ________,
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________, ________,            ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________,            ________, 
        ________, ________,   ________,                                 ________,                                           ________, ________,            ________, ________, ________, ________, ________),

    [1] = LAYOUT(
                                                                                                                                                           ________, ________, ________, ________, ________,
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, ________, ________, ________, ________, 
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________,                      ________, ________, ________, ________,
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________, ________,            ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________,            ________, 
        ________, ________,   ________,                                 ________,                                           ________, ________,            ________, ________, ________, ________, ________),

    [2] = LAYOUT(
                                                                                                                                                           ________, ________, ________, ________, ________,
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, ________, ________, ________, ________, 
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________,                      ________, ________, ________, ________,
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________, ________,            ________, 
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________,            ________, 
        ________, ________,   ________,                                 ________,                                           ________, ________,            ________, ________, ________, ________, ________),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______)},
    [5] = {ENCODER_CCW_CW(_______, _______)},
    [6] = {ENCODER_CCW_CW(_______, _______)},
    [7] = {ENCODER_CCW_CW(_______, _______)},
    [8] = {ENCODER_CCW_CW(_______, _______)}
};
#endif
// clang-format on
