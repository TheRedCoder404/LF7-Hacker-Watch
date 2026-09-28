#pragma once

#include "Application.h"
#include "Selector.h"

class SettingsApp {
public:
    SettingsApp()
        : app("Settings") {
        setup();
    }

    void setup();
    Application& getApp();

private:
    static const String settings[2];
    static Selector selector;

    Application app;
    static int scroll;
    static int viewScroll;

    static void onUpdateDisplay(Display& display);
    static void onScrollUp();
    static void onScrollDown();
    static void onRotaryButtonPressed();
};
