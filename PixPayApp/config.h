/**
 * PixPayApp Configuration Template
 * Modify these settings for your specific hardware setup
 */

#ifndef CONFIG_H
#define CONFIG_H

// ================= DISPLAY CONFIGURATION =================
// 7-inch RGB Display Settings
#define DISPLAY_WIDTH  800
#define DISPLAY_HEIGHT 480
#define DISPLAY_BL_PIN 2

// RGB Display Timing (adjust for your specific panel)
#define HSYNC_FRONT_PORCH 210
#define HSYNC_PULSE_WIDTH 30
#define HSYNC_BACK_PORCH  16
#define VSYNC_FRONT_PORCH 22
#define VSYNC_PULSE_WIDTH 13
#define VSYNC_BACK_PORCH  10
#define PIXEL_CLOCK_FREQ  16000000

// ================= TOUCH CONFIGURATION =================
// GT911 Touch Controller Settings
#define TOUCH_SDA_PIN    19
#define TOUCH_SCL_PIN    20
#define TOUCH_INT_PIN    18
#define TOUCH_RST_PIN    38
#define TOUCH_I2C_ADDR   0x5D

// ================= WIFI CONFIGURATION =================
// WiFiManager Settings
#define WIFI_AP_NAME     "PixPayAP"
#define WIFI_AP_PASSWORD "pix12345"
#define WIFI_TIMEOUT     300  // 5 minutes
#define WIFI_RETRY_DELAY 5000 // 5 seconds

// ================= PAYMENT CONFIGURATION =================
// PIX Payment Settings
#define DEFAULT_PAYMENT_VALUE "R$ 2,00"
#define PAYMENT_TIMEOUT_MS    60000  // 60 seconds
#define QR_CODE_VERSION       3      // QR complexity level

// Payment Values (customize as needed)
#define PAYMENT_VALUE_1 "R$ 2,00"
#define PAYMENT_VALUE_2 "R$ 5,00"
#define PAYMENT_VALUE_3 "R$ 10,00"

// ================= UI CONFIGURATION =================
// LVGL Memory Settings
#define LVGL_BUFFER_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT / 4)
#define LVGL_REFRESH_PERIOD 20  // ms

// Screen Transition Settings
#define SCREEN_FADE_TIME 300    // ms
#define BUTTON_PRESS_FEEDBACK true

// ================= DEBUG CONFIGURATION =================
// Debug Output Settings
#define DEBUG_SERIAL_ENABLE true
#define DEBUG_WIFI_ENABLE   true
#define DEBUG_TOUCH_ENABLE  false
#define DEBUG_LVGL_ENABLE   false

// Serial Settings
#define SERIAL_BAUD_RATE 115200

// ================= HARDWARE PINS =================
// ESP32-S3 RGB Display Pin Mapping
#define PIN_DE     41
#define PIN_VSYNC  40
#define PIN_HSYNC  39
#define PIN_PCLK   42

// Red Channel Pins
#define PIN_R0     14
#define PIN_R1     21
#define PIN_R2     47
#define PIN_R3     48
#define PIN_R4     45

// Green Channel Pins
#define PIN_G0     9
#define PIN_G1     46
#define PIN_G2     3
#define PIN_G3     8
#define PIN_G4     16
#define PIN_G5     1

// Blue Channel Pins
#define PIN_B0     15
#define PIN_B1     7
#define PIN_B2     6
#define PIN_B3     5
#define PIN_B4     4

// ================= COLOR SCHEME =================
// UI Color Definitions (RGB565)
#define COLOR_PRIMARY     0x007BFF  // Blue
#define COLOR_SECONDARY   0x6C757D  // Gray
#define COLOR_SUCCESS     0x28A745  // Green
#define COLOR_DANGER      0xDC3545  // Red
#define COLOR_WARNING     0xFFC107  // Yellow
#define COLOR_INFO        0x17A2B8  // Cyan
#define COLOR_LIGHT       0xF8F9FA  // Light Gray
#define COLOR_DARK        0x343A40  // Dark Gray
#define COLOR_WHITE       0xFFFFFF  // White
#define COLOR_BLACK       0x000000  // Black

// ================= FONT SETTINGS =================
// LVGL Font Sizes
#define FONT_TITLE   &lv_font_montserrat_24
#define FONT_HEADING &lv_font_montserrat_20
#define FONT_BODY    &lv_font_montserrat_16
#define FONT_SMALL   &lv_font_montserrat_14
#define FONT_LARGE   &lv_font_montserrat_30

#endif // CONFIG_H