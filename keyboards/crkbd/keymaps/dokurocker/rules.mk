BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
OLED_ENABLE = yes
#CONSOLE_ENABLE = yes

EXTRAFLAGS += -flto

SRC += jis2us.c \
    gui2alt.c \
    dvorak.c
