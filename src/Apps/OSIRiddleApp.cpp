#include "OSIRiddleApp.h"

#include "Apps.h"
#include "WindowManager.h"

const String OSIRiddleApp::blockText[] = {"OSI-Sequence", "1: Router", "2: Switch", "3: Request", "4: Cable"};
Selector OSIRiddleApp::selector = {blockText, false};

void OSIRiddleApp::setup() {
    m_app.setUpdateDisplay(&onUpdateDisplay);
    m_app.setOnScrollUp(&onScrollUp);
    m_app.setOnScrollDown(&onScrollDown);
    m_app.setOnButtonPressed(&onButtonPressed);
}

Application &OSIRiddleApp::getApp() {
    return m_app;
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
