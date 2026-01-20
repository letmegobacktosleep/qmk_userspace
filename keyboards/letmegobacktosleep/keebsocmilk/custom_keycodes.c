#include "quantum.h"

// Create a custom keycode enum
enum custom_keycodes {
  AT_T = QK_KB_0,
  AT_R,
};

// Variables to track whether alt tab is active
bool alt_tab_active = false;
bool alt_tab_repeat = false;
uint16_t alt_tab_next_tab = 0;
uint16_t alt_tab_timeout = 0;

// Handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case AT_T:
        if (record->event.pressed) {
            // hold alt
            if (!alt_tab_active) {
                register_code(KC_LALT);
                alt_tab_active = true;
            }
            // tap tab
            tap_code(KC_TAB);
            // wait for timeout
            alt_tab_timeout = timer_read();
        }
        break;
    case AT_R:
        if (record->event.pressed) {
            // hold alt
            if (!alt_tab_repeat) {
                register_code(KC_LALT);
                alt_tab_active = true;
                alt_tab_repeat = true;
            }
        }
        else {
            // stop tab repeat
            alt_tab_repeat = false;
        }
        break;
  }
  return true;
}

// Handle repeat and timeout
void matrix_scan_user(void) {
    if (alt_tab_active) {
        if (alt_tab_repeat) {
            if (timer_elapsed(alt_tab_next_tab) > 250) {
                // tap tab every 250ms
                tap_code(KC_TAB);
                alt_tab_next_tab = timer_read();
            }
        }
        else if (timer_elapsed(alt_tab_timeout) > 500) {
            // release alt after 500ms
            unregister_code(KC_LALT);
            alt_tab_active = false;
        }
    }
}
