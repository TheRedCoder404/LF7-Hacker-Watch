#include "OSIRiddleApp.h"

#include "Apps/Apps.h"
#include "WindowManager.h"

const String OSIRiddleApp::blockText[] = {"OSI-Sequence:", "1: Router", "2: Switch", "3: Request", "4: Cable"};
Selector OSIRiddleApp::selector = {blockText, false};

void OSIRiddleApp::setup() {
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnButtonPressed(&onButtonPressed);
}

Application &OSIRiddleApp::getApp() {
    return app;
}

void OSIRiddleApp::onUpdateDisplay(Display &display) {
    display.clear();
    selector.onUpdateDisplay(display);
}

void OSIRiddleApp::onScrollUp() {
    selector.onScrollUp();
}

void OSIRiddleApp::onScrollDown() {
    selector.onScrollDown();
}

void OSIRiddleApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getHandshakeGrabber().getApp());
}
