RGB_MATRIX_CUSTOM_USER = yes
RGBLIGHT_DRIVER        = custom
KEYBOARD_NAME          = jiebao/z87
include keyboards/$(KEYBOARD_NAME)/rgb_record/rgb_record.mk
include keyboards/$(KEYBOARD_NAME)/control/control.mk
include keyboards/linker/wireless/wireless.mk
