#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Serial Baud Rate
#define SERIAL_BAUD_RATE 115200

// Screen Dimensions (ILI9341 240x320)
#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

// Reze Pet Face Colors (RGB565 format)
#define COLOR_BG          0x18C3 // Dark Purple / Midnight Gray
#define COLOR_CHEEK       0xFBB0 // Soft Blush Pink
#define COLOR_EYE_GREEN   0x3E8A // Reze Emerald Eye Green
#define COLOR_HAIR_PURPLE 0x3971 // Reze Hair Deep Violet
#define COLOR_WHITE       0xFFFF // White
#define COLOR_BLACK       0x0000 // Black
#define COLOR_BOMB_RED    0xF800 // Bomb Mode Bright Red

#endif // CONFIG_H
