// Copyright 2024 nut65-vim
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"
#include "qmk-vim/src/vim.h"
#include "qmk-vim/src/modes.h"
#include "qmk-vim/src/process_func.h"

// Vendor housekeeping loop, renamed in nut65.c to make room for the keymap hook
extern void hs_housekeeping_task_user(void);

// qmk-vim current keycode processor (can be swapped to drive a custom mode)
extern process_func_t process_func;

// wireless / low-power hooks used by the original-Delete(now _GO key)+Space combo
extern void suspend_wakeup_init(void);
extern void wireless_devs_change(uint8_t old_devs, uint8_t new_devs, bool reset);
extern uint8_t wireless_get_current_devs(void);
#define PW_DEVS_USB  0
#define PW_DEVS_2G4  6

#ifdef VIM_DOT_REPEAT
extern void add_repeat_keycode(uint16_t keycode);
#endif

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _DEFA,
    _GO,
};

enum custom_keycodes {
    GO_HOLD = SAFE_RANGE, // hold to switch into the _GO layer
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT( /* win Base */
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_DEL,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   GO_HOLD,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    KC_WFWD,
        KC_LSFT,              KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,  KC_UP,     KC_WBAK,
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

    [_GO] = LAYOUT(  /* hold grave key -> F-row layer */
        KC_GRV,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   _______,   _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,   _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,            _______,   _______,
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
    [4] = {ENCODER_CCW_CW(_______, _______)},
    [5] = {ENCODER_CCW_CW(_______, _______)}
};
#endif

// clang-format on

/* ===== Vim is always on: enter Normal mode at boot ===== */
void keyboard_post_init_user(void) {
    enable_vim_mode();
}

/* ===== Esc visual exit tracking ===== */
static bool esc_visual_exit = false;

/* ===== Replace mode (vim R: overwrite chars until Esc) ===== */
static bool replace_active = false;

/* ===== Power combo: original Delete key (row1 col14, now GO_HOLD) + Space
 * held >= 3s with no USB cable = deep-sleep power toggle.
 * pw_off: any key wakes the MCU, but only a fresh >=3s combo boots wireless
 * again; every other key is swallowed and it goes straight back to sleep.
 */
#define PW_HOLD_MS 3000
static bool     pw_off = false;
static bool     pw_del = false; // the original-Delete/_GO key
static bool     pw_spc = false;
static bool     pw_combo = false;
static uint32_t pw_combo_timer = 0;
static uint8_t  pw_last_wls = PW_DEVS_2G4; // remembered non-USB device
static bool     pw_cable_last = false;
static uint32_t pw_cable_timer = 0;

static bool pw_no_cable(void) {
    return !readPin(HS_BAT_CABLE_PIN);
}

static void pw_enter_sleep(void) {
    pw_off   = true;
    pw_combo = false;
    pw_del   = false;
    pw_spc   = false;
    clear_keyboard();
    lpwr_set_state(1); // LPWR_PRESLEEP -> LPWR_STOP (deep sleep)
}

static void pw_boot_wireless(void) {
    pw_off   = false;
    pw_combo = false;
    pw_del   = false;
    pw_spc   = false;
    suspend_wakeup_init();
    if (wireless_get_current_devs() == PW_DEVS_USB) {
        wireless_devs_change(PW_DEVS_USB, pw_last_wls, false);
    }
}

static bool process_replace_mode(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed) {
        uint16_t base = keycode;
        if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
            // only a pure Shift modifier is printable here, let others through
            if ((keycode & 0xFF00) != QK_LSFT) {
                return true;
            }
            base = keycode & 0xFF;
        }
        // printable + tab: A-Z, 1-0, space, punctuation row (vim R overwrites tab too)
        if ((base >= KC_A && base <= KC_Z) || (base >= KC_1 && base <= KC_0) || base == KC_SPC || base == KC_TAB || (base >= KC_MINS && base <= KC_SLSH)) {
            tap_code(KC_DELETE); // overwrite char under cursor
            tap_code16(keycode); // type the (possibly shifted) char, cursor advances
            return false;
        }
    }
    return true;
}

// vim R == replace mode until Esc/Caps (normal_mode clears it)
static void enter_replace_mode(void) {
    replace_active = true;
    process_func   = process_replace_mode;
}

// Called by qmk-vim whenever Normal mode is entered, keeps state in sync.
// Strong symbol so it overrides qmk-vim's weak default (two weak symbols would
// make the linker pick either one).
void normal_mode_user(void) {
    replace_active = false;
}

// Normal mode bindings
bool process_normal_mode_user(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_BSPC:
                tap_code(KC_LEFT);
                return false;
            case KC_SPC:
                tap_code(KC_RIGHT);
                return false;
            case KC_MINS:
                tap_code(KC_UP);
                tap_code(KC_HOME);
                return false;
            case LSFT(KC_EQL):
                tap_code(KC_DOWN);
                tap_code(KC_HOME);
                return false;
            case LCTL(KC_F):
                tap_code(KC_PGDN);
                return false;
            case LCTL(KC_B):
                tap_code(KC_PGUP);
                return false;
            case KC_SLSH:
            case LSFT(KC_SLSH):
                tap_code16(LCTL(KC_F));
                return false;
            case KC_ENT:
                tap_code(KC_ENT);
                return false;
            case LSFT(KC_J):
                tap_code(KC_END);   // join next line onto this one
                tap_code(KC_DELETE);
                return false;
            case LSFT(KC_R):
                enter_replace_mode();
                return false;
            default:
                break;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // ---- Power on/off combo: hold original-Delete(_GO) key + Space >= 3s,
    // only with no USB cable. Single key presses keep their normal role. ----
    bool is_pw_del = (keycode == GO_HOLD); // original Delete position
    bool is_pw_spc = (keycode == KC_SPC);
    if (is_pw_del || is_pw_spc) {
        if (pw_no_cable()) {
            if (record->event.pressed) {
                if (is_pw_del) {
                    pw_del = true;
                } else {
                    pw_spc = true;
                }
                if (pw_del && pw_spc) {
                    if (!pw_combo) {
                        pw_combo       = true;
                        pw_combo_timer = timer_read32();
                        clear_keyboard(); // stop output while holding the combo
                    }
                    return false; // both held: awaiting the 3s power action
                }
                if (pw_off) return false; // off: only the combo may run
                return true;              // single key: normal (layer / space)
            } else {
                if (is_pw_del) {
                    pw_del = false;
                } else {
                    pw_spc = false;
                }
                if (pw_combo) {
                    pw_combo = false;
                    if (pw_off) pw_enter_sleep(); // aborted boot -> sleep again
                }
                if (pw_off) return false;
                return true;
            }
        }
        // USB cable present: leave pw_off and behave normally
        if (pw_off) pw_off = false;
        return true;
    }
    if (pw_off && pw_no_cable()) {
        // woke up with some other key while off -> not the combo, sleep again
        if (record->event.pressed) pw_enter_sleep();
        return false; // swallow everything until a valid power-on combo
    }

    // GO_HOLD: hold the grave key to switch into the _GO layer (F-row + grave)
    if (keycode == GO_HOLD) {
        if (record->event.pressed) {
            layer_on(_GO);
        } else {
            layer_off(_GO);
        }
        return false;
    }

    // Esc first, before anything else can consume it. Normal & Insert mode:
    // send a real Esc to the host and DO NOT switch modes. Only Visual modes
    // (qmk-vim native exit) and Replace mode are special.
    if (keycode == KC_ESC && vim_mode_enabled()) {
        if (record->event.pressed) {
            if (get_vim_mode() == VISUAL_MODE || get_vim_mode() == VISUAL_LINE_MODE) {
                // real Esc handed to qmk-vim to leave visual selection
                esc_visual_exit = true;
            } else if (replace_active) {
                normal_mode(); // leave replace mode
                return false;
            } else {
                esc_visual_exit = false;
                tap_code(KC_ESC); // plain Esc: host acts, vim mode unchanged
                return false;
            }
        } else {
            if (esc_visual_exit) {
                esc_visual_exit = false;
            }
            return false;
        }
    }

    // Caps: press = switch to Normal; Fn+Caps = toggle vim
    if (keycode == KC_CAPS) {
        bool fn_active = IS_LAYER_ON(_FL) || IS_LAYER_ON(_MFL);
        if (fn_active) {
            if (record->event.pressed) {
                toggle_vim_mode();
            }
            return false;
        }
        if (!vim_mode_enabled()) {
            return true; // vim off: Caps acts as normal Caps Lock
        }
        if (record->event.pressed) {
            normal_mode();
#ifdef VIM_DOT_REPEAT
            add_repeat_keycode(KC_NO); // stop repeat recording on Caps->Normal
#endif
        }
        return false;
    }

    if (!process_vim_mode(keycode, record)) {
        return false;
    }

    // Insert mode digit keys: plain digits pass straight through (no more
    // long-press F-row). Ctrl+digit still emits Ctrl+F1..F10.
    if (get_vim_mode() == INSERT_MODE && keycode >= KC_1 && keycode <= KC_0 && (get_mods() & MOD_MASK_CTRL) && record->event.pressed) {
        uint8_t num = (keycode == KC_0) ? 10 : (keycode - KC_1 + 1);
        tap_code(KC_F1 + num - 1);
        return false;
    }

    return true;
}

void housekeeping_task_user(void) {
    // USB plugged while powered off -> recover to normal (wired) operation
    if (pw_off && !pw_no_cable()) {
        pw_off = false;
        pw_combo = false;
        pw_del = pw_spc = false;
        suspend_wakeup_init();
    }

    // Remember the last non-USB device so unplugging can return to wireless
    if (!pw_off) {
        uint8_t cur = wireless_get_current_devs();
        if (cur != PW_DEVS_USB) pw_last_wls = cur;
    }

    // Debounced USB cable auto switch: plug -> wired, unplug -> last wireless
    bool cable = !pw_no_cable();
    if (!pw_off) {
        if (cable != pw_cable_last) {
            pw_cable_last = cable;
            pw_cable_timer = timer_read32();
        } else if (pw_cable_timer && timer_elapsed32(pw_cable_timer) >= 200) {
            pw_cable_timer = 0;
            uint8_t cur = wireless_get_current_devs();
            if (cable && cur != PW_DEVS_USB) {
                wireless_devs_change(cur, PW_DEVS_USB, false);
            } else if (!cable && cur == PW_DEVS_USB) {
                wireless_devs_change(PW_DEVS_USB, pw_last_wls, false);
            }
        }
    }

    // original-Delete(_GO) + Space held for >= 3s (no cable) -> toggle power
    if (pw_combo && timer_elapsed32(pw_combo_timer) >= PW_HOLD_MS) {
        if (pw_off) {
            pw_boot_wireless(); // deep-sleep -> boot wireless
        } else {
            pw_enter_sleep(); // running -> power off (deep sleep)
        }
    }

    hs_housekeeping_task_user();
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t r, g, b;
    if (!vim_mode_enabled()) {
        r = 0xFF; g = 0x00; b = 0x00; // red: vim off
    } else {
        switch (get_vim_mode()) {
            case NORMAL_MODE:
                r = 0x00; g = 0x00; b = 0xFF; // blue
                break;
            case INSERT_MODE:
                r = 0x00; g = 0xFF; b = 0x00; // green
                break;
            case VISUAL_MODE:
            case VISUAL_LINE_MODE:
                r = 0x80; g = 0x00; b = 0x80; // purple
                break;
            default:
                return true;
        }
    }

    rgb_matrix_set_color(6, r, g, b);  // Caps single LED (full brightness)
    rgb_matrix_set_color(56, r, g, b); // Esc single LED
    rgb_matrix_set_color(70, r, g, b); // Delete (was Insert) single LED

    uint8_t r2, g2, b2;
    if (replace_active) {
        // strip turns orange while in replace (R) mode
        r2 = 0xFF * 7 / 100;
        g2 = 0x80 * 7 / 100;
        b2 = 0;
    } else {
        r2 = r * 7 / 100; // bottom strip at 7% brightness
        g2 = g * 7 / 100;
        b2 = b * 7 / 100;
    }

    for (uint8_t i = 71; i <= 150; i++) { // bottom strip
        rgb_matrix_set_color(i, r2, g2, b2);
    }
    rgb_matrix_set_color(10, r2, g2, b2);
    rgb_matrix_set_color(11, r2, g2, b2);
    rgb_matrix_set_color(13, r2, g2, b2);
    rgb_matrix_set_color(14, r2, g2, b2);

    return true;
}
