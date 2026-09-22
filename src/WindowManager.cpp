#include "WindowManager.h"

void WindowManager::updateDisplay() {
    currentApp.updateDisplay();
}

void WindowManager::setCurrentApp(const Application& app) {
    currentApp = app;
}

void WindowManager::onRotarySwitchPressed() {
}

void WindowManager::loop() {
}
