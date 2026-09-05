import json
import time
import serial
import serial.tools.list_ports

class SerialBridge:
    def __init__(self, port=None, baudrate=115200):
        self.port = port
        self.baudrate = baudrate
        self.ser = None

    def auto_detect_port(self):
        ports = serial.tools.list_ports.comports()
        for p in ports:
            # Common USB Serial CH340, CP210x, ESP32 CDC
            if "CH340" in p.description or "CP210" in p.description or "USB" in p.description or "ESP" in p.description:
                print(f"[*] Tìm thấy bo mạch ESP tại cổng: {p.device} ({p.description})")
                return p.device
        if ports:
            print(f"[*] Sử dụng cổng đầu tiên khả dụng: {ports[0].device}")
            return ports[0].device
        return None

    def connect(self):
        if not self.port:
            self.port = self.auto_detect_port()

        if not self.port:
            print("[!] Không tìm thấy cổng COM kết nối ESP. Vui lòng cắm cáp USB!")
            return False

        try:
            self.ser = serial.Serial(self.port, self.baudrate, timeout=1)
            time.sleep(2) # Chờ ESP reset sau khi mở Serial
            print(f"[✓] Đã kết nối Serial thành công tới {self.port} ở tốc độ {self.baudrate} baud.")
            return True
        except Exception as e:
            print(f"[!] Lỗi kết nối cổng Serial {self.port}: {e}")
            self.ser = None
            return False

    def send_emotion(self, emotion: str, text: str = ""):
        payload = {
            "emotion": emotion.upper(),
            "text": text
        }
        json_cmd = json.dumps(payload) + "\n"
        print(f"[-> Serial] Gửi lệnh: {json_cmd.strip()}")

        if self.ser and self.ser.is_open:
            try:
                self.ser.write(json_cmd.encode('utf-8'))
                return True
            except Exception as e:
                print(f"[!] Lỗi khi gửi dữ liệu qua Serial: {e}")
                return False
        else:
            print("[Simulated Serial] (Chưa cắm ESP): Dữ liệu gửi thành công simulated.")
            return True

    def close(self):
        if self.ser and self.ser.is_open:
            self.ser.close()
            print("[*] Đã đóng cổng Serial.")
