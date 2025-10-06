#pragma message "Compiling rgb.c"

#ifdef RGB_MATRIX_ENABLE

#define DISCRETE_CAPS 3
#define DISCRETE_NUML 4
#define DISCRETE_SCRL 5
#define LAYER_INDICATOR_MIN 2
#define LAYER_INDICATOR_MAX 0

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max){

    // get the current brightness value
    uint8_t val = rgb_matrix_get_val();
    // get the current led state
    led_t led_state = host_keyboard_led_state();

    // set the caps, num, scroll indicators (not implemented: compose, kana)
    if (led_state.caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_CAPS, val, val, val);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_CAPS, 0, 0, 0);
    }
    if (led_state.num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_NUML, val, val, val);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_NUML, 0, 0, 0);
    }
    if (led_state.scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_SCRL, val, val, val);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(DISCRETE_SCRL, 0, 0, 0);
    }

    for (uint8_t layer = 1; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++){
        // check if layer is active
        if (layer_state_is(layer)){

            // set discrete layer indicator LEDs
#         if (LAYER_INDICATOR_MIN <= LAYER_INDICATOR_MAX)
            RGB_MATRIX_INDICATOR_SET_COLOR(
                MIN((LAYER_INDICATOR_MIN + layer - 1), (LAYER_INDICATOR_MAX)),
                val, val, val // set to white
            );
#         else
            RGB_MATRIX_INDICATOR_SET_COLOR(
                MIN((LAYER_INDICATOR_MAX + layer - 1), (LAYER_INDICATOR_MIN)),
                val, val, val // set to white
            );
#         endif
#         ifdef DYNAMIC_KEYMAP_LAYER_COUNT
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
#         endif // DYNAMIC_KEYMAP_LAYER_COUNT
        }
    }
    return false;
}

#else

#pragma message "RGB_MATRIX is not enabled"

#endif // RGB_MATRIX_ENABLE