#pragma once

#include "Application.h"
#include "Display.h"

class WindowManager {
public:
    WindowManager(Display& display, Application& app)
        : display(display)
        , currentApp(app) {}

    void updateDisplay();
    void setCurrentApp(const Application& app);

    void onRotarySwitchPressed();

    void loop();

private:
    Display& display;
    Application& currentApp;
};
