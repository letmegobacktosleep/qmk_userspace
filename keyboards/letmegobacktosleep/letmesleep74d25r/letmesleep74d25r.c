/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <stdbool.h>
#include "quantum.h"

void keyboard_pre_init_user(void) {
    // Trigger a hardware reset for the mouse sensor
    gpio_set_pin_output(GP22);
    gpio_write_pin_high(GP22);
    wait_ms(1); // Wait at least 100ns
    gpio_write_pin_low(GP22);
    gpio_set_pin_input(GP22);
}

void pointing_device_init_user(void) {
    // Enable auto-mouse layer
    set_auto_mouse_enable(true);
}
