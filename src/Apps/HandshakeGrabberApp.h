#pragma once
#include "Application.h"
#include "ScrollingString.h"

class HandshakeGrabberApp {
public:
    HandshakeGrabberApp()
        : m_app("HandshakeGrab") {
        setup();
    }

    void setup();
    Application& getApp();

private:
    Application m_app;
    static ScrollingString testText;

    static void loop();
    static void onSelected();
    static void onUpdateDisplay(Display& display);
    static void onScrollUp();
    static void onScrollDown();
    static void onRotaryButtonPressed();
    static void onButtonPressed();
};
