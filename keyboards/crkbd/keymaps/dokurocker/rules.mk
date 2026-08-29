BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
OLED_ENABLE = yes
#RGBLIGHT_ENABLE = yes
#CONSOLE_ENABLE = yes

EXTRAFLAGS += -flto

#SRC += jis2us.c \
    gui2alt.c \
    dvorakjp/dvorakjp.c \
    dvorak.c
SRC += jis2us.c \
    dvorakjp/dvorakjp.c \
    dvorak.c
