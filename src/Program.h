#pragma once

#include "WindowManager.h"

class Program {
public:
    Program()
        : windowManager() {
        setup();
    }

    void loop();

private:
    WindowManager windowManager;

    void setup();
};
