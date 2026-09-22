#include "WindowManager.h"

void WindowManager::setup() {
    pinMode(rotarySw, INPUT_PULLUP);
    pinMode(button, INPUT);

    attachInterruptArg(digitalPinToInterrupt(rotarySw), &WindowManager::rotarySwitchInterrupt, this, FALLING);
}

void WindowManager::updateDisplay() {
    currentApp.updateDisplay();
}

void WindowManager::setCurrentApp(const Application& app) {
    currentApp = app;
    currentApp.setDisplay(&display);
}

void WindowManager::onRotarySwitchPressed() {
    toBePressed = true;
}

void WindowManager::loop() {
    checkRotaryEncoder();
    checkRotaryEncoderButton();
    checkButton();
}

void WindowManager::rotarySwitchInterrupt(void *argument) {
    auto* manager = static_cast<WindowManager*>(argument);
    manager->onRotarySwitchPressed();
}

void WindowManager::checkRotaryEncoder() {
    const long currentRot = encoder.read();
    if (currentRot == rotaryState) {
        return;
    }

    if (currentRot < rotaryState) {
        currentApp.onScrollUp();
    } else {
        currentApp.onScrollDown();
    }

    rotaryState = currentRot;
}

void WindowManager::checkRotaryEncoderButton() {
    if (!toBePressed) {
        return;
    }
    uint32_t now = millis();

    if (!rotaryButtonPressed) {
        rotaryButtonPressed = true;
        lastPressed = now;
        currentApp.onRotaryButtonPressed();
    }

    if (now - lastPressed >= RELEASED_DELAY) {

        rotaryButtonPressed = false;
        toBePressed = false;
        currentApp.onRotaryButtonReleased();
    }
}

void WindowManager::checkButton() {
    const bool isPressed = digitalRead(button);
    if (isPressed) {
        buttonPressed = true;
        currentApp.onButtonPressed();
    } else if (buttonPressed) {
        buttonPressed = false;
        currentApp.onButtonReleased();
    }
}
