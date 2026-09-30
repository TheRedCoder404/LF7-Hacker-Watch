#include "SettingsApp.h"

#include "Apps.h"
#include "WindowManager.h"

int SettingsApp::scroll = 0;
int SettingsApp::viewScroll = 0;

const String SettingsApp::settings[] = {"Reset", "Full Reset"};
Selector SettingsApp::selector = {settings, true};

void SettingsApp::setup() {
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
    app.setOnButtonPressed(&onButtonPressed);
}

Application & SettingsApp::getApp() {
    return app;
}

void SettingsApp::onUpdateDisplay(Display &display) {
    display.clear();
    selector.onUpdateDisplay(display);
}

void SettingsApp::onScrollUp() {
    selector.onScrollUp();
}

void SettingsApp::onScrollDown() {
    selector.onScrollDown();
}

void SettingsApp::onRotaryButtonPressed() {
    if (selector.getCurrentSelected() == 0) {
        WifiCrackApp::reset();
        OSIRiddleApp::reset();
        BinaryRiddleApp::reset();
        LogicRiddleApp::reset();
        CodeRiddleApp::reset();
        WindowManager::setCurrentApp(Apps::getAppSelector().getApp());
    }

    if (selector.getCurrentSelected() == 1) {
        esp_restart();
    }
}

void SettingsApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getAppSelector().getApp());
}
