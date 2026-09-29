#pragma once

#include "Application.h"
#include "ScrollingString.h"
#include "Selector.h"

class HandshakeGrabberApp {
public:
    HandshakeGrabberApp()
        : app("HandshakeGrab") {
        setup();
    }

    void setup();
    Application& getApp();

private:
    Application app;
    static String appNames[];
    static Selector selector;

    static void onUpdateDisplay(Display& display);
    static void onScrollUp();
    static void onScrollDown();
    static void onRotaryButtonPressed();
    static void onButtonPressed();
};
