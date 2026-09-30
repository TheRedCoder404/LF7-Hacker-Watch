#pragma once

#include "Application.h"
#include "ScrollingString.h"
#include "Selector.h"

class CodeRiddleApp {
public:
    CodeRiddleApp()
        : app("Code-Analyser") {
        setup();
    }

    void setup();
    Application& getApp();
    static bool isDone();

private:
    Application app;
    static Selector selector;
    static const String blockText[9];
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
