#include "WifiCrackApp.h"

#include "Apps.h"
#include "WindowManager.h"

bool WifiCrackApp::selecting = true;
bool WifiCrackApp::selectedYes = false;
bool WifiCrackApp::devicesDisconnected = false;
bool WifiCrackApp::disconnectComplete = false;
int WifiCrackApp::scrollPos = 0;
int WifiCrackApp::disconnectLoadingProgress = 0;
long WifiCrackApp::lastTiming = 0;

void WifiCrackApp::setup() {
    m_app.setLoop(&loop);
    m_app.setOnScrollUp(&onScrollUp);
    m_app.setOnScrollDown(&onScrollDown);
    m_app.setUpdateDisplay(&onUpdateDisplay);
    m_app.setOnButtonPressed(&onButtonPressed);
    m_app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
}

Application &WifiCrackApp::getApp() {
    return m_app;
}

void WifiCrackApp::loop() {
    if (devicesDisconnected && !disconnectComplete) {
        loadingTimings();
        return;
    }

    scrollDisconnectTimings();
}

void WifiCrackApp::scrollDisconnectTimings() {
    const long mills = millis();
    if (scrollPos == 0) {
        if (mills - lastTiming < scrollCompleteDelay) {
            return;
        }

        lastTiming = mills;
        scrollPos++;
        WindowManager::updateDisplay();
        return;
    }

    if (scrollPos < (disconnectComplete ? scrollDisconnectedMaxPos : scrollMaxPos)) {
        if (mills - lastTiming < scrollDelay) {
            return;
        }

        lastTiming = mills;
        scrollPos++;
        WindowManager::updateDisplay();
        return;
    }

    if (mills - lastTiming >= scrollCompleteDelay) {
        lastTiming = mills;
        scrollPos = 0;
        WindowManager::updateDisplay();
    }
}

void WifiCrackApp::loadingTimings() {
    const long mills = millis();
    if (disconnectLoadingProgress >= loadingMax) {
        disconnectComplete = true;
        scrollPos = 0;
        lastTiming = mills;
        WindowManager::updateDisplay();
        return;
    }

    if (mills - lastTiming < scrollDelay) {
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
    display.print(String("Disconnect nearby devices?").substring(scrollPos, 16 + scrollPos));

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
    display.print(String("Change to HandshakeGrab").substring(scrollPos, 16 + scrollPos));
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
    selecting = true;
    selectedYes = false;
    devicesDisconnected = false;
    scrollPos = 0;
    disconnectLoadingProgress = 0;
    lastTiming = 0;
}
