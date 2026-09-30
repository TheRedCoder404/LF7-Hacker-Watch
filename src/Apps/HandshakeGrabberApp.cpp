#include "HandshakeGrabberApp.h"

#include "Apps.h"
#include "WindowManager.h"

String HandshakeGrabberApp::appNames[] = {"OSI-Analyser", "Bin-Analyser", "Logi-Analyser", "Code-Analyser"};
Selector HandshakeGrabberApp::selector = {appNames, true};

void HandshakeGrabberApp::setup() {
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
    app.setOnButtonPressed(&onButtonPressed);
}

Application &HandshakeGrabberApp::getApp() {
    return app;
}

void HandshakeGrabberApp::onUpdateDisplay(Display &display) {
    display.clear();

    if (CodeRiddleApp::isDone()) {
        display.setCursor(0, 0);
        display.print("Handshake");
        display.setCursor(0, 1);
        display.print("decrypted!");

        return;
    }

    if (WifiCrackApp::isDone()) {
        selector.onUpdateDisplay(display);
    } else {
        display.setCursor(0, 0);
        display.print("Waiting for");
        display.setCursor(0, 1);
        display.print("Handshake...");
    }
}

void HandshakeGrabberApp::onScrollUp() {
    selector.onScrollUp();
}

void HandshakeGrabberApp::onScrollDown() {
    selector.onScrollDown();
}

void HandshakeGrabberApp::onRotaryButtonPressed() {
    if (CodeRiddleApp::isDone()) {
        return;
    }
    WindowManager::setCurrentApp(*Apps::getHandshakeApps()[selector.getCurrentSelected()]);
}

void HandshakeGrabberApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getAppSelector().getApp());
}
