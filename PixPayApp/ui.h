/**
 * SquareLine Studio Generated UI Header
 * PixPayApp - Pix Payment System UI
 * 
 * This file should be replaced with the actual SquareLine Studio generated ui.h
 * Current version: Template/Placeholder for development
 */

#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// ================= SCREEN DECLARATIONS =================
extern lv_obj_t * ui_Screen_WiFi;
extern lv_obj_t * ui_Screen_Payment;
extern lv_obj_t * ui_Screen_Value;
extern lv_obj_t * ui_Screen_PIX;
extern lv_obj_t * ui_Screen_Complete;
extern lv_obj_t * ui_Screen_NoConnection;

// ================= UI COMPONENT DECLARATIONS =================
// WiFi Connect Screen Components
extern lv_obj_t * ui_wifi_title_label;
extern lv_obj_t * ui_wifi_status_label;
extern lv_obj_t * ui_connect_btn;
extern lv_obj_t * ui_wifi_icon;

// Payment Method Screen Components
extern lv_obj_t * ui_payment_title_label;
extern lv_obj_t * ui_pix_btn;
extern lv_obj_t * ui_card_btn;
extern lv_obj_t * ui_money_btn;

// Select Value Screen Components
extern lv_obj_t * ui_value_title_label;
extern lv_obj_t * ui_value_label;
extern lv_obj_t * ui_value_2_btn;
extern lv_obj_t * ui_value_5_btn;
extern lv_obj_t * ui_value_10_btn;
extern lv_obj_t * ui_confirm_value_btn;

// PIX Payment Screen Components
extern lv_obj_t * ui_pix_title_label;
extern lv_obj_t * ui_pix_amount_label;
extern lv_obj_t * ui_qr_code_canvas;
extern lv_obj_t * ui_timer_label;
extern lv_obj_t * ui_cancel_btn;

// Operation Complete Screen Components
extern lv_obj_t * ui_success_label;
extern lv_obj_t * ui_success_icon;
extern lv_obj_t * ui_back_to_start_btn;

// No Connection Screen Components
extern lv_obj_t * ui_no_conn_title_label;
extern lv_obj_t * ui_no_conn_desc_label;
extern lv_obj_t * ui_retry_btn;

// ================= EVENT HANDLERS =================
void onWiFiConnectClick(lv_event_t * e);
void onPaymentMethodClick(lv_event_t * e);
void onValueSelectClick(lv_event_t * e);
void onPaymentCompleteClick(lv_event_t * e);
void onRetryConnectionClick(lv_event_t * e);
void onCancelPaymentClick(lv_event_t * e);
void onBackToStartClick(lv_event_t * e);

// ================= UI INITIALIZATION =================
void ui_init(void);

// ================= SCREEN CREATION FUNCTIONS =================
void ui_Screen_WiFi_screen_init(void);
void ui_Screen_Payment_screen_init(void);
void ui_Screen_Value_screen_init(void);
void ui_Screen_PIX_screen_init(void);
void ui_Screen_Complete_screen_init(void);
void ui_Screen_NoConnection_screen_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif // UI_H