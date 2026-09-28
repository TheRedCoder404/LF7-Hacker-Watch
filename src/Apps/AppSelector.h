#pragma once

#include "Application.h"

class AppSelector {
public:
    AppSelector()
        : app("App Selector") {
        setUp();
    }

    void setUp();
    Application& getApp();

private:
    static const String SELECTED_SYMBOL;
    static const String NOT_SELECTED_SYMBOL;

    Application app;
    static bool pressed;
    static int scroll;
    static int viewScroll;

    static void onUpdateDisplay(Display& display);
    static String getAppNameAt(int index);
    static void onScrollUp();
    static void onScrollDown();
    static void scrollViewUp();
    static void scrollViewDown();
    static void onRotaryButtonPressed();
};
