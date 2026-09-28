#pragma once

#include "Application.h"

class SettingsApp {
public:
    SettingsApp()
        : m_app("Settings") {
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
