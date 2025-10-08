#include <WiFi.h>
#include <WiFiManager.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include <Wire.h>
#include <TAMC_GT911.h>      // touch GT911 (lib: TAMC_GT911)
#include "ui.h"              // SquareLine Studio generated UI

// ================= DISPLAY CONFIG =================
#define TFT_BL 2

// BUS RGB do ESP32-S3 — Arduino_GFX 1.3.6 (core 2.0.14)
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
  /*de*/    41,
  /*vsync*/ 40,
  /*hsync*/ 39,
  /*pclk*/  42,

  /*r0*/ 14, /*r1*/ 21, /*r2*/ 47, /*r3*/ 48, /*r4*/ 45,
  /*g0*/  9, /*g1*/ 46, /*g2*/  3, /*g3*/  8, /*g4*/ 16, /*g5*/ 1,
  /*b0*/ 15, /*b1*/  7, /*b2*/  6, /*b3*/  5, /*b4*/ 4,

  /*hs_polarity*/    0,
  /*hs_front_porch*/ 210,
  /*hs_pulse_width*/ 30,
  /*hs_back_porch*/  16,

  /*vs_polarity*/    0,
  /*vs_front_porch*/ 22,
  /*vs_pulse_width*/ 13,
  /*vs_back_porch*/  10,

  /*extra_polarity*/ 0,        // parâmetro #9 de timing (de_idle/pclk_idle); deixe 0

  /*prefer_speed*/   16000000, // int32_t
  /*pclk_active_neg*/ true,    // bool
  /*panelWidth*/     800,      // uint16_t
  /*panelHeight*/    480       // uint16_t
);

// Display (em 1.3.6 já existe)
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(800, 480, bus);

// ================= TOUCH (GT911) =================
#define TOUCH_GT911_SDA  19
#define TOUCH_GT911_SCL  20
#define TOUCH_GT911_INT  18
#define TOUCH_GT911_RST  38
#define TOUCH_GT911_ADDR 0x5D

TAMC_GT911 ts(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, 800, 480);

// ================= LVGL CONFIG =================
static const uint32_t screenWidth = 800;
static const uint32_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

// ================= APP STATE =================
enum AppScreen {
  SCREEN_WIFI_CONNECT = 0,
  SCREEN_PAYMENT_METHOD,
  SCREEN_SELECT_VALUE,
  SCREEN_PAYMENT_PIX,
  SCREEN_OPERATION_COMPLETE,
  SCREEN_NO_CONNECTION
};

AppScreen currentScreen = SCREEN_WIFI_CONNECT;
bool wifiConnected = false;
String selectedValue = "R$ 2,00";
unsigned long paymentStartTime = 0;
const unsigned long PAYMENT_TIMEOUT = 60000; // 60s

WiFiManager wifiManager;

// Forwards
void showNoConnectionScreen();
void generatePixPayment();
void updatePaymentTimer();
void showPaymentMethodScreen();
void showWiFiConnectScreen();

// ================= LVGL flush =================
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif
  lv_disp_flush_ready(disp);
}

// ================= TOUCH handlers =================
int16_t touch_last_x = 0, touch_last_y = 0;
bool touch_has_signal() { return true; }

bool touch_touched() {
  ts.read();
  if (ts.isTouched) {
    // mapeia para 800x480
    touch_last_x = map(ts.points[0].x, 800, 0, 0, 799);
    touch_last_y = map(ts.points[0].y, 480, 0, 0, 479);
    return true;
  }
  return false;
}
bool touch_released() { return !ts.isTouched; }

void my_touchpad_read(lv_indev_drv_t *indev, lv_indev_data_t *data) {
  if (touch_touched()) {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = touch_last_x;
    data->point.y = touch_last_y;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

// ================= WiFiManager callbacks =================
void configModeCallback(WiFiManager *wm) {
  Serial.println("Entered WiFi Config Mode");
  Serial.print("Config AP: "); Serial.println(wm->getConfigPortalSSID());
  Serial.print("IP Address: "); Serial.println(WiFi.softAPIP());
  lv_label_set_text(ui_wifi_status_label, "Conecte ao PixPayAP\npara configurar WiFi");
}

void saveConfigCallback() {
  Serial.println("WiFi Configuration Saved and Connected!");
  wifiConnected = true;
  Serial.print("Connected to: "); Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");  Serial.println(WiFi.localIP());
  lv_label_set_text(ui_wifi_status_label, "WiFi Conectado!\nRedirecionando...");
  delay(2000);
  lv_disp_load_scr(ui_Screen_Payment);
  currentScreen = SCREEN_PAYMENT_METHOD;
}

void setupWiFiManager() {
  Serial.println("Starting WiFi Manager...");
  lv_label_set_text(ui_wifi_status_label, "Iniciando configuração WiFi...\nAguarde...");
  lv_timer_handler(); // (LVGL 8.x)

  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.setConfigPortalTimeout(300);

  if (!wifiManager.autoConnect("PixPayAP", "pix12345")) {
    Serial.println("Failed to connect - showing no connection screen");
    showNoConnectionScreen();
    return;
  }

  Serial.println("WiFi Connected Successfully!");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  wifiConnected = true;
  lv_disp_load_scr(ui_Screen_Payment);
  currentScreen = SCREEN_PAYMENT_METHOD;
}

// ================= Navegação de telas =================
void showWiFiConnectScreen() {
  Serial.println("Showing WiFi Connect Screen");
  lv_disp_load_scr(ui_Screen_WiFi);
  currentScreen = SCREEN_WIFI_CONNECT;

  lv_label_set_text(ui_wifi_title_label, "Conecte seu equipamento à internet");
  if (WiFi.status() == WL_CONNECTED) {
    lv_label_set_text(ui_wifi_status_label, "WiFi Conectado!\nToque para continuar");
    lv_obj_add_state(ui_connect_btn, LV_STATE_CHECKED);
  } else {
    lv_label_set_text(ui_wifi_status_label, "Configure sua rede WiFi\nToque em CONECTAR para começar");
    lv_obj_clear_state(ui_connect_btn, LV_STATE_CHECKED);
  }
}

void showPaymentMethodScreen() {
  Serial.println("Showing Payment Method Screen");
  lv_disp_load_scr(ui_Screen_Payment);
  currentScreen = SCREEN_PAYMENT_METHOD;
  lv_obj_add_state(ui_pix_btn, LV_STATE_CHECKED);
}

void showSelectValueScreen() {
  Serial.println("Showing Select Value Screen");
  lv_disp_load_scr(ui_Screen_Value);
  currentScreen = SCREEN_SELECT_VALUE;
  lv_label_set_text(ui_value_label, selectedValue.c_str());
}

void showPaymentPixScreen() {
  Serial.println("Showing PIX Payment Screen");
  lv_disp_load_scr(ui_Screen_PIX);
  currentScreen = SCREEN_PAYMENT_PIX;
  generatePixPayment();
  paymentStartTime = millis();
  updatePaymentTimer();
}

void showOperationCompleteScreen() {
  Serial.println("Showing Operation Complete Screen");
  lv_disp_load_scr(ui_Screen_Complete);
  currentScreen = SCREEN_OPERATION_COMPLETE;
  String successMsg = "Pagamento realizado\n" + selectedValue;
  lv_label_set_text(ui_success_label, successMsg.c_str());
}

void showNoConnectionScreen() {
  Serial.println("Showing No Connection Screen");
  lv_disp_load_scr(ui_Screen_NoConnection);
  currentScreen = SCREEN_NO_CONNECTION;
}

// ================= PIX simulado =================
void generatePixPayment() {
  String pixData = "PIX:" + selectedValue + ":Lucas-PixPayApp";
  Serial.println("PIX Payment Generated!");
  Serial.println("Amount: " + selectedValue);
  Serial.println("Merchant: Lucas PixPayApp");
  Serial.println("Status: Waiting for payment...");
  paymentStartTime = millis();
}

void updatePaymentTimer() {
  if (currentScreen != SCREEN_PAYMENT_PIX) return;
  unsigned long elapsed = millis() - paymentStartTime;
  unsigned long remaining = PAYMENT_TIMEOUT - elapsed;
  if (remaining <= 0) { showWiFiConnectScreen(); return; }

  int seconds = remaining / 1000;
  int minutes = seconds / 60;
  seconds %= 60;

  char timerText[10];
  sprintf(timerText, "%02d:%02d", minutes, seconds);
  lv_label_set_text(ui_timer_label, timerText);
}

// ================= Handlers (SquareLine) =================
void onWiFiConnectClick(lv_event_t * e) {
  Serial.println("WiFi Connect Button Clicked");
  if (wifiConnected && WiFi.status() == WL_CONNECTED) showPaymentMethodScreen();
  else setupWiFiManager();
}

void onPaymentMethodClick(lv_event_t * e) {
  Serial.println("Payment Method (PIX) Selected");
  showSelectValueScreen();
}

void onValueSelectClick(lv_event_t * e) {
  Serial.println(String("Value Selected: ") + selectedValue);
  showPaymentPixScreen();
}

void onPaymentCompleteClick(lv_event_t * e) {
  Serial.println("Payment Completed");
  showOperationCompleteScreen();
}

void onRetryConnectionClick(lv_event_t * e) {
  Serial.println("Retry Connection Clicked");
  setupWiFiManager();
}

void onCancelPaymentClick(lv_event_t * e) {
  Serial.println("Payment Cancelled");
  showWiFiConnectScreen();
}

void onBackToStartClick(lv_event_t * e) {
  Serial.println("Back to Start");
  showWiFiConnectScreen();
}

// ================= Init TOUCH =================
void initTouch() {
  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  ts.begin();
  // (não usar ts.setRotation com TAMC_GT911)
  Serial.println("GT911 touch controller initialized");
  Serial.printf("Touch resolution: %dx%d\n", 800, 480);
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  Serial.println("=================================");
  Serial.println("PixPayApp Starting...");
  Serial.println("ESP32-S3 7-inch Display");
  Serial.println("=================================");

  // Display
  Serial.println("Initializing display...");
  gfx->begin();
  gfx->fillScreen(BLACK);

#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
    // API nova (core 3.x)
    ledcAttach(TFT_BL, 300, 8);
    ledcWrite(TFT_BL, 255);
  #else
    // API antiga (core 2.x)
    ledcSetup(0, 300, 8);
    ledcAttachPin(TFT_BL, 0);
    ledcWrite(0, 255);
  #endif
#endif

  // Splash
  gfx->fillScreen(RED);   delay(200);
  gfx->fillScreen(GREEN); delay(200);
  gfx->fillScreen(BLUE);  delay(200);
  gfx->fillScreen(BLACK);

  // LVGL
  Serial.println("Initializing LVGL...");
  lv_init();

#ifdef ESP32
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(
    sizeof(lv_color_t) * screenWidth * screenHeight / 4,
    MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT
  );
#else
  disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4);
#endif

  if (!disp_draw_buf) {
    Serial.println("LVGL display buffer allocation failed!");
    while (1) delay(1000);
  }

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 4);
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Touch
  Serial.println("Initializing touch...");
  initTouch();

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // UI
  Serial.println("Initializing UI...");
  ui_init(); // carrega tela WiFi por padrão

  // WiFi smart flow
  Serial.println("Checking WiFi status...");
  WiFi.mode(WIFI_STA);
  WiFi.begin();

  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < 20) {
    delay(500); wifiAttempts++; Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi already connected!");
    Serial.print("IP Address: "); Serial.println(WiFi.localIP());
    wifiConnected = true;
    lv_disp_load_scr(ui_Screen_Payment);
    currentScreen = SCREEN_PAYMENT_METHOD;
  } else {
    Serial.println("WiFi not connected - staying on WiFi setup screen");
    currentScreen = SCREEN_WIFI_CONNECT;
    lv_label_set_text(ui_wifi_title_label, "Configure sua conexão WiFi");
    lv_label_set_text(ui_wifi_status_label, "Toque em CONECTAR para\nconfigurar sua rede WiFi");
  }

  Serial.println("Setup completed successfully!");
  Serial.println("=================================");
}

// ================= LOOP =================
void loop() {
  lv_timer_handler(); // LVGL 8.x

  if (currentScreen == SCREEN_PAYMENT_PIX) {
    updatePaymentTimer();
  }

  static unsigned long lastWiFiCheck = 0;
  if (millis() - lastWiFiCheck > 5000) {
    lastWiFiCheck = millis();
    if (wifiConnected && WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi connection lost");
      wifiConnected = false;
      if (currentScreen != SCREEN_WIFI_CONNECT && currentScreen != SCREEN_NO_CONNECTION) {
        showNoConnectionScreen();
      }
    }
  }
  delay(5);
}
