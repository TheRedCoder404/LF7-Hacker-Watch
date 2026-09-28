#include "WifiCrackApp.h"

#include "Apps.h"
#include "WindowManager.h"

int WifiCrackApp::scrollPos = 0;
long WifiCrackApp::lastScrolled = 0;

void WifiCrackApp::setup() {
    m_app.setLoop(&loop);
    m_app.setUpdateDisplay(&onUpdateDisplay);
    m_app.setOnButtonPressed(&onButtonPressed);
}

Application &WifiCrackApp::getApp() {
    return m_app;
}

void WifiCrackApp::loop() {
    const long mills = millis();
    if (scrollPos == 0) {
        if (mills - lastScrolled < scrollCompleteDelay) {
            return;
        }

        lastScrolled = mills;
        scrollPos++;
        WindowManager::updateDisplay();
        return;
    }

    if (scrollPos < scrollMaxPos) {
        if (mills - lastScrolled < scrollDelay) {
            return;
        }

        lastScrolled = mills;
        scrollPos++;
        WindowManager::updateDisplay();
        return;
    }

    if (mills - lastScrolled >= scrollCompleteDelay) {
        lastScrolled = mills;
        scrollPos = 0;
        WindowManager::updateDisplay();
    }
}

void WifiCrackApp::onUpdateDisplay(Display &display) {
    display.clear();

    display.setCursor(0, 0);
    display.print(String("Disconnect nearby devices?").substring(scrollPos, 16 + scrollPos));

    display.setCursor(0, 1);
    display.print("[X]yes [ ]no");
}

void WifiCrackApp::onScrollUp() {
}

void WifiCrackApp::onScrollDown() {
}

void WifiCrackApp::onRotaryButtonPressed() {
}

void WifiCrackApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getAppSelector().getApp());
}
