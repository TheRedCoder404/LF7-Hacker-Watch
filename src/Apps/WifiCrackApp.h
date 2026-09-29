#pragma once
#include "Application.h"

class WifiCrackApp {
public:
    WifiCrackApp()
        : m_app("WifiCrack") {
        setup();
    }

    void setup();
    Application& getApp();

private:
    Application m_app;
    static bool selectedYes;
    static int scrollPos;
    static long lastScrolled;
    static constexpr int scrollMaxPos = 10;
    static constexpr int scrollDelay = 500;
    static constexpr int scrollCompleteDelay = 2000;

    static void loop();
    static void onUpdateDisplay(Display& display);
    static void onScrollUp();
    static void onScrollDown();
    static void onRotaryButtonPressed();

    static void onButtonPressed();
};
