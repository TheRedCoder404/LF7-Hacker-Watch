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

    static void onUpdateDisplay(Display& display);
    static void onScrollUp();
    static void onScrollDown();
    static void onRotaryButtonPressed();
};
