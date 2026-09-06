// Copyright 2024 nut65-vim
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <string.h>
#include "rgb_record/rgb_record.h"
#include "qmk-vim/src/vim.h"
#include "qmk-vim/src/modes.h"
#include "qmk-vim/src/process_func.h"

// Vendor housekeeping loop, renamed in nut65.c to make room for the keymap hook
extern void hs_housekeeping_task_user(void);

// qmk-vim current keycode processor (can be swapped to drive a custom mode)
extern process_func_t process_func;

// wireless / low-power hooks used by the Ctrl+RightAlt+Insert power combo
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
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT( /* win Base */
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_DEL,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   LALT(KC_F4),
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

/* ===== Vim is always on: start in typing (Insert) mode - hold Caps for
 * Normal, long-press Esc for Normal ===== */
void keyboard_post_init_user(void) {
    enable_vim_mode();
    insert_mode();
}

/* ===== Esc visual exit tracking ===== */
static bool esc_visual_exit = false;

/* ===== Esc tap/hold: short tap = real Esc, long press = Normal mode ===== */
#define ESC_HOLD_TIME 200
static uint16_t esc_press_timer = 0;
#define SPC_HOLD_TIME 200 // Normal mode Space: short=left click, long=hold left (drag)
static uint16_t spc_press_timer = 0;
static bool     spc_holding     = false; // left button currently held down

/* ===== Normal mode arrows: L+R together = right click ===== */
static bool arrow_l = false, arrow_r = false, arrow_combo = false;

/* ===== Replace mode (vim R: overwrite chars until Esc) ===== */
static bool replace_active = false;

/* ===== Power combo: Ctrl + Right Alt + the original Insert key (row0 col14)
 * held >= 3s with no USB cable = deep-sleep power toggle. While the combo is
 * pending the involved keys are swallowed so nothing leaks to the host.
 * pw_off: any key wakes the MCU, but only a fresh >=3s combo boots wireless
 * again; every other key is swallowed and it goes straight back to sleep.
 */
#define PW_HOLD_MS 3000
static bool     pw_off = false;
static bool     pw_ctrl = false;        // combo key 1: either Ctrl
static bool     pw_ralt = false;        // combo key 2: Right Alt
static bool     pw_ins  = false;        // combo key 3: original Insert (row0 col14)
static bool     pw_combo = false;
static bool     pw_combo_latch = false; // block re-engage until all released
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
    pw_ctrl  = false;
    pw_ralt  = false;
    pw_ins   = false;
    clear_keyboard();
    lpwr_set_state(1); // LPWR_PRESLEEP -> LPWR_STOP (deep sleep)
}

static void pw_boot_wireless(void) {
    pw_off   = false;
    pw_combo = false;
    pw_ctrl  = false;
    pw_ralt  = false;
    pw_ins   = false;
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
                tap_code(KC_ENT); // real Enter in Normal mode
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

/* ===== SQL snippet completion: type a tracked keyword, then Ctrl+P =====
 * Only plain lowercase letters feed the tracking stack (max 9); bare
 * modifiers are ignored and any other typed key clears it. Ctrl+P in a
 * typing context (Insert mode or vim off) expands an exact dictionary match
 * via SEND_STRING. Extend by adding entries to sql_dict[].
 */
#define SQL_STACK_SIZE 9
static char    sql_key_stack[SQL_STACK_SIZE] = {0};
static uint8_t sql_stack_len = 0;

static void sql_push_key(uint16_t keycode) {
    if (keycode >= KC_A && keycode <= KC_Z) {
        char c = 'a' + (keycode - KC_A);
        if (sql_stack_len == SQL_STACK_SIZE) {
            memmove(sql_key_stack, sql_key_stack + 1, SQL_STACK_SIZE - 1);
            sql_stack_len = SQL_STACK_SIZE - 1;
        }
        sql_key_stack[sql_stack_len++] = c;
        return;
    }
    if (keycode >= KC_LCTL && keycode <= KC_RGUI) return; // bare modifiers
    memset(sql_key_stack, 0, SQL_STACK_SIZE);
    sql_stack_len = 0;
}

typedef struct {
    const char *keyword;
    const char *snippet;
} sql_completion_t;

static const sql_completion_t sql_dict[] = {
    {"select",
     "set isolation to dirty read;" SS_LSFT("\n")
     "select" SS_LSFT("\n")
     "*" SS_LSFT("\n")
     "from" SS_LSFT("\n")
     SS_LSFT("\n")
     "where 1=1" SS_LSFT("\n")
     "-- group by " SS_LSFT("\n")
     "-- order by " SS_LSFT("\n")
     "-- having count(*)" SS_LSFT("\n")
     "limit 20 " SS_LSFT("\n")
     ";"
     // 6x Up so the cursor rests on the blank line under "from"
     SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP)
     SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP)}
};

static void sql_trigger_completion(void) {
    if (sql_stack_len == 0) return;
    for (int i = 0; i < (int)(sizeof(sql_dict) / sizeof(sql_completion_t)); i++) {
        const char *kw   = sql_dict[i].keyword;
        int kw_len       = strlen(kw);
        if (sql_stack_len != kw_len) continue;
        bool match = true;
        for (int j = 0; j < sql_stack_len; j++) {
            if (sql_key_stack[j] != kw[j]) { match = false; break; }
        }
        if (!match) continue;
        uint8_t saved_mods = get_mods();
        clear_mods(); // the held Ctrl must not pollute the typed snippet
        for (int b = 0; b < kw_len; b++) {
            tap_code(KC_BSPC); // erase the typed keyword, the snippet replaces it
        }
        SEND_STRING(sql_dict[i].snippet);
        set_mods(saved_mods);
        memset(sql_key_stack, 0, SQL_STACK_SIZE);
        sql_stack_len = 0;
        return;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pw_ok = (wireless_get_current_devs() != PW_DEVS_USB); // combo only off-wire

    // ---- Original Insert key (row0 col14): third key of the power combo
    // (Ctrl + Right Alt + Ins). Swallowed while the combo is pending so no
    // key leaks; normal Delete / Insert otherwise. ----
    if (record->event.key.row == 0 && record->event.key.col == 14) {
        pw_ins = record->event.pressed;
        if (pw_off) {
            if (!record->event.pressed) pw_enter_sleep(); // released: aborted combo
            return false;
        }
        if (pw_combo || (pw_ok && pw_ralt && pw_ctrl)) return false;
        return true;
    }

    // ---- Right Alt: second key of the power combo; normal Right Alt
    // otherwise. ----
    if (keycode == KC_RALT) {
        pw_ralt = record->event.pressed;
        if (pw_off) {
            if (!record->event.pressed) pw_enter_sleep(); // released: aborted combo
            return false;
        }
        return true;
    }

    // ---- Ctrl: first key of the power combo; tracked only, normal use
    // untouched. ----
    if (keycode == KC_LCTL || keycode == KC_RCTL) {
        pw_ctrl = record->event.pressed;
        if (pw_off) {
            if (!record->event.pressed) pw_enter_sleep(); // released: aborted combo
            return false;
        }
        return true;
    }

    // ---- Powered off (deep sleep): only the combo wakes, everything else is
    // swallowed and the board goes straight back to sleep. ----
    if (pw_off) {
        if (record->event.pressed) pw_enter_sleep();
        return false;
    }

    // ---- Right Shift combos (replaces the old _GO layer): Right Shift + Esc
    // = grave (add left Shift for ~), Right Shift + 1..0/-/= = F1..F12. Any
    // other key keeps normal right-shift behaviour. ----
    // NOTE: get_mods() is the 8-bit HID mod byte, while the MOD_R*/MOD_L*
    // constants are QMK's 5-bit packed encoding (MOD_RSFT=0x12 would match
    // Left-Shift 0x02 and Right-Ctrl 0x10 instead!). Always mask with the
    // 8-bit MOD_BIT_* constants here.
    if ((keycode == KC_ESC) && (get_mods() & MOD_BIT_LSHIFT) &&
        !(get_mods() & (MOD_BIT_LCTRL | MOD_BIT_RCTRL | MOD_BIT_LALT | MOD_BIT_RALT | MOD_BIT_LGUI | MOD_BIT_RGUI))) {
        // Left Shift + Esc = ~ (Right Shift may also be held); Right-Shift-only
        // + Esc falls through to the combo block below and sends grave.
        // All other modifiers still let Esc through.
        if (record->event.pressed) {
            uint8_t saved_mods = get_mods();
            clear_mods();
            tap_code16(LSFT(KC_GRV)); // ~
            set_mods(saved_mods);
        }
        return false;
    }
    if ((get_mods() & MOD_BIT_RSHIFT) &&
        (keycode == KC_ESC || (keycode >= KC_1 && keycode <= KC_0) || keycode == KC_MINS || keycode == KC_EQL)) {
        if (record->event.pressed) {
            uint16_t repl;
            if (keycode == KC_ESC) {
                repl = KC_GRV; // Left+Right Shift = ~ is handled above
            } else if (keycode == KC_MINS) {
                repl = KC_F11;
            } else if (keycode == KC_EQL) {
                repl = KC_F12;
            } else {
                uint8_t num = (keycode == KC_0) ? 10 : (keycode - KC_1 + 1);
                repl        = KC_F1 + num - 1;
            }
            uint8_t saved_mods = get_mods();
            clear_mods(); // the held Right Shift must not shift the F-keys
            tap_code16(repl);
            set_mods(saved_mods);
        }
        return false;
    }

    // ---- Right Shift + WASD = media keys: A/D = volume down/up,
    // W/S = brightness up/down. Press requires Right Shift; release
    // always unregisters (even if Right Shift was let go first) so the
    // media key can never stick. Arrows keep their normal behaviour. ----
    if (keycode == KC_A || keycode == KC_D || keycode == KC_W || keycode == KC_S) {
        static bool rsft_wasd_active = false;
        if (record->event.pressed) {
            if (get_mods() & MOD_BIT_RSHIFT) {
                rsft_wasd_active = true;
                switch (keycode) {
                    case KC_A: register_code(KC_VOLD); break; // volume down
                    case KC_D: register_code(KC_VOLU); break; // volume up
                    case KC_W: register_code(KC_BRIU); break; // brightness up
                    case KC_S: register_code(KC_BRID); break; // brightness down
                }
                return false;
            }
        } else if (rsft_wasd_active) {
            rsft_wasd_active = false;
            unregister_code(KC_VOLD);
            unregister_code(KC_VOLU);
            unregister_code(KC_BRIU);
            unregister_code(KC_BRID);
            return false;
        }
    }

    // Esc: short tap sends a real Esc to the host (firmware mode unchanged);
    // long press (>=200ms, decided on release) switches the firmware to
    // Normal mode without sending a key. Visual modes hand the tap to
    // qmk-vim (native exit); replace mode exits on the press.
    if (keycode == KC_ESC && vim_mode_enabled()) {
        if (record->event.pressed) {
            if (get_vim_mode() == VISUAL_MODE || get_vim_mode() == VISUAL_LINE_MODE) {
                // real Esc handed to qmk-vim to leave visual selection
                esc_visual_exit = true;
            } else if (replace_active) {
                normal_mode(); // leave replace mode
                return false;
            } else {
                // Cancel any pending vim operator (d/y/c ... awaiting a motion
                // or double tap). normal_mode() is idempotent in Normal mode and
                // resets process_func so a following key cannot be eaten by the
                // half-typed action. Insert mode is untouched (it must keep
                // typing and only deliver the real Esc to the host).
                if (get_vim_mode() != INSERT_MODE) {
                    normal_mode();
                }
                esc_visual_exit = false;
                esc_press_timer = timer_read(); // decide tap vs hold on release
                return false;
            }
        } else {
            if (esc_visual_exit) {
                esc_visual_exit = false;
                return false;
            }
            if (esc_press_timer && timer_elapsed(esc_press_timer) >= ESC_HOLD_TIME) {
                esc_press_timer = 0;
                normal_mode(); // long press -> Normal mode
                return false;
            }
            esc_press_timer = 0;
            tap_code(KC_ESC); // short tap -> real Esc
            return false;
        }
    }

    // Caps: hold = momentary Normal mode, release = back to typing (Insert).
    // Fn+Caps still toggles vim; vim off lets Caps act as normal Caps Lock.
    if (keycode == KC_CAPS) {
        bool fn_active = IS_LAYER_ON(_FL) || IS_LAYER_ON(_MFL);
        if (fn_active) {
            if (record->event.pressed) {
                toggle_vim_mode();
                insert_mode(); // vim on -> resting typing mode; off -> harmless
                               // engine reset (process_func / replace state)
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
        } else {
            insert_mode(); // released -> back to typing mode
        }
        return false;
    }

    // ---- Normal mode mouse emulation: physical arrows move the mouse
    // pointer (hjkl stays the text cursor), Space short = left click,
    // Space long (>=200ms) = hold left button (drag), Left+Right arrows
    // pressed together = right click. Only without modifiers, so
    // Shift+arrow etc. keep their plain behaviour; Insert and Visual
    // modes are untouched. Enter stays a normal Enter. ----
    if (vim_mode_enabled() && get_vim_mode() == NORMAL_MODE && get_mods() == 0) {
        uint16_t ms = 0;
        switch (keycode) {
            case KC_UP:   ms = KC_MS_UP;   break;
            case KC_DOWN: ms = KC_MS_DOWN; break;
            case KC_LEFT:
            case KC_RGHT: {
                if (record->event.pressed) {
                    if (keycode == KC_LEFT) arrow_l = true;
                    else                    arrow_r = true;
                    if (arrow_l && arrow_r) { // both held -> right click, no move
                        if (!arrow_combo) {
                            arrow_combo = true;
                            tap_code(KC_BTN2);
                        }
                        unregister_code(KC_MS_LEFT);
                        unregister_code(KC_MS_RIGHT);
                    } else {
                        register_code(keycode == KC_LEFT ? KC_MS_LEFT : KC_MS_RIGHT);
                    }
                } else {
                    if (keycode == KC_LEFT) arrow_l = false;
                    else                    arrow_r = false;
                    if (!(arrow_l && arrow_r)) arrow_combo = false;
                    unregister_code(KC_MS_LEFT);
                    unregister_code(KC_MS_RIGHT);
                    // resume the still-held single direction after the combo
                    if (arrow_l)      register_code(KC_MS_LEFT);
                    else if (arrow_r) register_code(KC_MS_RIGHT);
                }
                return false;
            }
            case KC_SPC:
                if (record->event.pressed) {
                    spc_press_timer = timer_read(); // short=click, long=hold
                } else {
                    if (spc_holding) { // long hold -> release left button (drag end)
                        unregister_code(KC_BTN1);
                        spc_holding = false;
                    } else if (spc_press_timer) { // short tap -> left click
                        tap_code(KC_BTN1);
                    }
                    spc_press_timer = 0;
                }
                return false;
            default:
                break;
        }
        if (ms) {
            if (record->event.pressed) {
                register_code(ms);   // hold to keep moving (QMK mouse accel)
            } else {
                unregister_code(ms);
            }
            return false;
        }
    }

    // ---- Alt+Tab: pass Tab through with the held Alt so the task switcher
    // stays open; vim normal mode would tap LALT(Tab), releasing Alt. ----
    if (keycode == KC_TAB && (get_mods() & MOD_MASK_ALT)) {
        return true;
    }

    // ---- SQL completion trigger: Ctrl+P expands the tracked keyword.
    // Typing contexts only (Insert mode or vim off). ----
    if (record->event.pressed && keycode == KC_P && (get_mods() & MOD_MASK_CTRL) &&
        (!vim_mode_enabled() || get_vim_mode() == INSERT_MODE)) {
        sql_trigger_completion();
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

    // Track actually-typed keys for the SQL completion stack
    if (record->event.pressed) {
        sql_push_key(keycode);
    }
    return true;
}

void housekeeping_task_user(void) {
    // Space long-press (Normal mode): once SPC_HOLD_TIME elapses while the
    // key is still down, hold the left button down (drag) until release.
    if (spc_press_timer && !spc_holding && timer_elapsed(spc_press_timer) >= SPC_HOLD_TIME) {
        register_code(KC_BTN1);
        spc_holding = true;
    }

    // USB plugged (or devs switched to USB) while powered off -> recover to
    // normal wired operation (RGB was disabled by the vendor presleep, so
    // force it back on here just like the combo boot does)
    if (pw_off && (wireless_get_current_devs() == PW_DEVS_USB || !pw_no_cable())) {
        pw_off = false;
        pw_combo = false;
        pw_ctrl = pw_ralt = pw_ins = false;
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

    // Power combo: Ctrl + Right Alt + original Insert key held >= 3s
    // (wireless only) -> toggle deep sleep / boot wireless. Engage clears the
    // keyboard report so nothing leaks while holding; the latch blocks a
    // re-engage until all three keys are released again.
    bool combo_now = (wireless_get_current_devs() != PW_DEVS_USB) && pw_ctrl && pw_ralt && pw_ins;
    if (pw_combo_latch) {
        if (!combo_now) pw_combo_latch = false; // all released -> re-arm
    } else if (combo_now && !pw_combo) {
        pw_combo       = true;
        pw_combo_timer = timer_read32();
        clear_keyboard();
    } else if (pw_combo && !combo_now) {
        pw_combo = false; // aborted before firing
    }
    if (pw_combo && timer_elapsed32(pw_combo_timer) >= PW_HOLD_MS) {
        pw_combo       = false;
        pw_combo_latch = true;
        if (pw_off) {
            pw_boot_wireless(); // deep-sleep -> boot wireless
        } else {
            pw_enter_sleep();   // running -> power off (deep sleep)
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

    // Mode keys at 33% brightness
    // Mode keys at 75% brightness (Caps no longer has a fixed light; the
    // global effect is Solid Reactive Nexus, so Caps participates in it)
    uint8_t k_r = r * 75 / 100, k_g = g * 75 / 100, k_b = b * 75 / 100;
    rgb_matrix_set_color(56, k_r, k_g, k_b); // Esc LED
    rgb_matrix_set_color(70, k_r, k_g, k_b); // Delete (was Insert) LED

    // Bottom strip = battery level (highest priority). Number of lit LEDs is
    // fixed by the charge level (both ends turned off toward the middle), the
    // mode only chooses the colour. Strip brightness: 9%.
    uint8_t c_r = r;
    uint8_t c_g = g;
    uint8_t c_b = b;
    if (replace_active) { // replace (R) mode is shown orange
        c_r = 0xFF;
        c_g = 0x80;
        c_b = 0x00;
    }
    c_r = c_r * 7 / 100;
    c_g = c_g * 7 / 100;
    c_b = c_b * 7 / 100;

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
