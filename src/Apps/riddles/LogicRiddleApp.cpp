#include "LogicRiddleApp.h"

#include "Apps/Apps.h"
#include "WindowManager.h"

const String LogicRiddleApp::blockText[] = {"Logic-Sequence:", "A=1 B=0 C=1 D=1", "1: A && B", "2: C || D", "3: A ^  C", "4:!B", "Press to confirm"};
Selector LogicRiddleApp::selector = {blockText, false};
bool LogicRiddleApp::scrolling = false;
bool LogicRiddleApp::confirmationEntered = false;
bool LogicRiddleApp::selectedYes = false;
bool LogicRiddleApp::pinConfirmed = false;
ScrollingString LogicRiddleApp::scrollText = {"Was the pin successfully entered into the keypad?", 500, 2000};

void LogicRiddleApp::setup() {
    app.setLoop(&loop);
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnSelected(&onSelected);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnButtonPressed(&onButtonPressed);
    app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
}

Application &LogicRiddleApp::getApp() {
    return app;
}

bool LogicRiddleApp::isDone() {
    return pinConfirmed;
}

void LogicRiddleApp::reset() {
    scrolling = false;
    confirmationEntered = false;
    selectedYes = false;
    pinConfirmed = false;
    selector.reset();
    scrollText.reset();
}

void LogicRiddleApp::loop() {
    if (scrolling) {
        scrollText.loop();
    }
}

void LogicRiddleApp::onUpdateDisplay(Display &display) {
    if (!BinaryRiddleApp::isDone()) {
        display.clear();

        display.setCursor(0, 0);
        display.print("Waiting for");
        display.setCursor(0, 1);
        display.print("Bin-Analysis...");

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

void LogicRiddleApp::onSelected() {
    scrolling = false;
    confirmationEntered = false;
    selectedYes = false;
    selector.reset();
}

void LogicRiddleApp::onScrollUp() {
    if (confirmationEntered) {
        selectedYes = !selectedYes;
        return;
    }

    selector.onScrollUp();
}

void LogicRiddleApp::onScrollDown() {
    if (confirmationEntered) {
        selectedYes = !selectedYes;
        return;
    }

    selector.onScrollDown();
}

void LogicRiddleApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getHandshakeGrabber().getApp());
}

void LogicRiddleApp::onRotaryButtonPressed() {
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
