#include "gui2alt.h"

bool input_gui2alt(uint16_t keycode, bool pressed) {
    // winキーの動作変更
    static uint16_t pressed_gui_keycode = XXXXXXX;
    static bool pressed_gui = false;

    switch (keycode) {
        case KC_LGUI:
        case KC_RGUI:
            if (pressed) {
                pressed_gui_keycode = keycode;
            } else {
                if (pressed_gui) {
                    unregister_code(pressed_gui_keycode);
                } else {
                    tap_code(pressed_gui_keycode);
                }
                pressed_gui_keycode = XXXXXXX;
                pressed_gui = false;
            }
            return false;
        case KC_TAB: // alt + tab (windows)
        case KC_ENTER: // alt + enter (excel セル内で改行)
            if (pressed_gui_keycode != XXXXXXX && !pressed_gui && pressed) {
                // Alt
                pressed_gui_keycode = pressed_gui_keycode == KC_LGUI ? KC_LALT : KC_RALT;
            }
            // break;
        default:
            if (pressed_gui_keycode != XXXXXXX && !pressed_gui && pressed) {
                pressed_gui = true;
                register_code(pressed_gui_keycode);
            }
            break;
    }
    return true;
}
