/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <stdlib.h>
#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE
// #if defined(RGB_MATRIX_EMABLE) && defined(DYNAMIC_KEYMAP_LAYER_COUNT)
#pragma message "Compiling rgb.c"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max){

    // get the current brightness value
    uint8_t val = rgb_matrix_get_val();

    // set the caps, num, scroll indicators (not implemented: compose, kana)
# if defined(DISCRETE_CAPS) || defined(DISCRETE_NUML) || defined(DISCRETE_SCRL)
    // get the current led state
    led_t led_state = host_keyboard_led_state();
#  ifdef DISCRETE_CAPS
#  pragma message "Compiling Caps Lock indicator"
    if (led_state.caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_CAPS, val, val, val);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_CAPS, 0, 0, 0);
    }
#  endif
#  ifdef DISCRETE_NUML
#  pragma message "Compiling Number Lock indicator"
    if (led_state.num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_NUML, val, val, val);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_NUML, 0, 0, 0);
    }
#  endif
#  ifdef DISCRETE_SCRL
#  pragma message "Compiling Scroll Lock indicator"
    if (led_state.scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_SCRL, val, val, val);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_SCRL, 0, 0, 0);
    }
#  endif
# endif

# if defined(LAYER_INDICATOR_MIN) && defined(LAYER_INDICATOR_MAX)
# pragma message "Compiling Layer indicators"
    int8_t  diff = (int8_t)LAYER_INDICATOR_MAX - (int8_t)LAYER_INDICATOR_MIN;
    uint8_t distance = abs(diff);
# endif // defined(LAYER_INDICATOR_MIN) && defined(LAYER_INDICATOR_MAX)

    for (uint8_t layer = 1; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++){

#     if defined(LAYER_INDICATOR_MIN) && defined(LAYER_INDICATOR_MAX)
        uint8_t offset = MIN(layer - 1, distance);
        int8_t  u_layer_led_index = (int8_t)LAYER_INDICATOR_MIN + (offset * (diff >= 0 ? 1 : -1));
        uint8_t layer_led_index = (uint8_t)u_layer_led_index;
#     endif // defined(LAYER_INDICATOR_MIN) && defined(LAYER_INDICATOR_MAX)

        // check if layer is active
        if (layer_state_is(layer)){

            // set discrete layer indicator LEDs
#         if defined(LAYER_INDICATOR_MIN) && defined(LAYER_INDICATOR_MAX)
            RGB_MATRIX_INDICATOR_SET_COLOR(
                layer_led_index,
                val, val, val // set to white
            );
#         endif // defined(LAYER_INDICATOR_MIN) && defined(LAYER_INDICATOR_MAX)

#         ifdef ENABLE_PER_KEY_LAYER_INDICATOR
#         pragma message "Compiling Per-Key Layer indicators"
            // set HSV
            hsv_t hsv = (hsv_t){
                // rainbow
                255 * layer / DYNAMIC_KEYMAP_LAYER_COUNT, 
                128, 
                val
            };

            // convert to RGB
            rgb_t rgb = hsv_to_rgb(hsv);

            // set per-key layer indicators
            for (uint8_t row = 0; row < MATRIX_ROWS; row++){
                for (uint8_t col = 0; col < MATRIX_COLS; col++){

                    // get LED index from row and column
                    uint8_t index = g_led_config.matrix_co[row][col];

                    // check if LED can be set & if keycode isn't transparent
                    if (
                        index >= led_min && 
                        index < led_max && 
                        index != NO_LED &&
                        keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS
                    )
                    {
                        // set colour
                        rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                    }
                }
            }
#         endif // ENABLE_PER_KEY_LAYER_INDICATOR
        }

#     if defined(LAYER_INDICATOR_MIN) && defined(LAYER_INDICATOR_MAX)
        else {
            // clear discrete layer indicator LEDs
            RGB_MATRIX_INDICATOR_SET_COLOR(
                layer_led_index,
                0, 0, 0 // set to none
            );
        }
#     endif // defined(LAYER_INDICATOR_MIN) && defined(LAYER_INDICATOR_MAX)
    }
    return false;
}

#else

#pragma message "RGB_MATRIX is not enabled"

#endif // RGB_MATRIX_ENABLE