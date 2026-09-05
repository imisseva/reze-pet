#ifndef REZE_EXPRESSIONS_H
#define REZE_EXPRESSIONS_H

#include <Arduino.h>

// Reze Emotion Enum States
enum RezeEmotion {
    EMOTION_NEUTRAL = 0, // Thản nhiên, nháy mắt
    EMOTION_HAPPY,       // Hạnh phúc, mắt cười cong ^ ^
    EMOTION_SHY,         // Ngượng phùng má, má hồng đậm
    EMOTION_TALKING,     // Đang nói chuyện (chớp khuôn miệng)
    EMOTION_BOMB_MODE,   // Chế độ Quỷ Bom (Mắt đỏ/tia lửa)
    EMOTION_SLEEPY,      // Đang ngủ (- _ - zZz)
    EMOTION_SURPRISED    // Bất ngờ (Mắt to tròn, miệng O)
};

// Convert string command from Serial (e.g., "HAPPY", "SHY") to enum
inline RezeEmotion parseEmotionString(const String& cmd) {
    String upperCmd = cmd;
    upperCmd.toUpperCase();
    upperCmd.trim();
    
    if (upperCmd == "HAPPY") return EMOTION_HAPPY;
    if (upperCmd == "SHY") return EMOTION_SHY;
    if (upperCmd == "TALKING") return EMOTION_TALKING;
    if (upperCmd == "BOMB") return EMOTION_BOMB_MODE;
    if (upperCmd == "SLEEPY") return EMOTION_SLEEPY;
    if (upperCmd == "SURPRISED") return EMOTION_SURPRISED;
    return EMOTION_NEUTRAL;
}

#endif // REZE_EXPRESSIONS_H
