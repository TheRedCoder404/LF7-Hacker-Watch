#pragma once

#include "WindowManager.h"
#include "Apps/Apps.h"

class Program {
public:
    Program()
        : windowManager(Apps::getAppSelector().getApp()) {
        setup();
    }

    void loop();

private:
    WindowManager windowManager;

    void setup();
};
