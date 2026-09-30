#include "WifiCrackApp.h"

#include "Apps.h"
#include "WindowManager.h"

ScrollingString WifiCrackApp::scrollText = {"Disconnect nearby devices?", 500, 2000};
bool WifiCrackApp::selecting = true;
bool WifiCrackApp::selectedYes = false;
bool WifiCrackApp::devicesDisconnected = false;
bool WifiCrackApp::disconnectComplete = false;
int WifiCrackApp::disconnectLoadingProgress = 0;
long WifiCrackApp::lastTiming = 0;

void WifiCrackApp::setup() {
    m_app.setLoop(&loop);
    m_app.setOnSelected(&onSelected);
    m_app.setOnScrollUp(&onScrollUp);
    m_app.setOnScrollDown(&onScrollDown);
    m_app.setUpdateDisplay(&onUpdateDisplay);
    m_app.setOnButtonPressed(&onButtonPressed);
    m_app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
}

void WifiCrackApp::reset() {
    selecting = true;
    selectedYes = false;
    devicesDisconnected = false;
    disconnectComplete = false;
    disconnectLoadingProgress = 0;
    lastTiming = 0;
    scrollText.reset()
}

Application &WifiCrackApp::getApp() {
    return m_app;
}

void WifiCrackApp::loop() {
    if (devicesDisconnected && !disconnectComplete) {
        loadingTimings();
        return;
    }

    scrollText.loop();
}

void WifiCrackApp::onSelected() {
    scrollText.reset();
}

void WifiCrackApp::loadingTimings() {
    const long mills = millis();
    if (disconnectLoadingProgress >= loadingMax) {
        disconnectComplete = true;
        scrollText.setText("Change to HandshakeGrab");
        WindowManager::updateDisplay();
        return;
    }

    if (mills - lastTiming < loadingDelay) {
        return;
    }

    lastTiming = mills;
    disconnectLoadingProgress++;
    WindowManager::updateDisplay();
}

void WifiCrackApp::onUpdateDisplay(Display &display) {
    display.clear();

    if (disconnectComplete) {
        printDisconnected(display);
        return;
    }

    if (!devicesDisconnected) {
        printDisconnectDialog(display);
        return;
    }

    printDisconnecting(display);
}

void WifiCrackApp::printDisconnectDialog(Display &display) {
    display.setCursor(0, 0);
    display.print(scrollText.getTextSlice());

    display.setCursor(0, 1);
    if (selectedYes) {
        display.print("[X]yes [ ]no");
    }
    else {
        display.print("[ ]yes [X]no");
    }
}

void WifiCrackApp::printDisconnecting(Display &display) {
    display.setCursor(0, 0);
    display.print("Disconnecting:");

    for (int i = 0; i < disconnectLoadingProgress; i++) {
        display.setCursor(i, 1);
        display.print(".");
    }
}

void WifiCrackApp::printDisconnected(Display &display) {
    display.setCursor(0, 0);
    display.print("Disconnected:");
    display.setCursor(0, 1);
    display.print(scrollText.getTextSlice());
}

void WifiCrackApp::onScrollUp() {
    selectedYes = !selectedYes;
}

void WifiCrackApp::onScrollDown() {
    selectedYes = !selectedYes;
}

void WifiCrackApp::onRotaryButtonPressed() {
    if (selecting) {
        if (!selectedYes) {
            onButtonPressed();
            return;
        }

        selecting = !selectedYes;
        devicesDisconnected = selectedYes;
        lastTiming = millis();
    }
}

void WifiCrackApp::onButtonPressed() {
    if (!disconnectComplete) {
        resetApp();
    }

    WindowManager::setCurrentApp(Apps::getAppSelector().getApp());
}

void WifiCrackApp::resetApp() {
    scrollText.setText("Disconnect nearby devices?");
    selecting = true;
    selectedYes = false;
    devicesDisconnected = false;
    disconnectLoadingProgress = 0;
    lastTiming = 0;
}

bool WifiCrackApp::isDone() {
    return disconnectComplete;
}
