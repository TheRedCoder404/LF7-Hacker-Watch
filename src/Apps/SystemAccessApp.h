#pragma once
#include "Application.h"

class SystemAccessApp {
public:
    SystemAccessApp()
        : app("System Access") {
        setup();
    }

    void setup();
    Application& getApp();

private:
    Application app;
    static bool hacked;

    static void onUpdateDisplay(Display& display);
    static void onButtonPressed();
    static void onScrollUp();
    static void onScrollDown();
};
