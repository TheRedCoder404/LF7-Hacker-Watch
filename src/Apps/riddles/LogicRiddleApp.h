#pragma once

#include "Application.h"
#include "ScrollingString.h"
#include "Selector.h"

class LogicRiddleApp {
public:
    LogicRiddleApp()
        : app("Logi-Analyser") {
        setup();
    }

    void setup();
    Application& getApp();
    static bool isDone();
    static void reset();

private:
    Application app;
    static Selector selector;
    static const String blockText[7];
    static bool scrolling;
    static bool confirmationEntered;
    static bool selectedYes;
    static bool pinConfirmed;
    static ScrollingString scrollText;

    static void loop();
    static void onUpdateDisplay(Display& display);
    static void onSelected();
    static void onScrollUp();
    static void onScrollDown();
    static void onButtonPressed();
    static void onRotaryButtonPressed();
};
