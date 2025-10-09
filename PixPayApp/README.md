# 💳 ESP32 Payment System with QR Code

This project is an ESP32-based payment interface that displays a graphical user interface (GUI) using LVGL and SquareLine Studio. It allows users to configure Wi-Fi, select payment amounts, generate QR codes, and verify transactions via an API.

## 🧩 Screens Overview

### ⚙️ ConfigScreen
Screen for configuring Wi-Fi using **WiFiManager**. Displayed automatically on first boot or when Wi-Fi connection fails.

### 💰 PayScreen (Main Screen)
Main screen where the user selects the payment amount.

**Features:**
- Default amount: **2.00**
- "+" and "–" buttons to change the value.
- Available amounts: 2.00, 5.00, 10.00, 20.00, 50.00, 100.00, 200.00
- **"Pay"** button to initiate the payment.

**Behavior:**
- If **no internet** or API response ≠ `200 OK`: navigate to **NoConnectionScreen** (shows “No Internet” for 10 seconds, then returns to PayScreen).
- If **API returns 200 OK**: navigate to **Qrcode-Screen** to display the payment QR code.

### 🚫 NoConnectionScreen
Displays the message **“No Internet”**, remains visible for **10 seconds**, then automatically returns to **PayScreen**.

### 🧾 Qrcode-Screen
Displays the QR code generated for the selected payment amount.

**Components:**
- Selected payment value.
- Countdown timer of **2 minutes**.
- **Cancel** button → Returns to **PayScreen**.

**Behavior:**
- If payment not completed within 2 minutes → Return to PayScreen.
- If payment completed (`status = "approved"`) → Navigate to **ApprovedScreen**.

### ✅ ApprovedScreen
Displays **“Payment Received!”** and triggers a relay pulse on **GPIO 17**, pulsing every **300 ms** for the number of times defined by the API field `pulsos`.

## 🌐 API Endpoints

> **Note:** The actual server URL is hidden for security reasons.

### 1️⃣ Generate QR Code
**POST** `/qrcode`
```json
{
  "maquinaId": "<your_machine_id>",
  "valor": 1.00
}
Response (HTTP 200):

json
Copiar código
{
  "id": 129190831640,
  "qr_code_base64": "<base64_png_data>",
  "qr_code_text": "<pix_qr_code_text>"
}
Use either qr_code_base64 to render the QR code as an image, or qr_code_text to generate it dynamically.

2️⃣ Check Payment Status
POST /qrcode/status

json
Copiar código
{
  "maquinaId": "<your_machine_id>",
  "paymentId": "129190831640"
}
Response Example:

json
Copiar código
{
  "status": "pending",
  "pulsos": 1
}
If status = "approved", show ApprovedScreen and pulse relay on pin 17.

⏱ Timeout Behavior
If the payment is not completed within 2 minutes, the system automatically returns to PayScreen to allow a new payment.

⚙️ Configuration
At the beginning of your code, define two fixed string constants:

cpp
Copiar código
const char* SERVER_URL = "<hidden_server_url>";
const char* MACHINE_ID = "0005cd1a-e258-4c57-b6d9-a55bcffa7405";
🧠 Additional Notes
Wi-Fi connection handled via WiFiManager.

GUI designed using SquareLine Studio and rendered with LVGL.

API communication handled using HTTP POST requests.

Payment checking runs every 2 seconds on the Qrcode-Screen.

🛠️ Technologies
ESP32

LVGL + SquareLine Studio

C++ / Arduino Framework

WiFiManager

HTTPClient
