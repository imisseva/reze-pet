# 💣 Reze Desktop Pet - Chainsaw Man Companion

Dự án thú cưng để bàn thông minh mô phỏng nhân vật **Reze (Chainsaw Man)** trên màn hình **TFT ILI9341 240x320** kết nối với vi điều khiển **ESP32 / ESP8266**, phản hồi cảm xúc sinh động khi bạn trò chuyện qua giọng nói.

---

## 🌟 Tính Năng Nổi Bật

- 🎭 **Đồ Họa Biểu Cảm Procedural Mượt Mà:** Mắt anime emerald, chớp mắt tự nhiên, má hồng thay đổi theo cảm xúc (`HAPPY`, `SHY`, `BOMB_MODE`, `SLEEPY`, `SURPRISED`, `TALKING`).
- 🎙️ **Nhận Diện Giọng Nói Real-time:** Thu âm qua Micro máy tính (vi-VN), tự động phân tích từ khóa câu chào, lời khen, trêu chọc và phát tín hiệu đổi mặt Reze.
- 💻 **Trình Mô Phỏng Web Preview:** Dễ dàng test hoạt ảnh và giọng nói Reze trực tiếp trên trình duyệt mà chưa cần cắm dây mạch!
- ⚡ **Giao Tiếp USB Serial:** Đơn giản, độ ổn định cao, latency cực thấp.

---

## 📁 Cấu Trúc Dự Án

```
reze-pet/
├── firmware/                     # ESP32/ESP8266 Firmware (PlatformIO)
│   ├── platformio.ini           # Cấu hình nạp vi điều khiển & thư viện TFT_eSPI
│   ├── include/
│   │   ├── config.h             # Định nghĩa bảng màu Reze & kích thước ILI9341
│   │   └── reze_expressions.h   # Enum biểu cảm & parser lệnh Serial
│   └── src/
│       └── main.cpp             # Code vẽ mặt Reze & xử lý chớp mắt / Serial
├── host_app/                    # Ứng dụng Python Controller trên PC
│   ├── main.py                  # Điểm chạy chính (Chế độ Voice Mic & Bàn phím)
│   ├── reze_brain.py            # Logic nhận diện câu thoại & chọn cảm xúc Reze
│   ├── serial_bridge.py         # Quản lý giao tiếp cổng COM USB Serial với ESP
│   └── requirements.txt         # Thư viện Python hỗ trợ
├── docs/
│   └── hardware_setup.md        # Sơ đồ nối dây chi tiết ESP <-> ILI9341 TFT
└── web_preview/
    └── index.html               # Web Simulator xem thử Reze mượt mà trên browser
```

---

## 🚀 Hướng Dẫn Sử Dụng Nhanh

### 1. Xem Thử Trên Web Simulator (Không cần cắm phần cứng)
1. Mở file [web_preview/index.html](file:///d:/my-projects/reze-pet/web_preview/index.html) bằng trình duyệt Web (Google Chrome hoặc Microsoft Edge).
2. Click nút **"🎙️ Lắng nghe Giọng nói"** và thử nói *"Chào Reze"* hoặc *"Reze xinh quá"* để xem Reze đổi biểu cảm!

---

### 2. Cài Đặt Firmware Cho ESP & Màn Hình ILI9341
1. Xem hướng dẫn nối dây tại [docs/hardware_setup.md](file:///d:/my-projects/reze-pet/docs/hardware_setup.md).
2. Mở thư mục `firmware/` bằng **VS Code + PlatformIO extension**.
3. Cắm ESP vào máy tính qua cáp USB và bấm **Build & Upload**.

---

### 3. Chạy Host Voice Controller Trên Máy Tính (Python)
1. Cài đặt các thư viện Python:
   ```bash
   cd host_app
   pip install -r requirements.txt
   ```
2. Chạy ứng dụng lắng nghe giọng nói:
   ```bash
   python main.py
   ```
3. Nói chuyện với Reze và quan sát biểu cảm Reze lập tức thay đổi trên màn hình TFT!
