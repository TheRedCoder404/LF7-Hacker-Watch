#include "OSIRiddleApp.h"

#include "Apps/Apps.h"
#include "WindowManager.h"

const String OSIRiddleApp::blockText[] = {"OSI-Sequence:", "1: Router", "2: Switch", "3: Request", "4: Cable", "Press to confirm"};
Selector OSIRiddleApp::selector = {blockText, false};
bool OSIRiddleApp::scrolling = false;
bool OSIRiddleApp::confirmationEntered = false;
bool OSIRiddleApp::selectedYes = false;
bool OSIRiddleApp::pinConfirmed = false;
ScrollingString OSIRiddleApp::scrollText = {"Was the pin successfully entered into the keypad?", 500, 2000};

void OSIRiddleApp::setup() {
    app.setLoop(&loop);
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnSelected(&onSelected);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnButtonPressed(&onButtonPressed);
    app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
}

Application &OSIRiddleApp::getApp() {
    return app;
}

bool OSIRiddleApp::isDone() {
    return pinConfirmed;
}

void OSIRiddleApp::loop() {
    if (scrolling) {
        scrollText.loop();
    }
}

void OSIRiddleApp::onUpdateDisplay(Display &display) {
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

void OSIRiddleApp::onSelected() {
    scrolling = false;
    confirmationEntered = false;
    selectedYes = false;
    selector.reset();
}

void OSIRiddleApp::onScrollUp() {
    if (confirmationEntered) {
        selectedYes = !selectedYes;
        return;
    }

    selector.onScrollUp();
}

void OSIRiddleApp::onScrollDown() {
    if (confirmationEntered) {
        selectedYes = !selectedYes;
        return;
    }

    selector.onScrollDown();
}

void OSIRiddleApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getHandshakeGrabber().getApp());
}

void OSIRiddleApp::onRotaryButtonPressed() {
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
