#pragma once

/* Change emulated EEPROM size for RP2040 */
#define WEAR_LEVELING_RP2040_FLASH_SIZE (2*1024*1024)
#define WEAR_LEVELING_RP2040_FLASH_BASE ((2*1024*1024)-(128*1024))
#define WEAR_LEVELING_LOGICAL_SIZE (64*1024)
#define WEAR_LEVELING_BACKING_SIZE (128*1024)
#define BACKING_STORE_WRITE_SIZE 2

/* Declare the data pins for the mouse sensor */
#define SPI_SCK_PIN GP18
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP19
#define PMW33XX_CS_PIN GP21

/* Optional: Set sensor CPI, default 1600 */
/* #define PMW33XX_CPI 12000 */

/* Configure pointing device */
#define POINTING_DEVICE_INVERT_Y
#define POINTING_DEVICE_MOTION_PIN GP23
#define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW

/* Optional: Auto-Mouse Layer */
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 7 /* last layer */