import sys
import time
from serial_bridge import SerialBridge
from reze_brain import RezeBrain

try:
    import speech_recognition as sr
    HAS_SR = True
except ImportError:
    HAS_SR = False

def main():
    print("=" * 60)
    print("      🌸 REZE DESKTOP PET - HOST VOICE CONTROLLER 🌸")
    print("=" * 60)

    bridge = SerialBridge()
    connected = bridge.connect()
    if not connected:
        print("[!] Chế độ SIMULATION: Gửi lệnh giả lập (không nối Serial thực tế).")

    brain = RezeBrain()

    print("\nChọn phương thức tương tác:")
    print("  1. Nhập văn bản bàn phím (Testing / Quick Mode)")
    print("  2. Lắng nghe giọng nói qua Micro (Continuous Voice Mode)")
    
    choice = input("Lựa chọn (1 hoặc 2) [Mặc định: 1]: ").strip()

    if choice == "2":
        if not HAS_SR:
            print("[!] Thư viện speech_recognition chưa được cài. Vui lòng chạy: pip install SpeechRecognition pyaudio")
            print("[*] Tự động chuyển về Chế độ 1 (Nhập bàn phím).")
            run_keyboard_mode(brain, bridge)
        else:
            run_voice_mode(brain, bridge)
    else:
        run_keyboard_mode(brain, bridge)

def run_keyboard_mode(brain: RezeBrain, bridge: SerialBridge):
    print("\n[✓] Đã bật Chế độ Nhập Bàn phím.")
    print("Gõ câu thoại (Ví dụ: 'chào reze', 'reze xinh quá', 'nổ bom', 'đi ngủ') hoặc gõ 'exit' để thoát:\n")
    
    try:
        while True:
            text = input("Bạn > ").strip()
            if not text:
                continue
            if text.lower() in ["exit", "quit"]:
                break

            emotion, response = brain.process_input(text)
            print(f"Reze ({emotion}) > {response}\n")
            bridge.send_emotion(emotion, response)
    except KeyboardInterrupt:
        pass
    finally:
        bridge.close()
        print("\nTam biệt!")

def run_voice_mode(brain: RezeBrain, bridge: SerialBridge):
    print("\n[✓] Đã bật Chế độ Lắng nghe Giọng nói Micro.")
    recognizer = sr.Recognizer()
    recognizer.energy_threshold = 300
    recognizer.dynamic_energy_threshold = True

    try:
        with sr.Microphone() as source:
            print("[*] Đang căn chỉnh tiếng ồn môi trường... Vui lòng giữ yên lặng trong 1s.")
            recognizer.adjust_for_ambient_noise(source, duration=1)
            print("[✓] Đã sẵn sàng! Hãy nói điều gì đó với Reze (Ví dụ: 'Chào Reze')...\n")

            while True:
                try:
                    print("🎤 Đang lắng nghe...")
                    audio = recognizer.listen(source, timeout=5, phrase_time_limit=5)
                    print("⚡ Đang nhận diện giọng nói...")

                    # Sử dụng Google Speech Recognition cho tiếng Việt (vi-VN)
                    text = recognizer.recognize_google(audio, language="vi-VN")
                    print(f"Bạn (Nói) > \"{text}\"")

                    emotion, response = brain.process_input(text)
                    print(f"Reze ({emotion}) > {response}\n")
                    bridge.send_emotion(emotion, response)

                except sr.WaitTimeoutError:
                    continue
                except sr.UnknownValueError:
                    print("[?] Chưa nghe rõ câu bạn nói, thử lại xem sao...")
                except sr.RequestError as e:
                    print(f"[!] Lỗi kết nối Google Speech API: {e}")
                    time.sleep(2)
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(f"[!] Lỗi Micro: {e}")
    finally:
        bridge.close()
        print("\nTạm biệt!")

if __name__ == "__main__":
    main()
