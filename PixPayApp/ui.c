/**
 * SquareLine Studio Generated UI Implementation
 * PixPayApp - Pix Payment System UI Implementation
 * 
 * This file should be replaced with the actual SquareLine Studio generated ui.c
 * Current version: Template/Placeholder for development
 */

#include "ui.h"

// ================= SCREEN OBJECTS =================
lv_obj_t * ui_Screen_WiFi;
lv_obj_t * ui_Screen_Payment;
lv_obj_t * ui_Screen_Value;
lv_obj_t * ui_Screen_PIX;
lv_obj_t * ui_Screen_Complete;
lv_obj_t * ui_Screen_NoConnection;

// ================= UI COMPONENT OBJECTS =================
// WiFi Connect Screen Components
lv_obj_t * ui_wifi_title_label;
lv_obj_t * ui_wifi_status_label;
lv_obj_t * ui_connect_btn;
lv_obj_t * ui_wifi_icon;

// Payment Method Screen Components
lv_obj_t * ui_payment_title_label;
lv_obj_t * ui_pix_btn;
lv_obj_t * ui_card_btn;
lv_obj_t * ui_money_btn;

// Select Value Screen Components
lv_obj_t * ui_value_title_label;
lv_obj_t * ui_value_label;
lv_obj_t * ui_value_2_btn;
lv_obj_t * ui_value_5_btn;
lv_obj_t * ui_value_10_btn;
lv_obj_t * ui_confirm_value_btn;

// PIX Payment Screen Components
lv_obj_t * ui_pix_title_label;
lv_obj_t * ui_pix_amount_label;
lv_obj_t * ui_qr_code_canvas;
lv_obj_t * ui_timer_label;
lv_obj_t * ui_cancel_btn;

// Operation Complete Screen Components
lv_obj_t * ui_success_label;
lv_obj_t * ui_success_icon;
lv_obj_t * ui_back_to_start_btn;

// No Connection Screen Components
lv_obj_t * ui_no_conn_title_label;
lv_obj_t * ui_no_conn_desc_label;
lv_obj_t * ui_retry_btn;

// ================= STYLES =================
static lv_style_t style_btn_primary;
static lv_style_t style_btn_secondary;
static lv_style_t style_title_text;
static lv_style_t style_body_text;

// ================= SCREEN 1: WiFi Connect =================
void ui_Screen_WiFi_screen_init(void) {
    ui_Screen_WiFi = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_WiFi, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_Screen_WiFi, lv_color_hex(0xF5F5F5), LV_PART_MAIN);
    
    // Title
    ui_wifi_title_label = lv_label_create(ui_Screen_WiFi);
    lv_obj_set_width(ui_wifi_title_label, 700);
    lv_obj_set_height(ui_wifi_title_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_wifi_title_label, 0);
    lv_obj_set_y(ui_wifi_title_label, -120);
    lv_obj_set_align(ui_wifi_title_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_title_label, "Configurar Wi-Fi!");
    lv_obj_set_style_text_align(ui_wifi_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_wifi_title_label, &lv_font_montserrat_20, LV_PART_MAIN);
    
    // WiFi Status
    ui_wifi_status_label = lv_label_create(ui_Screen_WiFi);
    lv_obj_set_width(ui_wifi_status_label, 600);
    lv_obj_set_height(ui_wifi_status_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_wifi_status_label, 0);
    lv_obj_set_y(ui_wifi_status_label, -20);
    lv_obj_set_align(ui_wifi_status_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_status_label, "Toque em CONECTAR para configurar WiFi");
    lv_obj_set_style_text_align(ui_wifi_status_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_wifi_status_label, &lv_font_montserrat_16, LV_PART_MAIN);
    
    // Connect Button
    ui_connect_btn = lv_btn_create(ui_Screen_WiFi);
    lv_obj_set_width(ui_connect_btn, 200);
    lv_obj_set_height(ui_connect_btn, 60);
    lv_obj_set_x(ui_connect_btn, 0);
    lv_obj_set_y(ui_connect_btn, 80);
    lv_obj_set_align(ui_connect_btn, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_connect_btn, onWiFiConnectClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(ui_connect_btn, lv_color_hex(0x007BFF), LV_PART_MAIN);
    
    lv_obj_t * label = lv_label_create(ui_connect_btn);
    lv_label_set_text(label, "CONECTAR");
    lv_obj_center(label);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_18, LV_PART_MAIN);
}

// ================= SCREEN 2: Payment Method =================
void ui_Screen_Payment_screen_init(void) {
    ui_Screen_Payment = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Payment, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_Screen_Payment, lv_color_hex(0xF5F5F5), LV_PART_MAIN);
    
    // Title
    ui_payment_title_label = lv_label_create(ui_Screen_Payment);
    lv_obj_set_width(ui_payment_title_label, 600);
    lv_obj_set_height(ui_payment_title_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_payment_title_label, 0);
    lv_obj_set_y(ui_payment_title_label, -120);
    lv_obj_set_align(ui_payment_title_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_payment_title_label, "Selecione a forma de pagamento");
    lv_obj_set_style_text_align(ui_payment_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_payment_title_label, &lv_font_montserrat_20, LV_PART_MAIN);
    
    // PIX Button (highlighted)
    ui_pix_btn = lv_btn_create(ui_Screen_Payment);
    lv_obj_set_width(ui_pix_btn, 300);
    lv_obj_set_height(ui_pix_btn, 80);
    lv_obj_set_x(ui_pix_btn, 0);
    lv_obj_set_y(ui_pix_btn, 0);
    lv_obj_set_align(ui_pix_btn, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_pix_btn, onPaymentMethodClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(ui_pix_btn, lv_color_hex(0x007BFF), LV_PART_MAIN);
    
    lv_obj_t * pix_label = lv_label_create(ui_pix_btn);
    lv_label_set_text(pix_label, "PIX");
    lv_obj_center(pix_label);
    lv_obj_set_style_text_color(pix_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(pix_label, &lv_font_montserrat_20, LV_PART_MAIN);
}

// ================= SCREEN 3: Select Value =================
void ui_Screen_Value_screen_init(void) {
    ui_Screen_Value = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Value, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_Screen_Value, lv_color_hex(0xF5F5F5), LV_PART_MAIN);
    
    // Title
    ui_value_title_label = lv_label_create(ui_Screen_Value);
    lv_obj_set_width(ui_value_title_label, 600);
    lv_obj_set_height(ui_value_title_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_value_title_label, 0);
    lv_obj_set_y(ui_value_title_label, -150);
    lv_obj_set_align(ui_value_title_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_value_title_label, "Selecione o valor");
    lv_obj_set_style_text_align(ui_value_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_value_title_label, &lv_font_montserrat_20, LV_PART_MAIN);
    
    // Current Value Display
    ui_value_label = lv_label_create(ui_Screen_Value);
    lv_obj_set_width(ui_value_label, 300);
    lv_obj_set_height(ui_value_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_value_label, 0);
    lv_obj_set_y(ui_value_label, -80);
    lv_obj_set_align(ui_value_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_value_label, "R$ 2,00");
    lv_obj_set_style_text_align(ui_value_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_value_label, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_value_label, lv_color_hex(0x007BFF), LV_PART_MAIN);
    
    // Value Selection Buttons
    ui_value_2_btn = lv_btn_create(ui_Screen_Value);
    lv_obj_set_width(ui_value_2_btn, 120);
    lv_obj_set_height(ui_value_2_btn, 50);
    lv_obj_set_x(ui_value_2_btn, -140);
    lv_obj_set_y(ui_value_2_btn, 20);
    lv_obj_set_align(ui_value_2_btn, LV_ALIGN_CENTER);
    
    lv_obj_t * label_2 = lv_label_create(ui_value_2_btn);
    lv_label_set_text(label_2, "R$ 2,00");
    lv_obj_center(label_2);
    
    // Confirm Button
    ui_confirm_value_btn = lv_btn_create(ui_Screen_Value);
    lv_obj_set_width(ui_confirm_value_btn, 200);
    lv_obj_set_height(ui_confirm_value_btn, 60);
    lv_obj_set_x(ui_confirm_value_btn, 0);
    lv_obj_set_y(ui_confirm_value_btn, 120);
    lv_obj_set_align(ui_confirm_value_btn, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_confirm_value_btn, onValueSelectClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(ui_confirm_value_btn, lv_color_hex(0x007BFF), LV_PART_MAIN);
    
    lv_obj_t * confirm_label = lv_label_create(ui_confirm_value_btn);
    lv_label_set_text(confirm_label, "PAGAR");
    lv_obj_center(confirm_label);
    lv_obj_set_style_text_color(confirm_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(confirm_label, &lv_font_montserrat_18, LV_PART_MAIN);
}

// ================= SCREEN 4: PIX Payment =================
void ui_Screen_PIX_screen_init(void) {
    ui_Screen_PIX = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_PIX, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_Screen_PIX, lv_color_hex(0xF5F5F5), LV_PART_MAIN);
    
    // Title
    ui_pix_title_label = lv_label_create(ui_Screen_PIX);
    lv_obj_set_width(ui_pix_title_label, 600);
    lv_obj_set_height(ui_pix_title_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_pix_title_label, 0);
    lv_obj_set_y(ui_pix_title_label, -180);
    lv_obj_set_align(ui_pix_title_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_pix_title_label, "Forma de pagamento: PIX");
    lv_obj_set_style_text_align(ui_pix_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_pix_title_label, &lv_font_montserrat_20, LV_PART_MAIN);
    
    // Amount
    ui_pix_amount_label = lv_label_create(ui_Screen_PIX);
    lv_obj_set_width(ui_pix_amount_label, 300);
    lv_obj_set_height(ui_pix_amount_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_pix_amount_label, 0);
    lv_obj_set_y(ui_pix_amount_label, -130);
    lv_obj_set_align(ui_pix_amount_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_pix_amount_label, "R$ 2,00");
    lv_obj_set_style_text_align(ui_pix_amount_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_pix_amount_label, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_pix_amount_label, lv_color_hex(0x007BFF), LV_PART_MAIN);
    
    // QR Code placeholder
    ui_qr_code_canvas = lv_obj_create(ui_Screen_PIX);
    lv_obj_set_width(ui_qr_code_canvas, 200);
    lv_obj_set_height(ui_qr_code_canvas, 200);
    lv_obj_set_x(ui_qr_code_canvas, 0);
    lv_obj_set_y(ui_qr_code_canvas, -20);
    lv_obj_set_align(ui_qr_code_canvas, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_qr_code_canvas, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_border_color(ui_qr_code_canvas, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(ui_qr_code_canvas, 2, LV_PART_MAIN);
    
    // Timer
    ui_timer_label = lv_label_create(ui_Screen_PIX);
    lv_obj_set_width(ui_timer_label, 200);
    lv_obj_set_height(ui_timer_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_timer_label, 0);
    lv_obj_set_y(ui_timer_label, 120);
    lv_obj_set_align(ui_timer_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_timer_label, "01:00");
    lv_obj_set_style_text_align(ui_timer_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_timer_label, &lv_font_montserrat_20, LV_PART_MAIN);
    
    // Cancel Button
    ui_cancel_btn = lv_btn_create(ui_Screen_PIX);
    lv_obj_set_width(ui_cancel_btn, 150);
    lv_obj_set_height(ui_cancel_btn, 50);
    lv_obj_set_x(ui_cancel_btn, 0);
    lv_obj_set_y(ui_cancel_btn, 180);
    lv_obj_set_align(ui_cancel_btn, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_cancel_btn, onCancelPaymentClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(ui_cancel_btn, lv_color_hex(0xDC3545), LV_PART_MAIN);
    
    lv_obj_t * cancel_label = lv_label_create(ui_cancel_btn);
    lv_label_set_text(cancel_label, "Cancelar");
    lv_obj_center(cancel_label);
    lv_obj_set_style_text_color(cancel_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
}

// ================= SCREEN 5: Operation Complete =================
void ui_Screen_Complete_screen_init(void) {
    ui_Screen_Complete = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_Complete, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_Screen_Complete, lv_color_hex(0xF5F5F5), LV_PART_MAIN);
    
    // Success Message
    ui_success_label = lv_label_create(ui_Screen_Complete);
    lv_obj_set_width(ui_success_label, 600);
    lv_obj_set_height(ui_success_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_success_label, 0);
    lv_obj_set_y(ui_success_label, -50);
    lv_obj_set_align(ui_success_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_success_label, "Compra concluída com sucesso\nR$ 2,00");
    lv_obj_set_style_text_align(ui_success_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_success_label, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_success_label, lv_color_hex(0x28A745), LV_PART_MAIN);
    
    // Back to Start Button
    ui_back_to_start_btn = lv_btn_create(ui_Screen_Complete);
    lv_obj_set_width(ui_back_to_start_btn, 200);
    lv_obj_set_height(ui_back_to_start_btn, 60);
    lv_obj_set_x(ui_back_to_start_btn, 0);
    lv_obj_set_y(ui_back_to_start_btn, 80);
    lv_obj_set_align(ui_back_to_start_btn, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_back_to_start_btn, onBackToStartClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(ui_back_to_start_btn, lv_color_hex(0x007BFF), LV_PART_MAIN);
    
    lv_obj_t * back_label = lv_label_create(ui_back_to_start_btn);
    lv_label_set_text(back_label, "NOVO PAGAMENTO");
    lv_obj_center(back_label);
    lv_obj_set_style_text_color(back_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(back_label, &lv_font_montserrat_16, LV_PART_MAIN);
}

// ================= SCREEN 6: No Connection =================
void ui_Screen_NoConnection_screen_init(void) {
    ui_Screen_NoConnection = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_NoConnection, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_Screen_NoConnection, lv_color_hex(0xF5F5F5), LV_PART_MAIN);
    
    // Title
    ui_no_conn_title_label = lv_label_create(ui_Screen_NoConnection);
    lv_obj_set_width(ui_no_conn_title_label, 600);
    lv_obj_set_height(ui_no_conn_title_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_no_conn_title_label, 0);
    lv_obj_set_y(ui_no_conn_title_label, -80);
    lv_obj_set_align(ui_no_conn_title_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_no_conn_title_label, "Sem Conexão com a Internet");
    lv_obj_set_style_text_align(ui_no_conn_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_no_conn_title_label, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_no_conn_title_label, lv_color_hex(0xDC3545), LV_PART_MAIN);
    
    // Description
    ui_no_conn_desc_label = lv_label_create(ui_Screen_NoConnection);
    lv_obj_set_width(ui_no_conn_desc_label, 500);
    lv_obj_set_height(ui_no_conn_desc_label, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_no_conn_desc_label, 0);
    lv_obj_set_y(ui_no_conn_desc_label, -20);
    lv_obj_set_align(ui_no_conn_desc_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_no_conn_desc_label, "Verifique sua conexão WiFi e tente novamente");
    lv_obj_set_style_text_align(ui_no_conn_desc_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_no_conn_desc_label, &lv_font_montserrat_16, LV_PART_MAIN);
    
    // Retry Button
    ui_retry_btn = lv_btn_create(ui_Screen_NoConnection);
    lv_obj_set_width(ui_retry_btn, 200);
    lv_obj_set_height(ui_retry_btn, 60);
    lv_obj_set_x(ui_retry_btn, 0);
    lv_obj_set_y(ui_retry_btn, 60);
    lv_obj_set_align(ui_retry_btn, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(ui_retry_btn, onRetryConnectionClick, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(ui_retry_btn, lv_color_hex(0x007BFF), LV_PART_MAIN);
    
    lv_obj_t * retry_label = lv_label_create(ui_retry_btn);
    lv_label_set_text(retry_label, "TENTAR NOVAMENTE");
    lv_obj_center(retry_label);
    lv_obj_set_style_text_color(retry_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(retry_label, &lv_font_montserrat_16, LV_PART_MAIN);
}

// ================= MAIN UI INITIALIZATION =================
void ui_init(void) {
    // Initialize all screens
    ui_Screen_WiFi_screen_init();
    ui_Screen_Payment_screen_init();
    ui_Screen_Value_screen_init();
    ui_Screen_PIX_screen_init();
    ui_Screen_Complete_screen_init();
    ui_Screen_NoConnection_screen_init();
    
    // Load the first screen (WiFi setup)
    lv_disp_load_scr(ui_Screen_WiFi);
}