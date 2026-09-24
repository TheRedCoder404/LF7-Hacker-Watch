#include "Apps.h"

TestApp Apps::testApp = TestApp();
AppSelector Apps::appSelector = AppSelector();
Application *Apps::apps[] = {&testApp.getApp(), &appSelector.getApp()};

TestApp Apps::getTestApp() {
    return testApp;
}

AppSelector Apps::getAppSelector() {
    return appSelector;
}

Application **Apps::getApps() {
    return apps;
}

int Apps::getAppCount() {
    return sizeof(apps) / sizeof(Application *);
}
