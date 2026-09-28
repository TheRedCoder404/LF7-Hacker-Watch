#include "WindowManager.h"

#include "Apps/Apps.h"

volatile bool WindowManager::toBeScrollUp = false;
volatile bool WindowManager::toBeScrollDown = false;

Application* WindowManager::currentApp = &Apps::getAppSelector().getApp();
Display WindowManager::display = Display();

void WindowManager::setup() {
    pinMode(button, INPUT);
    pinMode(rotaryButton, INPUT_PULLUP);

    attachInterruptArg(
        digitalPinToInterrupt(rotaryButton),
        rotarySwitchInterrupt,
        this,
        FALLING
    );

    currentApp->setDisplay(&display);
    encoder.setOnRotationUpCallback(&onRotationUp);
    encoder.setOnRotationDownCallback(&onRotationDown);

    updateDisplay();
}

void WindowManager::updateDisplay() {
    currentApp->updateDisplay();
}

void WindowManager::setCurrentApp(Application& app) {
    currentApp = &app;
    currentApp->setDisplay(&display);
    currentApp->updateDisplay();
}

void WindowManager::onRotarySwitchPressed() {
    toBePressed = true;
}

void WindowManager::loop() {
    encoder.loop();

    if (toBeScrollUp) {
        toBeScrollUp = false;
        if (currentApp != nullptr) {
            currentApp->onScrollUp();
        }
    }

    if (toBeScrollDown) {
        toBeScrollDown = false;
        if (currentApp != nullptr) {
            currentApp->onScrollDown();
        }
    }

    checkRotaryEncoderButton();
    checkButton();
}

void WindowManager::rotarySwitchInterrupt(void *argument) {
    auto* manager = static_cast<WindowManager*>(argument);
    manager->onRotarySwitchPressed();
}

void WindowManager::onRotationUp() {
    toBeScrollUp = true;
}

void WindowManager::onRotationDown() {
    toBeScrollDown = true;
}

void WindowManager::checkRotaryEncoder(int rotation) {
    if (rotation == rotaryState) {
        return;
    }

    if (rotation < rotaryState) {
        currentApp->onScrollUp();
    } else {
        currentApp->onScrollDown();
    }

    rotaryState = rotation;
}

void WindowManager::checkRotaryEncoderButton() {
    if (!toBePressed) {
        return;
    }
    uint32_t now = millis();

    if (!rotaryButtonPressed) {
        rotaryButtonPressed = true;
        lastPressed = now;

        Application* appBeforePress = currentApp;
        if (appBeforePress != nullptr) {
            appBeforePress->onRotaryButtonPressed();
        }

        if (currentApp != nullptr && currentApp != appBeforePress) {
            currentApp->updateDisplay();
        }
    }

    if (now - lastPressed >= RELEASED_DELAY) {
        rotaryButtonPressed = false;
        toBePressed = false;
        
        if (currentApp != nullptr) {
            currentApp->onRotaryButtonReleased();
        }
    }
}

void WindowManager::checkButton() {
    const bool isPressed = digitalRead(button);

    if (isPressed && !buttonPressed) {
        buttonPressed = true;
        if (currentApp != nullptr) {
            currentApp->onButtonPressed();
        }
    } else if (!isPressed && buttonPressed) {
        buttonPressed = false;
        if (currentApp != nullptr) {
            currentApp->onButtonReleased();
        }
    }
}
