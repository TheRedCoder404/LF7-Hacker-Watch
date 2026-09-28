#pragma once
#include "Application.h"

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

    static void onUpdateDisplay(Display& display);
    static void onScrollUp();
    static void onScrollDown();
    static void onRotaryButtonPressed();
    static void onButtonPressed();
};
