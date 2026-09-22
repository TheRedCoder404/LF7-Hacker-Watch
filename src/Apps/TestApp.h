#pragma once

#include "Application.h"

class TestApp {
public:
    TestApp() {
        setup();
    }

    void setup();
    Application& getApp();

private:
    Application m_app;
    static bool pressed;
    static int scroll;

    static void loop();
    static void onUpdateDisplay(Display& display);
    static void onScrollUp();
    static void onScrollDown();
    static void onRotaryButtonPressed();
};
