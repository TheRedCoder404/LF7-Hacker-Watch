#pragma once

#include "Application.h"
#include "ScrollingString.h"

class WifiCrackApp {
public:
    WifiCrackApp()
        : m_app("WifiCrack") {
        setup();
    }

    void setup();
    Application& getApp();
    static bool isDone();
    static void reset();

private:
    Application m_app;
    static ScrollingString scrollText;
    static bool selecting;
    static bool selectedYes;
    static bool devicesDisconnected;
    static bool disconnectComplete;
    static int disconnectLoadingProgress;
    static long lastTiming;
    static constexpr int loadingDelay = 500;
    static constexpr int loadingMax = 11;

    static void loop();
    static void onSelected();
    static void loadingTimings();

    static void onUpdateDisplay(Display& display);
    static void printDisconnectDialog(Display &display);
    static void printDisconnecting(Display &display);
    static void printDisconnected(Display &display);

    static void onScrollUp();
    static void onScrollDown();
    static void onRotaryButtonPressed();

    static void onButtonPressed();
    static void resetApp();
};
