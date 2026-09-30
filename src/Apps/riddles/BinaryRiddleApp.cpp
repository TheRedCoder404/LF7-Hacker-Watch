#include "BinaryRiddleApp.h"

#include "Apps/Apps.h"
#include "WindowManager.h"

const String BinaryRiddleApp::blockText[] = {"Binary-Sequence:", "1: 0110", "2: 0011", "3: 1001", "4: 0001", "Press to confirm"};
Selector BinaryRiddleApp::selector = {blockText, false};
bool BinaryRiddleApp::scrolling = false;
bool BinaryRiddleApp::confirmationEntered = false;
bool BinaryRiddleApp::selectedYes = false;
bool BinaryRiddleApp::pinConfirmed = false;
ScrollingString BinaryRiddleApp::scrollText = {"Was the pin successfully entered into the keypad?", 500, 2000};

void BinaryRiddleApp::setup() {
    app.setLoop(&loop);
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnSelected(&onSelected);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnButtonPressed(&onButtonPressed);
    app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
}

Application &BinaryRiddleApp::getApp() {
    return app;
}

bool BinaryRiddleApp::isDone() {
    return pinConfirmed;
}

void BinaryRiddleApp::reset() {
    scrolling = false;
    confirmationEntered = false;
    selectedYes = false;
    pinConfirmed = false;
    selector.reset();
    scrollText.reset();
}

void BinaryRiddleApp::loop() {
    if (scrolling && !isDone()) {
        scrollText.loop();
    }
}

void BinaryRiddleApp::onUpdateDisplay(Display &display) {
    if (isDone()) {
        display.clear();

        display.setCursor(0, 0);
        display.print("Binary-Sequence");
        display.setCursor(0, 1);
        display.print("already cleared");

        return;
    }

    if (!OSIRiddleApp::isDone()) {
        display.clear();

        display.setCursor(0, 0);
        display.print("Waiting for");
        display.setCursor(0, 1);
        display.print("OSI-Sequence...");

        return;
    }

    if (confirmationEntered) {
        display.clear();

        display.setCursor(0, 0);
        display.print(scrollText.getTextSlice());
        display.setCursor(0, 1);
        if (selectedYes) {
            display.print("[X]yes [ ]no");
        } else {
            display.print("[ ]yes [X]no");
        }

        return;
    }

    selector.onUpdateDisplay(display);
}

void BinaryRiddleApp::onSelected() {
    scrolling = false;
    confirmationEntered = false;
    selectedYes = false;
    selector.reset();
}

void BinaryRiddleApp::onScrollUp() {
    if (confirmationEntered) {
        selectedYes = !selectedYes;
        return;
    }

    selector.onScrollUp();
}

void BinaryRiddleApp::onScrollDown() {
    if (confirmationEntered) {
        selectedYes = !selectedYes;
        return;
    }

    selector.onScrollDown();
}

void BinaryRiddleApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getHandshakeGrabber().getApp());
}

void BinaryRiddleApp::onRotaryButtonPressed() {
    if (isDone()) {
        return;
    }

    if (!confirmationEntered) {
        confirmationEntered = true;
        scrolling = true;
        scrollText.reset();
        return;
    }

    confirmationEntered = false;
    scrolling = false;

    if (selectedYes) {
        pinConfirmed = true;
        WindowManager::setCurrentApp(Apps::getHandshakeGrabber().getApp());
    }
}
