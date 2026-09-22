#pragma once

#include "Encoder.h"
#include "WindowManager.h"
#include "Apps/TestApp.h"

class Program {
public:
    Program()
        : encoder(rotaryDt, rotaryClk)
        , menu(display)
        , windowManager(display, menu.getApp()) {}

    void loop();

private:
    const uint8_t rotarySw = D10;
    const uint8_t rotaryDt = D9;
    const uint8_t rotaryClk = D8;
    Encoder encoder;

    long rotaryState = -999;
    bool pressed = false;
    volatile bool toBePressed = false;

    Display display;
    TestApp menu;
    WindowManager windowManager;

    void setup();
};
