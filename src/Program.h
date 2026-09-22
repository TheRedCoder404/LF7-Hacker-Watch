#pragma once

#include "WindowManager.h"
#include "Apps/TestApp.h"

class Program {
public:
    Program()
        : menu()
        , windowManager(menu.getApp()) {
        setup();
    }

    void loop();

private:
    TestApp menu;
    WindowManager windowManager;

    void setup();
};
