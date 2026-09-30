#include "BinaryRiddleApp.h"

#include "Apps/Apps.h"
#include "WindowManager.h"

const String BinaryRiddleApp::blockText[] = {"Binary-Sequence:", "1: 0110", "2: 0011", "3: 1001", "4: 0001"};
Selector BinaryRiddleApp::selector = {blockText, false};

void BinaryRiddleApp::setup() {
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnButtonPressed(&onButtonPressed);
}

Application &BinaryRiddleApp::getApp() {
    return app;
}

void BinaryRiddleApp::onUpdateDisplay(Display &display) {
    if (!OSIRiddleApp::isDone()) {
        display.clear();

        display.setCursor(0, 0);
        display.print("Waiting for");
        display.setCursor(0, 1);
        display.print("OSI-Sequence...");

        return;
    }

    selector.onUpdateDisplay(display);
}

void BinaryRiddleApp::onScrollUp() {
    selector.onScrollUp();
}

void BinaryRiddleApp::onScrollDown() {
    selector.onScrollDown();
}

void BinaryRiddleApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getHandshakeGrabber().getApp());
}
