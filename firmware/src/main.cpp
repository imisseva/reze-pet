#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include "config.h"
#include "reze_expressions.h"

TFT_eSPI tft = TFT_eSPI();
RezeEmotion currentEmotion = EMOTION_NEUTRAL;
RezeEmotion targetEmotion = EMOTION_NEUTRAL;

unsigned long lastBlinkTime = 0;
bool isBlinking = false;
unsigned long emotionTimer = 0;

void drawBackground() {
    tft.fillScreen(COLOR_BG);
    
    // Draw subtle Reze choker pin / ribbon icon at the bottom
    tft.fillRoundRect(80, 290, 80, 12, 6, COLOR_HAIR_PURPLE);
    tft.fillCircle(120, 296, 6, COLOR_BOMB_RED);
}

void drawFace(RezeEmotion emotion, bool blink) {
    int eyeY = 130;
    int leftEyeX = 70;
    int rightEyeX = 170;
    int eyeRadiusX = 24;
    int eyeRadiusY = 32;

    // Clear Face Area
    tft.fillRect(30, 70, 180, 190, COLOR_BG);

    // 1. Draw Cheek Blush
    if (emotion == EMOTION_SHY || emotion == EMOTION_HAPPY) {
        tft.fillEllipse(leftEyeX - 15, eyeY + 45, 18, 10, COLOR_CHEEK);
        tft.fillEllipse(rightEyeX + 15, eyeY + 45, 18, 10, COLOR_CHEEK);
    } else {
        tft.fillEllipse(leftEyeX - 15, eyeY + 45, 12, 6, COLOR_CHEEK);
        tft.fillEllipse(rightEyeX + 15, eyeY + 45, 12, 6, COLOR_CHEEK);
    }

    // 2. Draw Eyes
    if (blink || emotion == EMOTION_SLEEPY) {
        // Closed Eyes (Line ^ ^ or - -)
        tft.drawFastHLine(leftEyeX - 20, eyeY, 40, COLOR_HAIR_PURPLE);
        tft.drawFastHLine(rightEyeX - 20, eyeY, 40, COLOR_HAIR_PURPLE);
    } else if (emotion == EMOTION_HAPPY) {
        // Happy Eyes (Cute Arcs ^ ^)
        for (int i = 0; i < 4; i++) {
            tft.drawCircleHelper(leftEyeX, eyeY + 5, 22 - i, 1, COLOR_HAIR_PURPLE);
            tft.drawCircleHelper(leftEyeX, eyeY + 5, 22 - i, 2, COLOR_HAIR_PURPLE);
            tft.drawCircleHelper(rightEyeX, eyeY + 5, 22 - i, 1, COLOR_HAIR_PURPLE);
            tft.drawCircleHelper(rightEyeX, eyeY + 5, 22 - i, 2, COLOR_HAIR_PURPLE);
        }
    } else if (emotion == EMOTION_BOMB_MODE) {
        // Bomb Mode (Glowing Red Sharp Eyes)
        tft.fillEllipse(leftEyeX, eyeY, eyeRadiusX, eyeRadiusY, COLOR_BOMB_RED);
        tft.fillEllipse(rightEyeX, eyeY, eyeRadiusX, eyeRadiusY, COLOR_BOMB_RED);
        tft.fillCircle(leftEyeX, eyeY, 8, COLOR_BLACK);
        tft.fillCircle(rightEyeX, eyeY, 8, COLOR_BLACK);
        // Spark effect
        tft.drawLine(leftEyeX - 30, eyeY - 20, leftEyeX - 10, eyeY - 5, COLOR_WHITE);
        tft.drawLine(rightEyeX + 30, eyeY - 20, rightEyeX + 10, eyeY - 5, COLOR_WHITE);
    } else {
        // Neutral / Shy / Surprised / Talking (Anime Eyes with emerald iris)
        uint16_t eyeColor = (emotion == EMOTION_SHY) ? COLOR_HAIR_PURPLE : COLOR_EYE_GREEN;
        
        tft.fillEllipse(leftEyeX, eyeY, eyeRadiusX, eyeRadiusY, COLOR_WHITE);
        tft.fillEllipse(rightEyeX, eyeY, eyeRadiusX, eyeRadiusY, COLOR_WHITE);
        
        // Iris
        tft.fillEllipse(leftEyeX, eyeY, eyeRadiusX - 8, eyeRadiusY - 6, eyeColor);
        tft.fillEllipse(rightEyeX, eyeY, eyeRadiusX - 8, eyeRadiusY - 6, eyeColor);

        // Pupil & Highlights
        tft.fillCircle(leftEyeX, eyeY + 2, 8, COLOR_BLACK);
        tft.fillCircle(rightEyeX, eyeY + 2, 8, COLOR_BLACK);
        tft.fillCircle(leftEyeX - 6, eyeY - 8, 5, COLOR_WHITE);
        tft.fillCircle(rightEyeX - 6, eyeY - 8, 5, COLOR_WHITE);
        tft.fillCircle(leftEyeX + 5, eyeY + 8, 3, COLOR_WHITE);
        tft.fillCircle(rightEyeX + 5, eyeY + 8, 3, COLOR_WHITE);

        // Eyelashes
        tft.drawFastHLine(leftEyeX - 25, eyeY - eyeRadiusY, 50, COLOR_HAIR_PURPLE);
        tft.drawFastHLine(rightEyeX - 25, eyeY - eyeRadiusY, 50, COLOR_HAIR_PURPLE);
    }

    // 3. Draw Mouth
    int mouthY = eyeY + 55;
    if (emotion == EMOTION_HAPPY) {
        // Big Smile curve
        tft.fillCircleHelper(120, mouthY - 5, 16, 4, COLOR_HAIR_PURPLE);
    } else if (emotion == EMOTION_TALKING) {
        // Open Mouth
        tft.fillEllipse(120, mouthY, 12, 8, COLOR_HAIR_PURPLE);
        tft.fillEllipse(120, mouthY + 2, 8, 4, COLOR_CHEEK);
    } else if (emotion == EMOTION_SURPRISED) {
        // Small 'O' Mouth
        tft.drawCircle(120, mouthY, 10, COLOR_HAIR_PURPLE);
    } else if (emotion == EMOTION_BOMB_MODE) {
        // Sharp smile / smirk
        tft.drawLine(105, mouthY + 5, 120, mouthY, COLOR_BOMB_RED);
        tft.drawLine(120, mouthY, 135, mouthY + 5, COLOR_BOMB_RED);
    } else {
        // Slight cute smile line
        tft.drawCircleHelper(120, mouthY - 8, 12, 4, COLOR_HAIR_PURPLE);
    }
}

void processIncomingSerial() {
    if (Serial.available() > 0) {
        String jsonInput = Serial.readStringUntil('\n');
        JsonDocument doc;
        DeserializationError err = deserializeJson(doc, jsonInput);

        if (!err) {
            const char* emotionStr = doc["emotion"];
            if (emotionStr) {
                targetEmotion = parseEmotionString(String(emotionStr));
                currentEmotion = targetEmotion;
                emotionTimer = millis();
                drawFace(currentEmotion, false);
            }
        } else {
            // Raw text command fallback
            jsonInput.trim();
            targetEmotion = parseEmotionString(jsonInput);
            currentEmotion = targetEmotion;
            drawFace(currentEmotion, false);
        }
    }
}

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    tft.init();
    tft.setRotation(0); // Portrait 240x320
    drawBackground();
    drawFace(currentEmotion, false);
}

void loop() {
    processIncomingSerial();

    // Blink Logic (Every 3-5 seconds)
    unsigned long now = millis();
    if (now - lastBlinkTime > 3500) {
        drawFace(currentEmotion, true);
        delay(120);
        drawFace(currentEmotion, false);
        lastBlinkTime = now;
    }

    // Reset temporary emotions (e.g., TALKING / SURPRISED back to HAPPY or NEUTRAL after 4 seconds)
    if (currentEmotion != EMOTION_NEUTRAL && currentEmotion != EMOTION_HAPPY && (now - emotionTimer > 4000)) {
        currentEmotion = EMOTION_NEUTRAL;
        drawFace(currentEmotion, false);
    }

    delay(20);
}
