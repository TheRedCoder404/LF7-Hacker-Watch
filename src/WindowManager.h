#pragma once

#include "Application.h"
#include "Components/Display.h"
#include "Components/RotaryEncoder.h"

class WindowManager {
    static constexpr int RELEASED_DELAY = 50;

public:
    explicit WindowManager()
        : encoder() {}

    void setup();

    static void updateDisplay();
    static void setCurrentApp(Application& app);

    void onRotarySwitchPressed();

    void loop();

private:
    const uint8_t button = D7;
    const uint8_t rotaryButton = D10;

    uint32_t lastPressed = 0;
    uint32_t lastRotated = 0;
    long rotaryState = -999;
    bool rotaryButtonPressed = false;
    bool buttonPressed = false;
    volatile bool toBePressed = false;
    static volatile bool toBeScrollUp;
    static volatile bool toBeScrollDown;

    static Display display;
    RotaryEncoder encoder;

    static Application* currentApp;

    static void ARDUINO_ISR_ATTR rotarySwitchInterrupt(void *argument);

    static void onRotationUp();
    static void onRotationDown();

    void checkRotaryEncoder(int rotation);
    void checkRotaryEncoderButton();
    void checkButton();
};
