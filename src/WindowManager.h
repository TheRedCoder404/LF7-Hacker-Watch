#pragma once

#include "Application.h"
#include "Display.h"
#include "Encoder.h"

class WindowManager {
    static constexpr int RELEASED_DELAY = 50;

public:
    WindowManager(Application& app)
        : display()
        , currentApp(app)
        , lastApp(app)
        , encoder(rotaryDt, rotaryClk)
        , toBePressed(false) {
        currentApp.setDisplay(&display);
        setup();
    }

    void setup();

    void updateDisplay();
    void setCurrentApp(const Application& app);

    void onRotarySwitchPressed();

    void loop();

private:
    const uint8_t rotarySw = D10;
    const uint8_t rotaryDt = D9;
    const uint8_t rotaryClk = D8;
    const uint8_t button = D7;

    uint32_t lastPressed = 0;
    long rotaryState = -999;
    bool rotaryButtonPressed = false;
    bool buttonPressed = false;
    volatile bool toBePressed;

    Display display;
    Application& currentApp;
    Application& lastApp;
    Encoder encoder;

    static void ARDUINO_ISR_ATTR rotarySwitchInterrupt(void *argument);

    void checkRotaryEncoder();
    void checkRotaryEncoderButton();
    void checkButton();
};
