# 🔌 Sơ đồ Đấu Nối Phần Cứng Reze Desktop Pet

Tài liệu này hướng dẫn cách kết nối vi điều khiển **ESP (ESP32-C3 / ESP8266)** với màn hình **TFT ILI9341 240x320 (SPI Interface)**.

---

## 📌 1. Bảng Sơ Đồ Đấu Nối Chân (Pinout Table)

### 🔹 Dành cho ESP32-C3 DevModule (Khuyên dùng)

| Chân trên Màn hình ILI9341 | Chân kết nối ESP32-C3 | Chức năng (Function) |
| :--- | :--- | :--- |
| **VCC** | `3.3V` hoặc `5V` | Nguồn nuôi màn hình |
| **GND** | `GND` | Chân mass / Đất |
| **CS (Chip Select)** | `GPIO 7` | Chọn thiết bị SPI |
| **RESET / RST** | `GPIO 5` | Reset màn hình |
| **DC / RS (Data/Command)**| `GPIO 6` | Phân biệt Lệnh hoặc Dữ liệu |
| **SDI / MOSI** | `GPIO 3` | Dữ liệu SPI Data In |
| **SCK / SCLK** | `GPIO 4` | Xung Clock SPI |
| **LED / BL (Backlight)** | `GPIO 8` hoặc `3.3V` | Đèn nền màn hình (Backlight) |
| **SDO / MISO** | `GPIO 2` (Optional) | Dữ liệu SPI Out (Không bắt buộc) |

---

### 🔹 Dành cho ESP8266 (NodeMCU v2 / D1 Mini)

| Chân trên Màn hình ILI9341 | Chân kết nối ESP8266 NodeMCU | Tên chân NodeMCU |
| :--- | :--- | :--- |
| **VCC** | `3.3V` | Nguồn nuôi 3.3V |
| **GND** | `GND` | Ground |
| **CS (Chip Select)** | `D8 (GPIO 15)` | Chip Select |
| **RESET / RST** | `D4 (GPIO 2)` | Hardware Reset |
| **DC / RS** | `D3 (GPIO 0)` | Data / Command Select |
| **SDI / MOSI** | `D7 (GPIO 13)` | SPI MOSI |
| **SCK / SCLK** | `D6 (GPIO 14)` | SPI SCK |
| **LED / BL** | `3.3V` | Đèn nền sáng liên tục |

---

## ⚡ 2. Lưu ý An Toàn & Cấp Nguồn

1. **Điện áp logic SPI:** Màn hình ILI9341 hoạt động ở mức logic **3.3V**. Cả ESP32-C3 và ESP8266 đều cấp đầu ra 3.3V nên nối trực tiếp mà không cần mạch chuyển mức điện áp (Level Shifter).
2. **Đèn nền (LED / BL):** Nếu bạn thấy màn hình tối thui sau khi nạp code, hãy đảm bảo chân **LED / BL** đã được nối với `3.3V` để bật đèn nền.
3. **Cáp USB:** Hãy sử dụng cáp Micro USB hoặc USB-C **có truyền dữ liệu (Data Cable)**, không dùng cáp sạc thuần túy để PC có thể nhận cổng COM Serial.
