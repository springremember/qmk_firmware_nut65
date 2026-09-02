// Copyright 2024 nut65-vim
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"
#include "qmk-vim/src/vim.h"
#include "qmk-vim/src/modes.h"

// Vendor housekeeping loop, renamed in nut65.c to make room for the keymap hook
extern void hs_housekeeping_task_user(void);

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
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    KC_PGUP,
        KC_LSFT,              KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
        KC_LCTL,  KC_LCMD,    KC_LALT,                        KC_SPC,                                           KC_RALT,    MO(_FL),  KC_LEFT,  KC_DOWN,   KC_RGHT,
        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
        ),

    [_FL] = LAYOUT( /* win FN */
        EE_CLR,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   RL_MOD,    MUS_STA,
        KC_GRV,   KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  _______,  _______,    _______,  _______,  RGB_MOD,   MUS_CUT,
        _______,  _______,    _______,    DEB_TOG,  _______,  _______,  KC_SCRL,  KC_PAUS,  KC_HOME,  KC_END,   _______,    _______,            RGB_HUI,   RL_VAI,
        _______,              _______,    _______,  _______,  _______,  _______,  NK_TOGG,  SYS_CUT,  _______,  _______,    _______,  MO(_DEFA),RGB_VAI,   RL_VAD,
        LED_TOG,  GU_TOGG,    HS_FREQ,                        HS_BATQ,                                          KC_FTOG,    _______,  RGB_SPD,  RGB_VAD,   RGB_SPI,
        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
        ),

    [_MBL] = LAYOUT(  /* mac Base */
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    KC_PGUP,
        KC_LSFT,              KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
        KC_LCTL,  KC_LALT,    KC_LCMD,                        KC_SPC,                                           KC_RCMD,    MO(_MFL), KC_LEFT,  KC_DOWN,   KC_RGHT,
        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
        ),

    [_MFL] = LAYOUT(  /*mac FN */
        EE_CLR,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   RL_MOD,    MUS_STA,
        KC_GRV,   KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  _______,  _______,    _______,  _______,  RGB_MOD,   MUS_CUT,
        _______,  _______,    _______,    DEB_TOG,  _______,  _______,  KC_SCRL,  KC_PAUS,  KC_HOME,  KC_END,   _______,    _______,            RGB_HUI,   RL_VAI,
        _______,              _______,    _______,  _______,  _______,  _______,  NK_TOGG,  SYS_CUT,  _______,  _______,    _______,  MO(_DEFA),RGB_VAI,   RL_VAD,
        LED_TOG,  _______,    HS_FREQ,                        HS_BATQ,                                          KC_FTOG,    _______,  RGB_SPD,  RGB_VAD,   RGB_SPI,
        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
        ),

    [_DEFA] = LAYOUT(  /* FN */
        QK_BOOT,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,   _______,
        _______,  _______,    BT_TEST,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,   _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  KC_TEST,  _______,    _______,            _______,   _______,
        _______,              _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,   _______,
        _______,  _______,    _______,                        _______,                                          _______,    _______,  _______,  _______,   _______,
        KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,     KC_NO
        ),

};

const uint16_t PROGMEM rgbrec_default_effects[RGBREC_CHANNEL_NUM][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________,             ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, HS_GREEN,  ________,
        ________, ________,   ________,                       ________,                                         ________,   ________, HS_GREEN, HS_GREEN,  HS_GREEN,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________
        ),

    [1] = LAYOUT(
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________,             ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, HS_GREEN,  ________,
        ________, ________,   ________,                       ________,                                         ________,   ________, HS_GREEN, HS_GREEN,  HS_GREEN,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________
        ),

    [2] = LAYOUT(
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________,             ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, HS_GREEN,  ________,
        ________, ________,   ________,                       ________,                                         ________,   ________, HS_GREEN, HS_GREEN,  HS_GREEN,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________
        ),
};
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(HS_VOLU, HS_VOLD)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______)}
};
#endif

// clang-format on

/* ===== Vim is always on: enter Normal mode at boot ===== */
void keyboard_post_init_user(void) {
    enable_vim_mode();
}

/* ===== Insert key (KC_INS) cursor indicator =====
 * Non-insert modes hold KC_INS (host cursor becomes a block),
 * insert mode releases it (cursor becomes a line). */
static bool ins_key_held = false;

static void set_insert_held(bool held) {
    if (held && !ins_key_held) {
        register_code(KC_INS);
        ins_key_held = true;
    } else if (!held && ins_key_held) {
        unregister_code(KC_INS);
        ins_key_held = false;
    }
}

void normal_mode_user(void)      { set_insert_held(true);  }
void visual_mode_user(void)      { set_insert_held(true);  }
void visual_line_mode_user(void) { set_insert_held(true);  }
void insert_mode_user(void)      { set_insert_held(false); }

/* ===== Number key long-press state (F-row emulation) ===== */
static uint16_t num_key_timer    = 0;
static uint8_t  num_keycode      = 0;
static bool     num_key_triggered = false;

// Normal mode extra bindings: s = save, / and ? = find
bool process_normal_mode_user(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_S:
                tap_code16(LCTL(KC_S));
                return false;
            case KC_SLSH:
            case LSFT(KC_SLSH):
                tap_code16(LCTL(KC_F));
                return false;
            default:
                break;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Esc: always send the real Esc first, then switch mode if needed
    if (keycode == KC_ESC && vim_mode_enabled() && record->event.pressed) {
        tap_code(KC_ESC);
        switch (get_vim_mode()) {
            case INSERT_MODE:
            case VISUAL_MODE:
            case VISUAL_LINE_MODE:
                normal_mode();
                break;
            default:
                break;
        }
        return false;
    }

    if (!process_vim_mode(keycode, record)) {
        return false;
    }

    // Number key dual-role (insert mode on base layer)
    if (get_vim_mode() == INSERT_MODE && get_highest_layer(layer_state) == _BL && keycode >= KC_1 && keycode <= KC_0) {
        uint8_t num  = (keycode == KC_0) ? 10 : (keycode - KC_1 + 1);
        uint8_t mods = get_mods();

        if (record->event.pressed) {
            if (mods & MOD_MASK_CTRL) {
                // Ctrl already held: emit the F key, host sees Ctrl+F
                tap_code(KC_F1 + num - 1);
                return false;
            }
            num_key_timer     = timer_read();
            num_keycode       = keycode;
            num_key_triggered = false;
            return false;
        } else {
            if (num_keycode == keycode && !num_key_triggered) {
                tap_code(keycode);
            }
            num_key_timer     = 0;
            num_keycode       = 0;
            num_key_triggered = false;
            return false;
        }
    }

    return true;
}

void housekeeping_task_user(void) {
    if (num_key_timer && !num_key_triggered && timer_elapsed(num_key_timer) > NUM_HOLD_TIME) {
        uint8_t num = (num_keycode == KC_0) ? 10 : (num_keycode - KC_1 + 1);
        tap_code(KC_F1 + num - 1);
        num_key_triggered = true;
    }

    hs_housekeeping_task_user();
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (vim_mode_enabled()) {
        switch (get_vim_mode()) {
            case NORMAL_MODE:
                rgb_matrix_set_color(VIM_LED_INDEX, 0x00, 0x00, 0xFF); // blue
                break;
            case INSERT_MODE:
                rgb_matrix_set_color(VIM_LED_INDEX, 0x00, 0xFF, 0x00); // green
                break;
            case VISUAL_MODE:
                rgb_matrix_set_color(VIM_LED_INDEX, 0xFF, 0x00, 0xFF); // magenta
                break;
            case VISUAL_LINE_MODE:
                rgb_matrix_set_color(VIM_LED_INDEX, 0x00, 0xFF, 0xFF); // cyan
                break;
            default:
                break;
        }
    }
    return true;
}
