# 💳 ESP32 Payment System with QR Code

This project is an ESP32-based payment interface that displays a graphical user interface (GUI) using LVGL and SquareLine Studio.  
It allows users to configure Wi-Fi, select payment amounts, generate QR codes, and verify transactions via an API.

---

## 🧩 Screens Overview

### ⚙️ ConfigScreen
Screen for configuring Wi-Fi using **WiFiManager**.  
Displayed automatically on first boot or when Wi-Fi connection fails.

---

### 💰 PayScreen (Main Screen)
Main screen where the user selects the payment amount.

**Features:**
- Default amount: **2.00**
- "+" and "–" buttons to change the value.
- Available amounts:
