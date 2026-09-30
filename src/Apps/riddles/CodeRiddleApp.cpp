#include "CodeRiddleApp.h"

#include "Apps/Apps.h"
#include "WindowManager.h"

const String CodeRiddleApp::blockText[] = {"What does this", "print?:", "i = 1", "x = \"\"", "for _ in 'x'*4':", "  i = i * 3", "  x=x+f\"{i}\"[-1]", "print(x)", "Press to confirm"};
const String CodeRiddleApp::funnyTexts[] = {"decrypting", "forcing control", "shenanigan-ing"};
Selector CodeRiddleApp::selector = {blockText, false};
bool CodeRiddleApp::scrolling = false;
bool CodeRiddleApp::confirmationEntered = false;
bool CodeRiddleApp::selectedYes = false;
bool CodeRiddleApp::pinConfirmed = false;
bool CodeRiddleApp::done = false;
long CodeRiddleApp::lastLoop = 0;
int CodeRiddleApp::progress = 0;
int CodeRiddleApp::currentPass = 0;
ScrollingString CodeRiddleApp::scrollText = {"Was the pin successfully entered into the keypad?", 500, 2000};

void CodeRiddleApp::setup() {
    app.setLoop(&loop);
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnSelected(&onSelected);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnButtonPressed(&onButtonPressed);
    app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
}

Application &CodeRiddleApp::getApp() {
    return app;
}

bool CodeRiddleApp::isDone() {
    return done;
}

void CodeRiddleApp::loop() {
    if (pinConfirmed) {
        const long mills = millis();
        if (mills - lastLoop >= loadingDelay) {
            lastLoop = mills;

            if (progress < 15) {
                progress++;
                WindowManager::updateDisplay();
                return;
            }
            progress = 0;

            if (currentPass < 2) {
                currentPass++;
                WindowManager::updateDisplay();
                return;
            }

            pinConfirmed = false;
            done = true;
            WindowManager::setCurrentApp(Apps::getHandshakeGrabber().getApp());
        }

        return;
    }

    if (scrolling) {
        scrollText.loop();
    }
}

void CodeRiddleApp::onUpdateDisplay(Display &display) {
    if (!LogicRiddleApp::isDone()) {
        display.clear();

        display.setCursor(0, 0);
        display.print("Waiting for");
        display.setCursor(0, 1);
        display.print("Logi-Analysis...");

        return;
    }

    if (pinConfirmed) {
        display.clear();

        display.setCursor(0, 0);
        display.print(funnyTexts[currentPass]);

        display.setCursor(0, 1);
        for (int i = 0; i < progress; i++) {
            display.print(".");
        }

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

void CodeRiddleApp::onSelected() {
    scrolling = false;
    confirmationEntered = false;
    selectedYes = false;
    selector.reset();
}

void CodeRiddleApp::onScrollUp() {
    if (confirmationEntered) {
        selectedYes = !selectedYes;
        return;
    }

    selector.onScrollUp();
}

void CodeRiddleApp::onScrollDown() {
    if (confirmationEntered) {
        selectedYes = !selectedYes;
        return;
    }

    selector.onScrollDown();
}

void CodeRiddleApp::onButtonPressed() {
    WindowManager::setCurrentApp(Apps::getHandshakeGrabber().getApp());
}

void CodeRiddleApp::onRotaryButtonPressed() {
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
    }
}
