BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
OLED_ENABLE = no
RGBLIGHT_ENABLE = no

EXTRAFLAGS += -flto

SRC += jis2us.c \
    gui2alt.c \
    dvorak.c
