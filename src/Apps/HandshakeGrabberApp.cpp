#include "HandshakeGrabberApp.h"

#include "Apps.h"
#include "WindowManager.h"

void HandshakeGrabberApp::setup() {
    m_app.setUpdateDisplay(&onUpdateDisplay);
    m_app.setOnButtonPressed(&onButtonPressed);
}

Application &HandshakeGrabberApp::getApp() {
    return m_app;
}

void HandshakeGrabberApp::onUpdateDisplay(Display &display) {
    display.clear();

    display.setCursor(0, 0);
    display.print("Waiting for");
    display.setCursor(0, 1);
    display.print("Handshake...");
}

void HandshakeGrabberApp::onScrollUp() {
}

void HandshakeGrabberApp::onScrollDown() {
}

void HandshakeGrabberApp::onRotaryButtonPressed() {
}

void HandshakeGrabberApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getAppSelector().getApp());
}
