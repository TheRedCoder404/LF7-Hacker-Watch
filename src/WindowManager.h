#pragma once

#include "Application.h"
#include "Components/Display.h"
#include "Components/RotaryEncoder.h"

class WindowManager {
    static constexpr int RELEASED_DELAY = 50;

public:
    explicit WindowManager(Application& app)
        : display()
        , currentApp(&app)
        , lastApp(nullptr)
        , encoder() {}

    void setup();

    void updateDisplay();
    void setCurrentApp(Application& app);

    void onRotarySwitchPressed();

    void loop();

private:
    const uint8_t button = D7;

    uint32_t lastPressed = 0;
    uint32_t lastRotated = 0;
    long rotaryState = -999;
    bool rotaryButtonPressed = false;
    bool buttonPressed = false;
    volatile bool toBePressed = false;
    static volatile bool toBeScrollUp;
    static volatile bool toBeScrollDown;

    Display display;
    RotaryEncoder encoder;

    Application* currentApp;
    Application* lastApp;

    static void ARDUINO_ISR_ATTR rotarySwitchInterrupt(void *argument);

    static void onRotationUp();
    static void onRotationDown();

    void checkRotaryEncoder(int rotation);
    void checkRotaryEncoderButton();
    void checkButton();
};
