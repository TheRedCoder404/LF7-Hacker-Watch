#pragma once

#include "Application.h"
#include "Display.h"

class TestApp {
public:
    TestApp();
    TestApp(Display& display)
        : m_display(display) {}

    void setup();
    Application& getApp();

private:
    Application m_app;
    Display& m_display;

    static void updateDisplay();
};
