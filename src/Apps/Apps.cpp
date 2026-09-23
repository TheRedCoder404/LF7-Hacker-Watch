#include "Apps.h"

TestApp Apps::testApp = TestApp();
Application *Apps::apps[] = {&testApp.getApp()};

TestApp Apps::getTestApp() {
    return testApp;
}

Application **Apps::getApps() {
    return apps;
}
