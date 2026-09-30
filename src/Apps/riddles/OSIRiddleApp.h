#pragma once

#include "Application.h"
#include "Selector.h"
#include "Components/Display.h"
#include "ScrollingString.h"

class OSIRiddleApp {
public:
    OSIRiddleApp()
        : app("OSI-Analyser") {
        setup();
    }

    void setup();
    Application& getApp();
    static bool isDone();

private:
    Application app;
    static Selector selector;
    static const String blockText[6];
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
