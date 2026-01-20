/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_Z,  	 KC_X
	),

	[1] = LAYOUT(
		KC_TRNS, KC_TRNS
	),

	[2] = LAYOUT(
		KC_TRNS, KC_TRNS
	),

	[3] = LAYOUT(
		KC_TRNS, KC_TRNS
	),

};

// caps lock = white
const rgblight_segment_t PROGMEM user_capslock_led[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 0, 0, 128} // starting at 1st LED, affecting 1 LEDs in the chain, makes it a bright white
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM user_capslock_indicator[] = RGBLIGHT_LAYERS_LIST(
    user_capslock_led
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = user_capslock_indicator;
}

/* make the leds do something */
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
