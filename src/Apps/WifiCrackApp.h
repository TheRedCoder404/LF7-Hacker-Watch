#pragma once
#include "Application.h"

class WifiCrackApp {
public:
    WifiCrackApp()
        : m_app("WifiCrack") {
        setup();
    }

    void setup();
    Application& getApp();
    static bool isDone();

private:
    Application m_app;
    static bool selecting;
    static bool selectedYes;
    static bool devicesDisconnected;
    static bool disconnectComplete;
    static int scrollPos;
    static int disconnectLoadingProgress;
    static long lastTiming;
    static constexpr int scrollMaxPos = 10;
    static constexpr int scrollDisconnectedMaxPos = 7;
    static constexpr int scrollDelay = 500;
    static constexpr int scrollCompleteDelay = 2000;
    static constexpr int loadingMax = 11;

    static void loop();
    static void scrollDisconnectTimings();
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
