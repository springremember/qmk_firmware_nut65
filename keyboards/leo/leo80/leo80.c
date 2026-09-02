// Copyright 2024 sdk66 (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "wls/wls.h"
#include "rgb_record/rgb_record.h"
#include "rgb_record/rgb_rgblight.h"

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, CS18_SW2,  CS17_SW2,  CS16_SW2   },  // 0  Esc
    {0, CS18_SW3,  CS17_SW3,  CS16_SW3   },  // 1  F1
    {0, CS18_SW4,  CS17_SW4,  CS16_SW4   },  // 2  F2
    {0, CS18_SW5,  CS17_SW5,  CS16_SW5   },  // 3  F3
    {0, CS18_SW6,  CS17_SW6,  CS16_SW6   },  // 4  F4
    {0, CS18_SW7,  CS17_SW7,  CS16_SW7   },  // 5  F5
    {0, CS18_SW8,  CS17_SW8,  CS16_SW8   },  // 6  F6
    {0, CS18_SW9,  CS17_SW9,  CS16_SW9   },  // 7  F7
    {0, CS18_SW10, CS17_SW10, CS16_SW10  },  // 8  F8
    {0, CS18_SW11, CS17_SW11, CS16_SW11  },  // 9  F9
    {0, CS18_SW12, CS17_SW12, CS16_SW12  },  // 10 F10
    {1, CS18_SW1,  CS17_SW1,  CS16_SW1   },  // 11 F11
    {1, CS18_SW2,  CS17_SW2,  CS16_SW2   },  // 12 F12
    {1, CS18_SW3,  CS17_SW3,  CS16_SW3   },  // 13 MUTE
    {1, CS18_SW4,  CS17_SW4,  CS16_SW4   },  // 14 PSCR
    {1, CS18_SW5,  CS17_SW5,  CS16_SW5   },  // 15 SCRL
    {1, CS18_SW6,  CS17_SW6,  CS16_SW6   },  // 16 PAUSE

    {0, CS15_SW2,  CS14_SW2,  CS13_SW2   },  // 17 `~
    {0, CS15_SW3,  CS14_SW3,  CS13_SW3   },  // 18 1
    {0, CS15_SW4,  CS14_SW4,  CS13_SW4   },  // 19 2
    {0, CS15_SW5,  CS14_SW5,  CS13_SW5   },  // 20 3
    {0, CS15_SW6,  CS14_SW6,  CS13_SW6   },  // 21 4
    {0, CS15_SW7,  CS14_SW7,  CS13_SW7   },  // 22 5
    {0, CS15_SW8,  CS14_SW8,  CS13_SW8   },  // 23 6
    {0, CS15_SW9,  CS14_SW9,  CS13_SW9   },  // 24 7
    {0, CS15_SW10, CS14_SW10, CS13_SW10  },  // 25 8
    {0, CS15_SW11, CS14_SW11, CS13_SW11  },  // 26 9
    {0, CS15_SW12, CS14_SW12, CS13_SW12  },  // 27 0
    {1, CS15_SW1,  CS14_SW1,  CS13_SW1   },  // 28 -_
    {1, CS15_SW2,  CS14_SW2,  CS13_SW2   },  // 29 =+
    {1, CS15_SW3,  CS14_SW3,  CS13_SW3   },  // 30 BSPC
    {1, CS15_SW4,  CS14_SW4,  CS13_SW4   },  // 31 INS
    {1, CS15_SW5,  CS14_SW5,  CS13_SW5   },  // 32 HOME
    {1, CS15_SW6,  CS14_SW6,  CS13_SW6   },  // 33 PGUP

    {0, CS12_SW2,  CS11_SW2,  CS10_SW2   },  // 34 Tab
    {0, CS12_SW3,  CS11_SW3,  CS10_SW3   },  // 35 Q
    {0, CS12_SW4,  CS11_SW4,  CS10_SW4   },  // 36 W
    {0, CS12_SW5,  CS11_SW5,  CS10_SW5   },  // 37 E
    {0, CS12_SW6,  CS11_SW6,  CS10_SW6   },  // 38 R
    {0, CS12_SW7,  CS11_SW7,  CS10_SW7   },  // 39 T
    {0, CS12_SW8,  CS11_SW8,  CS10_SW8   },  // 40 Y
    {0, CS12_SW9,  CS11_SW9,  CS10_SW9   },  // 41 U
    {0, CS12_SW10, CS11_SW10, CS10_SW10  },  // 42 I
    {0, CS12_SW11, CS11_SW11, CS10_SW11  },  // 43 O
    {0, CS12_SW12, CS11_SW12, CS10_SW12  },  // 44 P
    {1, CS12_SW1,  CS11_SW1,  CS10_SW1   },  // 45 [{
    {1, CS12_SW2,  CS11_SW2,  CS10_SW2   },  // 48 ]}
    {1, CS12_SW3,  CS11_SW3,  CS10_SW3   },  // 47 \|
    {1, CS12_SW4,  CS11_SW4,  CS10_SW4   },  // 48 Del
    {1, CS12_SW5,  CS11_SW5,  CS10_SW5   },  // 49 End
    {1, CS12_SW6,  CS11_SW6,  CS10_SW6   },  // 50 PGDN

    {0, CS1_SW2,   CS2_SW2,   CS3_SW2    },  // 51 Caps
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3    },  // 52 A
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4    },  // 33 S
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5    },  // 54 D
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6    },  // 55 F
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7    },  // 56 G
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8    },  // 57 H
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9    },  // 58 J
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10   },  // 59 K
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11   },  // 60 L
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12   },  // 61 ;:
    {1, CS1_SW1,   CS2_SW1,   CS3_SW1    },  // 62 '
    {1, CS1_SW2,   CS2_SW2,   CS3_SW2    },  // 63 #~
    {1, CS1_SW3,   CS2_SW3,   CS3_SW3    },  // 64 Enter

    {0, CS4_SW2,   CS5_SW2,   CS6_SW2    },  // 65 Shift
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3    },  // 66 NUBS
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4    },  // 67 Z
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5    },  // 68 X
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6    },  // 69 C
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7    },  // 70 V
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8    },  // 71 B
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9    },  // 72 N
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10   },  // 73 M
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11   },  // 74 ,<
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12   },  // 75 .>
    {1, CS4_SW1,   CS5_SW1,   CS6_SW1    },  // 76 ?
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3    },  // 77 Shift
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5    },  // 78 Up

    {0, CS7_SW2,   CS8_SW2,   CS9_SW2    },  // 79 Ctrl_L
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3    },  // 80 Win_L
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4    },  // 81 ALT_L
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8    },  // 82 SPACE
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12   },  // 83 ALT_L
    {1, CS7_SW1,   CS8_SW1,   CS9_SW1    },  // 84 Win_L
    {1, CS7_SW2,   CS8_SW2,   CS9_SW2    },  // 85 Fn
    {1, CS7_SW3,   CS8_SW3,   CS9_SW3    },  // 86 Ctrl_L
    {1, CS7_SW4,   CS8_SW4,   CS9_SW4    },  // 87 Left
    {1, CS7_SW5,   CS8_SW5,   CS9_SW5    },  // 88 Down
    {1, CS7_SW6,   CS8_SW6,   CS9_SW6    },  // 89 Right

    {1, CS1_SW5,   CS2_SW5,   CS3_SW5    },  // 100 SideLight_10
    {1, CS1_SW6,   CS2_SW6,   CS3_SW6,   },  // 101 SideLight_11
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7,   },  // 102 SideLight_12
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8,   },  // 103 SideLight_13
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9,   },  // 104 SideLight_14
    {1, CS1_SW10,  CS2_SW10,  CS3_SW10,  },  // 105 SideLight_15
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11,  },  // 106 SideLight_16

    {0, CS18_SW1,  CS17_SW1,  CS16_SW1   },  // 90  SideLight_0
    {0, CS15_SW1,  CS14_SW1,  CS13_SW1   },  // 91  SideLight_1
    {0, CS12_SW1,  CS11_SW1,  CS10_SW1   },  // 92  SideLight_2
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1    },  // 93  SideLight_3
    {0, CS4_SW1,   CS5_SW1,   CS6_SW1    },  // 94  SideLight_4
    {1, CS4_SW12,  CS5_SW12,  CS6_SW12   },  // 99  SideLight_9
    {1, CS1_SW12,  CS2_SW12,  CS3_SW12   },  // 98  SideLight_8
    {1, CS12_SW12, CS11_SW12, CS10_SW12  },  // 97  SideLight_7
    {1, CS15_SW12, CS14_SW12, CS13_SW12  },  // 96  SideLight_6
    {1, CS18_SW12, CS17_SW12, CS16_SW12  },  // 95  SideLight_5
};

#ifdef WIRELESS_ENABLE
#    include "wireless.h"
#    include "usb_main.h"
#    include "lowpower.h"
#endif

typedef union {
    uint32_t raw;
    struct {
        uint8_t leo_mod_index: 4;
        uint8_t leo_hui_index: 4;
        uint8_t record_last_mode;
        uint8_t devs : 3;
        uint8_t last_btdevs : 3;
        uint8_t rgb_hsv_index :3;
    };
} confinfo_t;
confinfo_t confinfo;

typedef struct {
    bool active;
    uint32_t timer;
    uint32_t interval;
    uint32_t times;
    uint8_t index;
    RGB rgb;
    void (*blink_cb)(uint8_t);
} hs_rgb_indicator_t;

uint16_t rgb_hsvs[7][2] = {   
    {0,255},
    {85,255},
    {170,255},
    {43,255},
    {191,255},
    {128,255},
    {0,0},
};

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _DEFA,
};

static uint8_t leo_modes[] = {WATERFALLLIGHT, DISCOLORATION, STEADYRED, MONOCHROMATICRESPIRATION, NEONLAMP, 0};
static uint8_t leo_hsvs[][3] = {
    {HSV_RED},
    {HSV_ORANGE},
    {HSV_YELLOW},
    {HSV_GREEN},
    {HSV_CYAN},
    {HSV_BLUE},
    {HSV_PURPLE},
    {HSV_WHITE}
};

hs_rgb_indicator_t hs_rgb_indicators[HS_RGB_INDICATOR_COUNT];
hs_rgb_indicator_t hs_rgb_bat[HS_RGB_BAT_COUNT];

void rgb_blink_dir(void);
void hs_reset_settings(void);
void rgb_matrix_hs_indicator(void);
void rgb_matrix_hs_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times);
void rgb_matrix_hs_set_remain_time(uint8_t index, uint8_t remain_time);

#define keymap_is_mac_system() ((get_highest_layer(default_layer_state) == _MBL) || (get_highest_layer(default_layer_state) == _MFL))
#define keymap_is_base_layer() ((get_highest_layer(default_layer_state) == _BL) || (get_highest_layer(default_layer_state) == _FL))

uint32_t post_init_timer     = 0x00;
bool inqbat_flag             = false;
bool mac_status              = false;
bool charging_state          = false;
bool bat_full_flag           = false;
bool enable_bat_indicators   = true;
uint32_t bat_indicator_cnt   = true;
static uint32_t ee_clr_timer = 0;
bool test_white_light_flag   = false;
bool lower_sleep             = false;
HSV start_hsv;

void eeconfig_confinfo_update(uint32_t raw) {

    eeconfig_update_kb(raw);
}

uint32_t eeconfig_confinfo_read(void) {

    return eeconfig_read_kb();
}

void eeconfig_confinfo_default(void) {

    confinfo.record_last_mode = 0xff;
    confinfo.last_btdevs      = 1;
    confinfo.leo_mod_index    = 0;
    confinfo.leo_hui_index    = 0;

    // #ifdef WIRELESS_ENABLE
    //     confinfo.devs = DEVS_USB;
    // #endif

    
    eeconfig_init_user_datablock();
    eeconfig_confinfo_update(confinfo.raw);

#ifdef RGBLIGHT_ENABLE
    rgblight_mode(leo_modes[confinfo.leo_mod_index]);
#endif
}

void eeconfig_confinfo_init(void) {

    confinfo.raw = eeconfig_confinfo_read();
    if (!confinfo.raw) {
        eeconfig_confinfo_default();
    }
}

void keyboard_post_init_kb(void) {

#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
    keymap_config.no_gui = 0;
    eeconfig_confinfo_init();

#ifdef LED_POWER_EN_PIN
    gpio_set_pin_output(LED_POWER_EN_PIN);
    gpio_write_pin_high(LED_POWER_EN_PIN);

#endif

#ifdef MM_BT_DEF_PIN
    setPinInputHigh(MM_BT_DEF_PIN);
#endif

#ifdef MM_2G4_DEF_PIN
    setPinInputHigh(MM_2G4_DEF_PIN);
#endif

#ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);
#endif

#ifdef HS_BAT_CABLE_PIN
    setPinInput(HS_BAT_CABLE_PIN);
#endif

#ifdef BAT_FULL_PIN
    setPinInputHigh(BAT_FULL_PIN);
#endif

#ifdef WIRELESS_ENABLE
    wireless_init();
    // wireless_devs_change(!confinfo.devs, confinfo.devs, false);
    post_init_timer = timer_read32();
#endif

    keyboard_post_init_user();
}

#ifdef WIRELESS_ENABLE

void usb_power_connect(void) {

#    ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
#    endif
}

void usb_power_disconnect(void) {

#    ifdef USB_POWER_EN_PIN
    gpio_write_pin_high(USB_POWER_EN_PIN);
#    endif
}

void suspend_power_down_kb(void) {

#    ifdef LED_POWER_EN_PIN
    gpio_write_pin_low(LED_POWER_EN_PIN);
#    endif

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {

#    ifdef LED_POWER_EN_PIN
    gpio_write_pin_high(LED_POWER_EN_PIN);
#    endif

    wireless_devs_change(wireless_get_current_devs(), wireless_get_current_devs(), false);
    suspend_wakeup_init_user();
    hs_rgb_blink_set_timer(timer_read32());
}

bool lpwr_is_allow_timeout_hook(void) {

    if (wireless_get_current_devs() == DEVS_USB) {
        return false;
    }

    return true;
}

void wireless_post_task(void) {

    // auto switching devs
    if (post_init_timer && timer_elapsed32(post_init_timer) >= 100) {

        md_send_devctrl(MD_SND_CMD_DEVCTRL_FW_VERSION);   // get the module fw version.
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);  // timeout 30min to sleep in bt mode, enable
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN); // timeout 30min to sleep in 2.4g mode, enable
        wireless_devs_change(!confinfo.devs, confinfo.devs, false);
        post_init_timer = 0x00;
    }

    hs_mode_scan(false, confinfo.devs, confinfo.last_btdevs);
}

uint32_t wls_process_long_press(uint32_t trigger_time, void *cb_arg) {
    uint16_t keycode = *((uint16_t *)cb_arg);

    switch (keycode) {
        case KC_BT1: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, true);
            }

        } break;
        case KC_BT2: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
            }
        } break;
        case KC_BT3: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, true);
            }
        } break;
        case KC_2G4: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_2g4) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, true);
            }
        } break;
        case EE_CLR: {

        } break;
        default:
            break;
    }

    return 0;
}

bool process_record_wls(uint16_t keycode, keyrecord_t *record) {
    static uint16_t keycode_shadow                     = 0x00;
    static deferred_token wls_process_long_press_token = INVALID_DEFERRED_TOKEN;

    keycode_shadow = keycode;

#    ifndef WLS_KEYCODE_PAIR_TIME
#        define WLS_KEYCODE_PAIR_TIME 3000
#    endif

#    define WLS_KEYCODE_EXEC(wls_dev)                                                                                          \
        do {                                                                                                                   \
            if (record->event.pressed) {                                                                                       \
                if (wireless_get_current_devs() != wls_dev)                                                                    \
                    wireless_devs_change(wireless_get_current_devs(), wls_dev, false);                                         \
                if (wls_process_long_press_token == INVALID_DEFERRED_TOKEN) {                                                  \
                    wls_process_long_press_token = defer_exec(WLS_KEYCODE_PAIR_TIME, wls_process_long_press, &keycode_shadow); \
                }                                                                                                              \
            } else {                                                                                                           \
                cancel_deferred_exec(wls_process_long_press_token);                                                            \
                wls_process_long_press_token = INVALID_DEFERRED_TOKEN;                                                         \
            }                                                                                                                  \
        } while (false)

    switch (keycode) {
        case KC_BT1: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT1);
                hs_rgb_blink_set_timer(timer_read32());
            }

        } break;
        case KC_BT2: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT2);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        case KC_BT3: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT3);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        case KC_2G4: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_2g4) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_2G4);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        default:
            return true;
    }

    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (test_white_light_flag && record->event.pressed) {
        test_white_light_flag = false;
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
    }

    if (*md_getp_state() == MD_STATE_CONNECTED) {
        hs_rgb_blink_set_timer(timer_read32());
    }

    switch (keycode) {
        case MO(_FL):
        case MO(_MFL): {
           
            break;
        }
        case RGB_MOD:
            break;
        default: {
            
        } break;
    }

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (process_record_user(keycode, record) != true) {
        return false;
    }

#ifdef WIRELESS_ENABLE
    if (process_record_wls(keycode, record) != true) {
        return false;
    }
#endif
    switch (keycode) {
        case KC_TS: {
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_LGUI);
                unregister_code(KC_TAB);
            }
            return false;  
        } break;
        case KC_DESK: {
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_D);
            } else {
                unregister_code(KC_LGUI);
                unregister_code(KC_LSFT);
                unregister_code(KC_D);
            }
            return false;
        } break;
        case LEO_MOD: {
            if (!record->event.pressed) {
                confinfo.leo_mod_index = (confinfo.leo_mod_index + 1) % LEO_MOD_MAX;
                uint8_t mode = leo_modes[confinfo.leo_mod_index];

                if (mode == 0) {
                    rgblight_disable();
                }
                else {
                    rgblight_enable();
                }

                rgblight_mode(mode);
                eeconfig_confinfo_update(confinfo.raw);
            }
            return false;
        }
        case LEO_HUI: {
            if (!record->event.pressed) {
                confinfo.leo_hui_index = (confinfo.leo_hui_index + 1) % LEO_HUI_MAX;
                rgblight_sethsv(leo_hsvs[confinfo.leo_hui_index][0],
                                leo_hsvs[confinfo.leo_hui_index][1],
                                leo_hsvs[confinfo.leo_hui_index][2]);
                eeconfig_confinfo_update(confinfo.raw);
            }
            return false;
        }
        case QK_BOOT: {
            if (record->event.pressed) {
                dprintf("into boot!!!\r\n");
                eeconfig_disable();
                bootloader_jump();
            }
        } break;
        case KC_TEST: {
            
            if (record->event.pressed) {
                test_white_light_flag = true;
            }

            return false;
        } break;
        case NK_TOGG: {
           
            if (record->event.pressed) {
                rgb_matrix_hs_indicator_set(0xFF, (RGB){0x00, 0x6E, 0x00}, 250, 1);
            }
        } break;
        case EE_CLR: {
            if (record->event.pressed) {
                ee_clr_timer = timer_read32();
            } else {
                ee_clr_timer = 0;
            }

            return false;
        } break;
        case TO(_BL): {
            if (record->event.pressed) {
                rgb_matrix_hs_set_remain_time(HS_RGB_BLINK_INDEX_MAC, 0);
                rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_WIN, (RGB){RGB_WHITE}, 250, 3);
                if (keymap_is_mac_system()) {
                    set_single_persistent_default_layer(_BL);
                    layer_move(0);
                }
            }

            return false;
        } break;
        case TO(_MBL): {
            if (record->event.pressed) {
                rgb_matrix_hs_set_remain_time(HS_RGB_BLINK_INDEX_WIN, 0);
                rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_MAC, (RGB){RGB_WHITE}, 250, 3);
                if (!keymap_is_mac_system()) {
                    set_single_persistent_default_layer(_MBL);
                    layer_move(0);
                }
            }

            return false;
        } break;
        case RGB_MOD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_mode() == RGB_MATRIX_CUSTOM_RGBR_PLAY) {
                    if (confinfo.record_last_mode != 0xFF)
                        rgb_matrix_mode(confinfo.record_last_mode);
                    else
                        rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
                    eeconfig_confinfo_update(confinfo.raw);
                    dprintf("confinfo.record_last_mode = %d\r\n", confinfo.record_last_mode);
                    start_hsv = rgb_matrix_get_hsv();
                    return false;
                }
                record_rgbmatrix_increase(&(confinfo.record_last_mode));
                eeconfig_confinfo_update(confinfo.raw);
                start_hsv = rgb_matrix_get_hsv();
            }

            return false;
        } break;
        case RGB_HUI: {
            if (record->event.pressed) {
                record_color_hsv(true);
                start_hsv = rgb_matrix_get_hsv();
            }

            return false;
        } break;
        case KC_LCMD: {
            if (keymap_is_mac_system()) {
                if (keymap_config.no_gui && !rgbrec_is_started()) {
                    if (record->event.pressed) {
                        register_code16(KC_LCMD);
                    } else {
                        unregister_code16(KC_LCMD);
                    }
                }
            }

            return true;
        } break;
        case KC_RCMD: {
            if (keymap_is_mac_system()) {
                if (keymap_config.no_gui && !rgbrec_is_started()) {
                    if (record->event.pressed) {
                        register_code16(KC_RCMD);
                    } else {
                        unregister_code16(KC_RCMD);
                    }
                }
            }

            return true;
        } break;
        case RGB_SPI: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() >= (RGB_MATRIX_SPD_STEP * 5)) {
                    rgb_blink_dir();
                }
            }
        } break;
        case RGB_SPD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() <= RGB_MATRIX_SPD_STEP) {
                    rgb_blink_dir();
                    rgb_matrix_set_speed(RGB_MATRIX_SPD_STEP);

                    return false;
                }
            }
        } break;
        case RGB_VAI: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() >= (RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP)) {
                    rgb_blink_dir();
                    start_hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                } else {
                    start_hsv.v = rgb_matrix_get_val() + RGB_MATRIX_VAL_STEP;
                }
            }
        } break;
        case RGB_VAD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() <= RGB_MATRIX_VAL_STEP) {
                    rgb_blink_dir();
                    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT - RGBLED_NUM; i++) {
                        rgb_matrix_set_color(i, 0, 0, 0);
                    }
                    start_hsv.v = 0;
                } else {
                    start_hsv.v = rgb_matrix_get_val() - RGB_MATRIX_VAL_STEP;
                }
            }
        } break;

        default:
            break;
    }

    return true;
}

void rgb_blink_dir(void) {

    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_SPI, (RGB){0x20, 0x20, 0x20}, 250, 3);
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_SPD, (RGB){0x20, 0x20, 0x20}, 250, 3);
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_VAI, (RGB){0x20, 0x20, 0x20}, 250, 3);
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_VAD, (RGB){0x20, 0x20, 0x20}, 250, 3);
}

void housekeeping_task_user(void) {
    uint8_t hs_now_mode;
    static uint32_t hs_current_time;

    charging_state = readPin(HS_BAT_CABLE_PIN);

    bat_full_flag = readPin(BAT_FULL_PIN);

    if (charging_state && (bat_full_flag)) {
        hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING_DONE;
    } else if (charging_state) {
        hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING;
    } else {
        hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING_STOP;
    }

    if (!hs_current_time || timer_elapsed32(hs_current_time) > 1000) {

        hs_current_time = timer_read32();
        md_send_devctrl(hs_now_mode);
        md_send_devctrl(MD_SND_CMD_DEVCTRL_INQVOL);
    }
}

#ifdef RGB_MATRIX_ENABLE

#    ifdef WIRELESS_ENABLE
bool wls_rgb_indicator_reset        = false;
uint32_t wls_rgb_indicator_timer    = 0x00;
uint32_t wls_rgb_indicator_interval = 0;
uint32_t wls_rgb_indicator_times    = 0;
uint32_t wls_rgb_indicator_index    = 0;
RGB wls_rgb_indicator_rgb           = {0};

void rgb_matrix_wls_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {

    wls_rgb_indicator_timer = timer_read32();

    wls_rgb_indicator_index    = index;
    wls_rgb_indicator_interval = interval;
    wls_rgb_indicator_times    = times * 2;
    wls_rgb_indicator_rgb      = rgb;
}

void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset) {

    wls_rgb_indicator_reset = reset;

    if (confinfo.devs != wireless_get_current_devs()) {
        confinfo.devs = wireless_get_current_devs();
        if (confinfo.devs > 0 && confinfo.devs < 4) confinfo.last_btdevs = confinfo.devs;
        eeconfig_confinfo_update(confinfo.raw);
    }

    switch (new_devs) {
        case DEVS_BT1: {
            if (reset) {
                rgb_matrix_wls_indicator_set(64, (RGB){HS_LBACK_COLOR_BT1}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(64, (RGB){HS_PAIR_COLOR_BT1}, 500, 1);
            }
        } break;
        case DEVS_BT2: {
            if (reset) {
                rgb_matrix_wls_indicator_set(64, (RGB){HS_LBACK_COLOR_BT2}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(64, (RGB){HS_PAIR_COLOR_BT2}, 500, 1);
            }
        } break;
        case DEVS_BT3: {
            if (reset) {
                rgb_matrix_wls_indicator_set(64, (RGB){HS_LBACK_COLOR_BT3}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(64, (RGB){HS_PAIR_COLOR_BT3}, 500, 1);
            }
        } break;
        case DEVS_BT4: {
            if (reset) {
                rgb_matrix_wls_indicator_set(41, (RGB){RGB_BLUE}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(41, (RGB){RGB_BLUE}, 500, 1);
            }
        } break;
        case DEVS_BT5: {
            if (reset) {
                rgb_matrix_wls_indicator_set(42, (RGB){RGB_BLUE}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(42, (RGB){RGB_BLUE}, 500, 1);
            }
        } break;
        case DEVS_2G4: {
            if (reset) {
                rgb_matrix_wls_indicator_set(64, (RGB){HS_LBACK_COLOR_2G4}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(64, (RGB){HS_LBACK_COLOR_2G4}, 500, 1);
            }
        } break;
        default:
            break;
    }
}

bool rgb_matrix_wls_indicator_cb(void) {

    if (*md_getp_state() != MD_STATE_CONNECTED) {
        wireless_devs_change_kb(wireless_get_current_devs(), wireless_get_current_devs(), wls_rgb_indicator_reset);
        return true;
    }

    // refresh led
    led_wakeup();

    return false;
}

void rgb_matrix_wls_indicator(void) {

    if (wls_rgb_indicator_timer) {

        if (timer_elapsed32(wls_rgb_indicator_timer) >= wls_rgb_indicator_interval) {
            wls_rgb_indicator_timer = timer_read32();

            if (wls_rgb_indicator_times) {
                wls_rgb_indicator_times--;
            }

            if (wls_rgb_indicator_times <= 0) {
                wls_rgb_indicator_timer = 0x00;
                if (rgb_matrix_wls_indicator_cb() != true) {
                    return;
                }
            }
        }

        if (wls_rgb_indicator_times % 2) {
            rgb_matrix_set_color(wls_rgb_indicator_index, wls_rgb_indicator_rgb.r, wls_rgb_indicator_rgb.g, wls_rgb_indicator_rgb.b);
        } else {
            rgb_matrix_set_color(wls_rgb_indicator_index, 0x00, 0x00, 0x00);
        }
    }
}

void rgb_matrix_hs_bat_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {
    for (int i = 0; i < HS_RGB_BAT_COUNT; i++) {
        if (!hs_rgb_bat[i].active) {
            hs_rgb_bat[i].active   = true;
            hs_rgb_bat[i].timer    = timer_read32();
            hs_rgb_bat[i].interval = interval;
            hs_rgb_bat[i].times    = times * 2;
            hs_rgb_bat[i].index    = index;
            hs_rgb_bat[i].rgb      = rgb;
            break;
        }
    }
}

void rgb_matrix_hs_bat(void) {
    for (int i = 0; i < HS_RGB_BAT_COUNT; i++) {
        if (hs_rgb_bat[i].active) {
            if (timer_elapsed32(hs_rgb_bat[i].timer) >= hs_rgb_bat[i].interval) {
                hs_rgb_bat[i].timer = timer_read32();

                if (hs_rgb_bat[i].times) {
                    hs_rgb_bat[i].times--;
                }

                if (hs_rgb_bat[i].times <= 0) {
                    hs_rgb_bat[i].active = false;
                    hs_rgb_bat[i].timer  = 0x00;
                }
            }

            if (hs_rgb_bat[i].times % 2) {
                rgb_matrix_set_color(hs_rgb_bat[i].index, hs_rgb_bat[i].rgb.r, hs_rgb_bat[i].rgb.g, hs_rgb_bat[i].rgb.b);
            } else {
                rgb_matrix_set_color(hs_rgb_bat[i].index, 0x00, 0x00, 0x00);
            }
        }
    }
}

void bat_indicators(void) {
    static uint32_t battery_process_time = 0;

    if (charging_state && (bat_full_flag)) {
        rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, 0, 25, 0);
        battery_process_time = 0;
    } else if (charging_state) {

        battery_process_time = 0;
        rgb_matrix_hs_bat_set(HS_MATRIX_BLINK_INDEX_BAT, (RGB){0x00, 0xff, 0x00}, 250, 0xff);
    } else if (*md_getp_bat() <= BATTERY_CAPACITY_LOW) {

        rgb_matrix_hs_bat_set(HS_MATRIX_BLINK_INDEX_BAT, (RGB){0x00, 25, 0x00}, 250, 1);

        if (*md_getp_bat() <= BATTERY_CAPACITY_STOP) {
            if (!battery_process_time) {
                battery_process_time = timer_read32();
            }

            if (battery_process_time && timer_elapsed32(battery_process_time) > 60000) {
                battery_process_time = 0;
                lower_sleep          = true;
                lpwr_set_timeout_manual(true);
            }
        }
    } else {
        rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, 0, 0, 0);
        battery_process_time = 0;
    }
}

#    endif

#endif

bool hs_reset_settings_user(void) {

    rgb_matrix_hs_indicator_set(0xFF, (RGB){0x10, 0x10, 0x10}, 250, 3);

    return true;
}

void nkr_indicators_hook(uint8_t index) {

    if ((hs_rgb_indicators[index].rgb.r == 0x6E) && (hs_rgb_indicators[index].rgb.g == 0x00) && (hs_rgb_indicators[index].rgb.b == 0x00)) {

        rgb_matrix_hs_indicator_set(0xFF, (RGB){0x6E, 0x00, 0x00}, 250, 1);

    } else if ((hs_rgb_indicators[index].rgb.r == 0x00) && (hs_rgb_indicators[index].rgb.g == 0x6E) && (hs_rgb_indicators[index].rgb.b == 0x00)) {

        rgb_matrix_hs_indicator_set(0xFF, (RGB){0x00, 0x00, 0x6F}, 250, 1);
    }
}

void rgb_matrix_hs_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {

    for (int i = 0; i < HS_RGB_INDICATOR_COUNT; i++) {
        if (!hs_rgb_indicators[i].active) {
            hs_rgb_indicators[i].active   = true;
            hs_rgb_indicators[i].timer    = timer_read32();
            hs_rgb_indicators[i].interval = interval;
            hs_rgb_indicators[i].times    = times * 2;
            hs_rgb_indicators[i].index    = index;
            hs_rgb_indicators[i].rgb      = rgb;
            if (index != 0xFF)
                hs_rgb_indicators[i].blink_cb = NULL;
            else {
                hs_rgb_indicators[i].blink_cb = nkr_indicators_hook;
            }
            break;
        }
    }
}

void rgb_matrix_hs_set_remain_time(uint8_t index, uint8_t remain_time) {

    for (int i = 0; i < HS_RGB_INDICATOR_COUNT; i++) {
        if (hs_rgb_indicators[i].index == index) {
            hs_rgb_indicators[i].times  = 0;
            hs_rgb_indicators[i].active = false;
            break;
        }
    }
}

void rgb_matrix_hs_indicator(void) {

    for (int i = 0; i < HS_RGB_INDICATOR_COUNT; i++) {
        if (hs_rgb_indicators[i].active) {
            if (timer_elapsed32(hs_rgb_indicators[i].timer) >= hs_rgb_indicators[i].interval) {
                hs_rgb_indicators[i].timer = timer_read32();

                if (hs_rgb_indicators[i].times) {
                    hs_rgb_indicators[i].times--;
                }

                if (hs_rgb_indicators[i].times <= 0) {
                    hs_rgb_indicators[i].active = false;
                    hs_rgb_indicators[i].timer  = 0x00;
                    if (hs_rgb_indicators[i].blink_cb != NULL)
                        hs_rgb_indicators[i].blink_cb(i);
                    continue;
                }
            }

            if ((hs_rgb_indicators[i].times % 2)) {
                if (hs_rgb_indicators[i].index == 0xFF) {
                    rgb_matrix_set_color_all(hs_rgb_indicators[i].rgb.r, hs_rgb_indicators[i].rgb.g, hs_rgb_indicators[i].rgb.b);
                } else {
                    rgb_matrix_set_color(hs_rgb_indicators[i].index, hs_rgb_indicators[i].rgb.r, hs_rgb_indicators[i].rgb.g, hs_rgb_indicators[i].rgb.b);
                }
            } else {
                if (hs_rgb_indicators[i].index == 0xFF) {
                    rgb_matrix_set_color_all(0x00, 0x00, 0x00);
                } else {
                    rgb_matrix_set_color(hs_rgb_indicators[i].index, 0x00, 0x00, 0x00);
                }
            }
        }
    }
}


bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {

#ifdef RGBLIGHT_ENABLE
    if (rgb_matrix_indicators_advanced_user(led_min, led_max) != true) {

        return false;
    }
#endif

    if (ee_clr_timer && timer_elapsed32(ee_clr_timer) > 3000) {
        hs_reset_settings();
        ee_clr_timer = 0;
    }

    if (get_highest_layer(default_layer_state | layer_state) == 1) {
        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_WIN, RGB_WHITE);
    } else if (get_highest_layer(default_layer_state | layer_state) == 3) {
        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_MAC, RGB_WHITE);
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(51, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(15, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    }
    if (keymap_config.no_gui) {
        if (get_highest_layer(default_layer_state) == 0) {
            rgb_matrix_set_color(80, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
        } else if (get_highest_layer(default_layer_state) == 2) {
            rgb_matrix_set_color(81, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
        }
    }
        
#ifdef WIRELESS_ENABLE
    rgb_matrix_wls_indicator();

    if (enable_bat_indicators && !inqbat_flag && !rgbrec_is_started()) {
        rgb_matrix_hs_bat();
        bat_indicators();
        bat_indicator_cnt = timer_read32();
    }

    if (!enable_bat_indicators) {
        if (timer_elapsed32(bat_indicator_cnt) > 2000) {
            enable_bat_indicators = true;
            bat_indicator_cnt     = timer_read32();
        }
    }

#endif

    rgb_matrix_hs_indicator();

    query();
    return true;
}

void hs_reset_settings(void) {
    enable_bat_indicators = false;
    eeconfig_init();
    eeconfig_update_rgb_matrix_default();


    keymap_config.raw = eeconfig_read_keymap();

#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 0;
    eeconfig_update_keymap(keymap_config.raw);
#endif

    // #if defined(WIRELESS_ENABLE)
    //     wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
    // #endif

    if (hs_reset_settings_user() != true) {

        return;
    }
    hs_rgb_blink_set_timer(timer_read32());
    keyboard_post_init_kb();
}

void lpwr_wakeup_hook(void) {
    hs_mode_scan(false, confinfo.devs, confinfo.last_btdevs);

    gpio_write_pin_high(LED_POWER_EN_PIN);
    gpio_write_pin_high(A9);
}
