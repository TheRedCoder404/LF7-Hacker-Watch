#pragma once

#include "WindowManager.h"
#include "Apps/Apps.h"

class Program {
public:
    Program()
        : windowManager(Apps::getTestApp().getApp()) {
        setup();
    }

    void loop();

private:
    WindowManager windowManager;

    void setup();
};
