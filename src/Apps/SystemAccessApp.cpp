#include "SystemAccessApp.h"

#include "Apps.h"
#include "WindowManager.h"

bool SystemAccessApp::hacked = false;

void SystemAccessApp::setup() {
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnButtonPressed(&onButtonPressed);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
}

Application& SystemAccessApp::getApp() {
    return app;
}

void SystemAccessApp::onUpdateDisplay(Display &display) {
    display.clear();

    if (hacked) {
        display.setCursor(0, 0);
        display.print("MASTER PASSWORD:");
        display.setCursor(0, 1);
        display.print("tHecompany1!");
    }
    else {
        display.setCursor(0, 0);
        display.print("No ACCESS");
    }
}

void SystemAccessApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getAppSelector().getApp());
}

void SystemAccessApp::onScrollUp() {
    hacked = !hacked;
}

void SystemAccessApp::onScrollDown() {
    hacked = !hacked;
}
