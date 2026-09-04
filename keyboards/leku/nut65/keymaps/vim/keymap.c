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
extern bool hs_usb_active(void);
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
    GO_RSFT = SAFE_RANGE, // hold the right Shift key to switch into the _GO layer
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT( /* win Base */
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_DEL,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_GRV,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    KC_WFWD,
        KC_LSFT,              KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  GO_RSFT,  KC_UP,     KC_WBAK,
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

/* ===== Power combo: the original Delete key (row1 col14, now grave `) +
 * Space held >= 3s with no USB cable = deep-sleep power toggle.
 * pw_off: any key wakes the MCU, but only a fresh >=3s combo boots wireless
 * again; every other key is swallowed and it goes straight back to sleep.
 */
#define PW_HOLD_MS 3000
static bool     pw_off = false;
static bool     pw_del = false; // the original-Delete (grave) combo key
static bool     pw_spc = false;
static bool     pw_combo = false;
static uint32_t pw_combo_timer = 0;
static uint8_t  pw_last_wls = PW_DEVS_2G4;   // remembered non-USB device
static bool     pw_last_valid = false;       // whether a real wireless devs seen
static uint8_t  pw_frozen_wls = PW_DEVS_2G4; // device right before switching to USB
static bool     pw_frozen_valid = false;
static uint32_t pw_cable_timer = 0;
static bool     pw_wired_prev = false;     // last cycle's wired state (edge detect)
static bool     pw_recover_armed = false;  // force-back window after unplug

// Fired by the wireless stack on every device switch - freeze the wireless
// device in use right before we go to USB (that is what unplug must return
// to), and keep the last wireless slot for boot.
void wireless_devs_change_user(uint8_t old_devs, uint8_t new_devs, bool reset) {
    if (new_devs == PW_DEVS_USB) {
        if (old_devs != PW_DEVS_USB) { // leaving wireless for wired: freeze it
            pw_frozen_wls   = old_devs;
            pw_frozen_valid = true;
        }
    } else {
        pw_last_wls   = new_devs;
        pw_last_valid = true;
    }
}

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
    // Stale frozen device from before the sleep must not force itself back
    // after boot - manual BT/2.4G switching has to work again.
    pw_frozen_valid  = false;
    pw_recover_armed = false;
    // Restore LEDs/RGB explicitly (vendor wakeup_cb may skip RGB when its
    // rgb_enable_bak got cleared by the intermediate presleep), then drive
    // the vendor LPWR through WAKEUP to finish the normal wake path.
    rgb_matrix_enable_noeeprom();
    suspend_wakeup_init();
    lpwr_set_state(3); // LPWR_WAKEUP
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
#ifdef VIM_NUMBERED_JUMPS
    { // consume any stale count so a leftover "3" cannot turn the next
      // dd/cc/yy into a multi-line operation
        extern int16_t motion_counter;
        motion_counter = 0;
    }
#endif
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
    bool pw_ok = (wireless_get_current_devs() != PW_DEVS_USB); // combo only off-wire
    // ---- Right Shift (_BL): hold to switch into the _GO layer (F-row +
    // grave). No shift function on this key - use the left Shift for that. ----
    if (keycode == GO_RSFT) {
        if (record->event.pressed) {
            if (pw_off) {
                pw_enter_sleep(); // off: not the combo, straight back to sleep
                return false;
            }
            layer_on(_GO);
        } else {
            layer_off(_GO);
        }
        return false;
    }

    // ---- Grave key (row1 col14, the original Delete position): normal `~
    // typing, and the power-combo key (identified by matrix position so the
    // _GO layer's own grave never arms it). ----
    if (keycode == KC_GRV) {
        bool is_pw_key = (record->event.key.row == 1 && record->event.key.col == 14);
        if (record->event.pressed) {
            if (is_pw_key && pw_ok) {
                pw_del = true;
                if (pw_del && pw_spc && !pw_combo) { // power combo engaged
                    pw_combo       = true;
                    pw_combo_timer = timer_read32();
                    clear_keyboard();
                    return false;
                }
            }
            if (pw_off) {
                pw_enter_sleep();
                return false;
            }
            return true; // normal `~ behaviour
        } else {
            if (is_pw_key && pw_ok) {
                pw_del = false;
                if (pw_combo) pw_combo = false;
            }
            if (pw_off) pw_enter_sleep(); // released without a full combo
            return true;
        }
    }

    // ---- Space: single press behaves normally; also arm the power combo. ----
    if (keycode == KC_SPC) {
        if (record->event.pressed) {
            if (pw_ok) {
                pw_spc = true;
                if (pw_del && pw_spc && !pw_combo) { // power combo engaged
                    pw_combo       = true;
                    pw_combo_timer = timer_read32();
                    clear_keyboard();
                    return false;
                }
            }
            if (pw_off) return false;
            return true; // normal space behaviour
        } else {
            if (pw_ok) {
                pw_spc = false;
                if (pw_combo) pw_combo = false;
            }
            if (pw_off) pw_enter_sleep();
            return true;
        }
    }

    // ---- Powered off (deep sleep): only the combo wakes, everything else is
    // swallowed and the board goes straight back to sleep. ----
    if (pw_off) {
        if (record->event.pressed) pw_enter_sleep();
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
                normal_mode(); // reset the engine: process_func / replace state /
                               // stale counters, even if vim was toggled off
                               // while inside R replace mode
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
    // USB plugged (or devs switched to USB) while powered off -> recover to
    // normal wired operation (RGB was disabled by the vendor presleep, so
    // force it back on here just like the combo boot does)
    if (pw_off && (wireless_get_current_devs() == PW_DEVS_USB || !pw_no_cable())) {
        pw_off = false;
        pw_combo = false;
        pw_del = pw_spc = false;
        rgb_matrix_enable_noeeprom();
        suspend_wakeup_init();
    }

    // USB auto switch driven by the live USB host (plus cable pin fallback).
    // Plug  -> switch to wired USB.
    // Unplug -> return to the wireless device that was in use right before
    // USB (frozen in wireless_devs_change_user), even if the vendor stack
    // already hopped to another slot (e.g. default 2.4G). The force-back only
    // lives inside a short recovery window right after unplug - once the
    // frozen device is reached (or the user picks a device manually) manual
    // BT/2.4G switching is free again.
    if (!pw_off) {
        bool usb_host   = hs_usb_active();
        bool line_cable = !pw_no_cable(); // pin fall back
        bool wired      = usb_host || line_cable;

        if (wired != pw_wired_prev) { // plug / unplug edge
            pw_wired_prev    = wired;
            pw_cable_timer   = timer_read32();
            pw_recover_armed = !wired; // arm the force-back window on unplug
        }

        if (wired) {
            pw_recover_armed = false;
            uint8_t cur = wireless_get_current_devs();
            if (cur != PW_DEVS_USB) {
                if (!pw_cable_timer) pw_cable_timer = timer_read32();
                if (timer_elapsed32(pw_cable_timer) >= 80) {
                    pw_cable_timer = 0;
                    wireless_devs_change(cur, PW_DEVS_USB, false); // plug -> wired
                }
            } else {
                pw_cable_timer = 0;
            }
        } else {
            uint8_t cur = wireless_get_current_devs();
            if (pw_recover_armed) {
                uint8_t target = pw_frozen_valid ? pw_frozen_wls : pw_last_wls;
                if (cur != target) {
                    // retry (throttled) until the frozen wireless device wins
                    if (!pw_cable_timer || timer_elapsed32(pw_cable_timer) >= 60) {
                        pw_cable_timer = timer_read32();
                        wireless_devs_change(cur, target, false);
                    }
                } else {
                    pw_cable_timer   = 0;
                    pw_recover_armed = false; // recovered; manual switching free
                }
            } else {
                pw_cable_timer = 0;
            }
            // extra safety: never sleep while stuck on USB with no host
            if (cur == PW_DEVS_USB && !usb_host) {
                lpwr_set_timeout_manual(false);
                lpwr_set_state(0);
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

extern uint8_t *md_getp_bat(void);

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

    // Bottom strip = battery level (highest priority). Number of lit LEDs is
    // fixed by the charge level (both ends turned off toward the middle), the
    // mode only chooses the colour.
    uint8_t c_r = r;
    uint8_t c_g = g;
    uint8_t c_b = b;
    if (replace_active) { // replace (R) mode is shown orange
        c_r = 0xFF;
        c_g = 0x80;
        c_b = 0x00;
    }
    c_r /= 2; // keep the strip readable but not dazzling
    c_g /= 2;
    c_b /= 2;

    uint8_t bat;
    if (wireless_get_current_devs() == PW_DEVS_USB) {
        bat = 100; // wired: bottom strip stays fully lit
    } else {
        bat = *md_getp_bat(); // wireless: real battery level
    }
    if (bat > 100) bat = 100;
    uint8_t lit = (uint8_t)(((uint16_t)bat * 80) / 100); // 80 strip LEDs
    uint8_t lo  = (80 - lit) / 2;                        // lit band centred

    for (uint8_t i = 71; i <= 150; i++) {
        uint8_t pos = i - 71;
        if (pos >= lo && pos < lo + lit) {
            rgb_matrix_set_color(i, c_r, c_g, c_b);
        } else {
            rgb_matrix_set_color(i, 0, 0, 0); // turned off from both ends
        }
    }
    rgb_matrix_set_color(10, 0, 0, 0);
    rgb_matrix_set_color(11, 0, 0, 0);
    rgb_matrix_set_color(13, 0, 0, 0);
    rgb_matrix_set_color(14, 0, 0, 0);

    return true;
}
