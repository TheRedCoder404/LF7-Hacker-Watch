#pragma once

#include "AppSelector.h"
#include "TestApp.h"

class Apps {
public:
    static TestApp getTestApp();
    static AppSelector getAppSelector();

    static Application **getApps();
    static int getAppCount();

private:
    static TestApp testApp;
    static AppSelector appSelector;

    static Application *apps[];
};
