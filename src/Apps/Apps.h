#pragma once

#include "TestApp.h"

class Apps {
public:
    static TestApp getTestApp();
    static Application **getApps();

private:
    static TestApp testApp;
    static Application *apps[];
};
