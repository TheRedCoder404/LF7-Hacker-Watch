#pragma once

#include "Application.h"
#include "Selector.h"
#include "Components/Display.h"

class OSIRiddleApp {
public:
    OSIRiddleApp()
        : m_app("OSI-Analyser") {
        setup();
    }

    void setup();
    Application& getApp();

private:
    Application m_app;
    static Selector selector;
    static const String blockText[5];

    static void onUpdateDisplay(Display& display);
    static void onScrollUp();
    static void onScrollDown();
    static void onButtonPressed();
};
