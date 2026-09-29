#include "HandshakeGrabberApp.h"

#include "Apps.h"
#include "WindowManager.h"

ScrollingString HandshakeGrabberApp::testText = {"this is a fantastic super test text", 500, 2000};

void HandshakeGrabberApp::setup() {
    m_app.setLoop(&loop);
    m_app.setOnSelected(&onSelected);
    m_app.setUpdateDisplay(&onUpdateDisplay);
    m_app.setOnButtonPressed(&onButtonPressed);
}

void HandshakeGrabberApp::loop() {
    testText.loop();
}

void HandshakeGrabberApp::onSelected() {
    testText.reset();
}

Application &HandshakeGrabberApp::getApp() {
    return m_app;
}

void HandshakeGrabberApp::onUpdateDisplay(Display &display) {
    display.clear();

    if (!WifiCrackApp::isDone()) {
        display.setCursor(0, 0);
        display.print("Waiting for");
        display.setCursor(0, 1);
        display.print(testText.getTextSlice());
    }
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
